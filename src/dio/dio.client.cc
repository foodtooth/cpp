//
// Created by dx on 12/25/20.
//

#include "dio/dio.h"

#include <cstdlib>

int main() {
  cpp::dio::ClientHandler ch{};
  cpp::dio::IoLoop::GetInstance().Start();

  return EXIT_SUCCESS;
}