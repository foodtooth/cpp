//
// Created by dx on 2/20/21.
//

#include "common/singleton.h"

#include <iostream>

class Test final : public cpp::common::Singleton<Test> {
 public:
  explicit Test(Token) { std::cout << "constructed" << std::endl; }
  ~Test() { std::cout << "destructed" << std::endl; }

  void use() const { std::cout << "in use" << std::endl; };
};

int main() {
  // Test cannot_create; /* ERROR */

  std::cout << "Entering main()" << std::endl;
  {
    auto const& t = Test::instance();
    t.use();
  }
  {
    auto const& t = Test::instance();
    t.use();
  }
  std::cout << "Leaving main()" << std::endl;
}