//
// Created by dx on 7/15/20.
//

#ifndef CPP_UNION_FIND_UNION_FIND_H
#define CPP_UNION_FIND_UNION_FIND_H

#include <vector>

namespace cpp::union_find {
class UnionFind {
 public:
  explicit UnionFind(int size);

  int FindRoot(int child);
  void UnionSet(int x, int y);
  bool Connected(int x, int y);
  [[nodiscard]] int Count() const;

 private:
  std::vector<int> parent_{};
  int count_{};

  void MakeSet(int size);
};
}  // namespace cpp::union_find

#endif  // CPP_UNION_FIND_UNION_FIND_H
