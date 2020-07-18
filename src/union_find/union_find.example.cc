//
// Created by dx on 7/15/20.
//

#include <cstdlib>
#include <iostream>
#include <utility>
#include <vector>

#include "union_find/union_find.h"

int main() {
  cpp::union_find::UnionFind uf(10);

  std::vector<std::pair<int, int>> v{{4, 3}, {3, 8}, {6, 5}, {9, 4},
                                     {2, 1}, {8, 9}, {5, 0}, {7, 2},
                                     {6, 1}, {1, 0}, {6, 7}};

  for (auto const &pair : v) {
    uf.UnionSet(pair.first, pair.second);
  }
  std::cout << uf.Count() << std::endl;

  return EXIT_SUCCESS;
}