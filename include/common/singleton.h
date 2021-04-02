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

// This will lead to segfault in process termination when so other singleton
// try to access instance method all the time. Use static shared_ptr,
// carefully define init order for shared_ptr and actual instance. Use
// weak_ptr to access shared_ptr to ensure that instance will always be valid
// as long as weak_ptr can successfully lock shared_ptr. (destructor is
// reverse order of object initialization. Make shared_ptr live longer than
// the instance)
template <typename T>
T& Singleton<T>::instance() {
  static T instance{Token{}};
  return instance;
}
}  // namespace cpp::common

#endif  // CPP_COMMON_SINGLETON_H
