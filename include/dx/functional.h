//
// Created by Michael Donux on 2021/9/18.
//

#ifndef CPP_DX_FUNCTIONAL_H
#define CPP_DX_FUNCTIONAL_H

#include <memory>

namespace cpp::dx {
template <typename>
class function;  // no definition

template <typename ReturnType, typename... Args>
class function<ReturnType(Args...)> {
 public:
  template <typename T>
  function& operator=(T t) {
    callable_ = std::make_unique<Callable<T>>(t);
    return *this;
  }
  ReturnType operator()(Args... args) const {
    assert(callable_);
    return callable_->Invoke(args...);
  }

 private:
  class CallableBase {
   public:
    virtual ~CallableBase() = default;
    virtual ReturnType Invoke(Args...) = 0;
  };
  template <typename T>
  class Callable : public CallableBase {
   public:
    Callable(const T& t) : t_(t) {}
    ~Callable() override = default;
    ReturnType Invoke(Args... args) override { return t_(args...); }

   private:
    T t_;
  };
  std::unique_ptr<CallableBase> callable_;
};
}  // namespace cpp::dx

#endif  // CPP_DX_FUNCTIONAL_H
