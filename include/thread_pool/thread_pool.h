/*
 * thread_pool.h
 *
 *  Created on: Jun 7, 2019
 *      Author: dx
 */

#ifndef CPP_THREAD_POOL_THREAD_POOL_H_
#define CPP_THREAD_POOL_THREAD_POOL_H_

#include <condition_variable>
#include <cstddef>
#include <functional>
#include <future>
#include <mutex>
#include <queue>
#include <thread>
#include <type_traits>
#include <vector>

namespace cpp::thread_pool {

class ThreadPool final {
  using Task = std::packaged_task<void()>;

 public:
  ThreadPool() = delete;
  explicit ThreadPool(std::size_t thread_num);

  ThreadPool(const ThreadPool&) = delete;
  ThreadPool(ThreadPool&&) = delete;
  ThreadPool& operator=(const ThreadPool&) = delete;
  ThreadPool& operator=(ThreadPool&&) = delete;

  ~ThreadPool();

  template <typename F, typename... Args>
  auto PushTask(F&& f, Args&&... args)
      -> std::future<std::invoke_result_t<F, Args...>>;

 private:
  std::vector<std::thread> workers_;

  std::queue<Task> tasks_;
  bool stop_{};

  std::mutex m_;
  std::condition_variable cv_;

  void StartPool(std::size_t thread_num);
  void StopPool();
};

template <typename F, typename... Args>
auto ThreadPool::PushTask(F&& f, Args&&... args)
    -> std::future<std::invoke_result_t<F, Args...>> {
  using RetType = std::invoke_result_t<F, Args...>;

  auto task = std::packaged_task<RetType()>(
      std::bind(std::forward<F>(f), std::forward<Args>(args)...));

  auto future = task.get_future();
  std::lock_guard<std::mutex> lock(m_);
  if (stop_)
    throw std::runtime_error("Tried pushing a task on stopped ThreadPool");
  tasks_.emplace(Task(std::move(task)));
  cv_.notify_one();

  return future;
}

}  // namespace cpp::thread_pool

#endif /* CPP_THREAD_POOL_THREAD_POOL_H_ */
