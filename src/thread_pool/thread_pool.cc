/*
 * thread_pool.cc
 *
 *  Created on: Jun 7, 2019
 *      Author: dx
 */

#include "thread_pool/thread_pool.h"

#include <utility>

namespace cpp::thread_pool {
ThreadPool::ThreadPool(std::size_t thread_num) { StartPool(thread_num); }

ThreadPool::~ThreadPool() { StopPool(); }

void ThreadPool::StartPool(std::size_t thread_num) {
  auto thread_func = [this]() {
    while (true) {
      std::packaged_task<void()> task;
      {
        std::unique_lock<std::mutex> lock(m_);
        cv_.wait(lock, [this] { return !tasks_.empty() || stop_; });
        if (stop_) break;
        task = std::move(tasks_.front());
        tasks_.pop();
      }
      task();
    }
  };
  workers_.reserve(thread_num);
  for (std::size_t index{}; index < thread_num; ++index)
    workers_.emplace_back(thread_func);
}

void ThreadPool::StopPool() {
  {
    std::lock_guard<std::mutex> lock(m_);
    stop_ = true;
  }
  cv_.notify_all();
  for (auto &worker : workers_)
    if (worker.joinable()) worker.join();
}
}  // namespace cpp::thread_pool