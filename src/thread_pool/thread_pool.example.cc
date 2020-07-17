//
// Created by dx on 7/17/20.
//

#include <cstdlib>
#include <iostream>

#include "thread_pool/thread_pool.h"

int main() {
  cpp::thread_pool::ThreadPool tp(4);

  auto futures = std::vector<std::future<std::size_t>>();
  for (std::size_t index{}; index < 1000; ++index) {
    futures.emplace_back(tp.PushTask([index]() { return index; }));
  }

  for (auto &future : futures) {
    std::cout << future.get() << std::endl;
  }

  return EXIT_SUCCESS;
}