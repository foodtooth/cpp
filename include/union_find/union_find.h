//
// Created by dx on 7/15/20.
//

#ifndef CPP_UNION_FIND_UNION_FIND_H
#define CPP_UNION_FIND_UNION_FIND_H

#include <vector>

namespace cpp::union_find {
class UnionFind {
 public:
  explicit UnionFind(std::vector<int>::size_type size) {
    parent_.resize(size);
    for (decltype(parent_)::size_type index{}; index < parent_.size(); ++index)
      parent_[index] = index;
  }

 private:
  std::vector<int> parent_{};
};
}  // namespace cpp::union_find

#endif  // CPP_UNION_FIND_UNION_FIND_H
