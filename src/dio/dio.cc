//
// Created by dx on 12/24/20.
//
#include "dio/dio.h"

#include <arpa/inet.h>
#include <fcntl.h>
#include <netdb.h>
#include <sys/epoll.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#include <array>
#include <cerrno>
#include <cstdio>
#include <cstring>
#include <string>
#include <thread>

namespace cpp::dio {
IoLoop::IoLoop() {
  epfd_ = epoll_create1(0);
  if (epfd_ < 0) {
    throw EpollCreateFailure("Failed epoll_create1");
  }
}

[[noreturn]] void IoLoop::Start() {
  std::array<epoll_event, kMaxEvents> events{};
  while (true) {
    int nfds = epoll_wait(epfd_, events.data(), kMaxEvents, -1);
    for (int i{}; i < nfds; ++i) {
      auto e = events[i];
      handlers_[e.data.fd]->Handle(e);
    }
  }
}

void IoLoop::AddHandler(int fd, Handler *p, std::uint32_t events) {
  handlers_[fd] = p;
  epoll_event e{};
  e.data.fd = fd;
  e.events = events;
  std::printf("AddHandler. epfd_: %d, fd: %d, e: %d\n", epfd_, fd, events);
  if (epoll_ctl(epfd_, EPOLL_CTL_ADD, fd, &e) < 0) {
    std::printf("Failed to insert handler to epoll\n");
  }
}

void IoLoop::ModEvents(int fd, std::uint32_t events) const {
  epoll_event e{};
  e.data.fd = fd;
  e.events = events;
  if (epoll_ctl(epfd_, EPOLL_CTL_MOD, fd, &e) < 0) {
    std::printf("Failed to modify events to epoll\n");
  }
}

void IoLoop::DelHandler(int fd) {
  handlers_.erase(fd);
  epoll_ctl(epfd_, EPOLL_CTL_DEL, fd, nullptr);
}

namespace {
bool SetNonBlocking(int fd) {
  int flags = fcntl(fd, F_GETFL, 0);
  if (flags == -1) {
    std::printf("fcntl failed (F_GETFL)\n");
    return false;
  }
  flags |= O_NONBLOCK;
  flags = fcntl(fd, F_SETFL, flags);
  if (flags == -1) {
    std::printf("fcntl failed (F_SETFL)\n");
    return false;
  }
  return true;
}

// Get sockaddr, IPv4 or IPv6:
void *GetInAddr(sockaddr *sa) {
  if (sa->sa_family == AF_INET) {
    return &(((struct sockaddr_in *)sa)->sin_addr);
  }
  return &(((struct sockaddr_in6 *)sa)->sin6_addr);
}

bool WriteData(int fd, int counter) {
  std::string msg{kMsg};
  msg.append(std::to_string(counter));
  if (send(fd, msg.data(), msg.size(), 0) == -1) {
    std::perror("send");
    return false;
  }
  return true;
}
}  // namespace

ServerHandler::ServerHandler(int port) {
  addrinfo hints{}, *ai, *p;
  hints.ai_family = AF_UNSPEC;
  hints.ai_socktype = SOCK_STREAM;
  hints.ai_flags = AI_PASSIVE;
  int rv = getaddrinfo(nullptr, std::to_string(port).data(), &hints, &ai);
  std::string msg{"Failed getaddrinfo: "};
  msg.append(gai_strerror(rv));
  if (rv != 0) {
    throw HandlerInitFailure(msg);
  }

  int yes{1};  // For setsockopt() SO_REUSEADDR, below
  int fd{};
  for (p = ai; p != nullptr; p = p->ai_next) {
    fd = socket(p->ai_family, p->ai_socktype, p->ai_protocol);
    if (fd < 0) {
      continue;
    }
    // Lose the pesky "address already in use" error message
    setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int));
    if (bind(fd, p->ai_addr, p->ai_addrlen) < 0) {
      close(fd);
      continue;
    }
    break;
  }
  // If we got here, it means we didn't get bound
  if (p == nullptr) {
    msg = "Failed binding fd";
    throw HandlerInitFailure(msg);
  }
  freeaddrinfo(ai);
  if (!SetNonBlocking(fd)) {
    msg = "Failed SetNonBlocking";
    throw HandlerInitFailure(msg);
  }
  if (listen(fd, kMaxPendingConn) < 0) {
    msg = "Failed to listen on server socket";
    throw HandlerInitFailure(msg);
  }
  IoLoop::GetInstance().AddHandler(fd, this, EPOLLIN | EPOLLET);
}

bool ServerHandler::Handle(epoll_event e) {
  int fd = e.data.fd;
  sockaddr_storage client_addr{};
  socklen_t addr_len = sizeof client_addr;

  int client_fd{};
  while (true) {
    client_fd = accept(fd, (struct sockaddr *)&client_addr, &addr_len);
    if (client_fd < 0) {
      if (errno == EAGAIN || errno == EWOULDBLOCK) {
        std::printf("No clients currently available\n");
        continue;
      } else {
        std::printf("accept failed: %s\n", std::strerror(errno));
        return false;
      }
    }
    break;
  }

  char remote_ip[INET6_ADDRSTRLEN];
  std::printf("new connection from %s on socket %d\n",
              inet_ntop(client_addr.ss_family,
                        GetInAddr((struct sockaddr *)&client_addr), remote_ip,
                        INET6_ADDRSTRLEN),
              client_fd);

  //  if (!SetNonBlocking(client_fd)) {
  //    std::printf("SetNonBlocking failed\n");
  //    return false;
  //  }

  Handler *ptr = new PingPongHandler();
  IoLoop::GetInstance().AddHandler(client_fd, ptr, EPOLLIN);
  return true;
}

ClientHandler::ClientHandler(int port) {
  addrinfo hints{}, *server_info, *p;
  hints.ai_family = AF_UNSPEC;
  hints.ai_socktype = SOCK_STREAM;
  int rv =
      getaddrinfo(nullptr, std::to_string(port).data(), &hints, &server_info);
  std::string msg{"ClientHandler failed to getaddrinfo: "};
  msg.append(gai_strerror(rv));
  if (rv != 0) {
    throw HandlerInitFailure(msg);
  }

  int fd{};
  // loop through all the results and connect to the first we can
  for (p = server_info; p != nullptr; p = p->ai_next) {
    fd = socket(p->ai_family, p->ai_socktype, p->ai_protocol);
    if (fd < 0) {
      std::perror("Client: socket");
      continue;
    }
    // SetNonBlocking(fd);
    if (connect(fd, p->ai_addr, p->ai_addrlen) < 0) {
      close(fd);
      std::perror("Client: connect");
      continue;
    }
    break;
  }
  if (p == nullptr) {
    msg = "Client: failed to connect";
    throw HandlerInitFailure(msg);
  }

  char remote_ip[INET6_ADDRSTRLEN];
  std::printf("connecting to %s\n",
              inet_ntop(p->ai_family, GetInAddr((struct sockaddr *)p->ai_addr),
                        remote_ip, INET6_ADDRSTRLEN));
  freeaddrinfo(server_info);
  //  SetNonBlocking(fd);

  Handler *ptr = new PingPongHandler();
  IoLoop::GetInstance().AddHandler(fd, ptr, EPOLLOUT);
}

bool PingPongHandler::Handle(epoll_event e) {
  int fd{e.data.fd};
  if ((e.events & EPOLLERR) || (e.events & EPOLLHUP)) {
    IoLoop::GetInstance().DelHandler(fd);
    return false;
  }
  if (e.events & EPOLLOUT) {
    WriteData(fd, count_ + 1);
    IoLoop::GetInstance().ModEvents(fd, EPOLLIN);
  }
  if (e.events & EPOLLIN) {
    int len = recv(fd, buf, kBufferSize, 0);
    if (len < 0) {
      std::printf("recv returned unrecoverable error %d\n", errno);
    } else {
      buf[len] = 0;
      std::string num(std::begin(buf) + kMsg.size());
      count_ = std::stoi(num);
    }
    if (len > 0) {
      std::printf("recv %s\n", buf);
      IoLoop::GetInstance().ModEvents(fd, EPOLLOUT);
    } else {
      IoLoop::GetInstance().DelHandler(fd);
    }
  }

  return false;
}
}  // namespace cpp::dio
