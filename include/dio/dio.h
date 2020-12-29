//
// Created by dx on 12/24/20.
//

#ifndef CPP_DIO_DIO_H
#define CPP_DIO_DIO_H

#include <sys/epoll.h>

#include <cstdint>
#include <stdexcept>
#include <unordered_map>
#include <variant>

namespace cpp::dio {
inline constexpr int kMaxEvents{20};
inline constexpr int kBufferSize{256};
inline constexpr int kMaxPendingConn{10};
inline constexpr int kDefaultPort{2333};

// Interface
class Handler {
 public:
  Handler() = default;
  Handler(const Handler &) = delete;
  Handler(Handler &&) = default;
  Handler &operator=(const Handler &) = delete;
  Handler &operator=(Handler &&) = default;
  virtual ~Handler() = default;

  virtual bool Handle(epoll_event e) = 0;
};

class ServerHandler : public Handler {
 public:
  explicit ServerHandler(int port = kDefaultPort);
  bool Handle(epoll_event e) override;
};
class ClientHandler : public Handler {
 public:
  explicit ClientHandler(int port = kDefaultPort);
  bool Handle(epoll_event e) override;

 private:
  int sockopt_ret_{-1};
};
class PingPongHandler : public Handler {
 public:
  bool Handle(epoll_event e) override;
};

using AHandler = std::variant<ServerHandler, ClientHandler, PingPongHandler>;

class IoLoop {
 public:
  IoLoop(const IoLoop &) = delete;
  IoLoop(IoLoop &&) = delete;
  IoLoop &operator=(const IoLoop &) = delete;
  IoLoop &operator=(IoLoop &&) = delete;
  // logging, terminate
  ~IoLoop() = default;

  static IoLoop &GetInstance() {
    static IoLoop instance;
    return instance;
  }

  [[noreturn]] void Start();
  void AddHandler(int fd, AHandler ah, std::uint32_t events);
  // TODO: AddEvents, DelEvents
  // TODO: handlers_ -> socket_infos_
  //  void AddEvents(int fd, std::uint32_t events);
  void ModEvents(int fd, std::uint32_t events);
  void DelHandler(int fd);

 private:
  IoLoop();

  int epfd_;
  // TODO: atomic lock
  std::unordered_map<int, AHandler> handlers_{};
};

class IoLoopException : public std::runtime_error {
 public:
  explicit IoLoopException(const std::string &msg)
      : std::runtime_error(msg + ", IoLoop Exception") {}
};
class HandlerException : public std::runtime_error {
 public:
  explicit HandlerException(const std::string &msg)
      : std::runtime_error(msg + ", Handler Exception") {}
};

class EpollCreateFailure : public IoLoopException {
 public:
  explicit EpollCreateFailure(const std::string &msg) : IoLoopException(msg){};
};

class HandlerInitFailure : public HandlerException {
 public:
  explicit HandlerInitFailure(const std::string &msg) : HandlerException(msg){};
};
}  // namespace cpp::dio

#endif  // CPP_DIO_DIO_H
