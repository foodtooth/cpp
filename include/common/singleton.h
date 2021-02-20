//
// Created by dx on 2/20/21.
//

#ifndef CPP_COMMON_SINGLETON_H
#define CPP_COMMON_SINGLETON_H

namespace cpp::common {
template <typename T>
class Singleton {
 public:
  static T& instance();

  Singleton(const Singleton&) = delete;
  Singleton& operator=(const Singleton) = delete;
  Singleton(Singleton&&) = delete;
  Singleton& operator=(Singleton&&) = delete;

 protected:
  struct Token {};
  Singleton() = default;
};

template <typename T>
T& Singleton<T>::instance() {
  static T instance{Token{}};
  return instance;
}
}  // namespace cpp::common

#endif  // CPP_COMMON_SINGLETON_H
