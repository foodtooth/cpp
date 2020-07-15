/*
 * thread_pool.h
 *
 *  Created on: Jun 7, 2019
 *      Author: dx
 */

#ifndef CPP_THREAD_POOL_THREAD_POOL_H_
#define CPP_THREAD_POOL_THREAD_POOL_H_

#include <queue>
#include <thread>
#include <vector>

namespace cpp {
namespace thread_pool {

class BoundedQueue {};

class ThreadPool {
 public:
  ThreadPool() = default;
  ThreadPool(const ThreadPool&) = default;
  ThreadPool(ThreadPool&&) = default;
  ThreadPool& operator=(const ThreadPool&) = default;
  ThreadPool& operator=(ThreadPool&&) = default;
  ~ThreadPool() = default;

 private:
  std::vector<std::thread> pool_(std::thread::hardware_concurrency());
  BoundedQueue task_queue_;
};
}  // namespace thread_pool
}  // namespace cpp

#endif /* CPP_THREAD_POOL_THREAD_POOL_H_ */
