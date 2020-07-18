//
// Created by dx on 7/15/20.
//

#include "union_find/union_find.h"

namespace cpp::union_find {

UnionFind::UnionFind(int size) : count_{size} { MakeSet(size); }

int UnionFind::FindRoot(int child) {
  if (parent_[child] == child) return child;
  parent_[child] = FindRoot(parent_[child]);  // path compression
  return parent_[child];
}

void UnionFind::UnionSet(int x, int y) {
  int root_x = FindRoot(x);
  int root_y = FindRoot(y);
  if (root_x == root_y) return;
  parent_[root_x] = root_y;
  --count_;
}

void UnionFind::MakeSet(int size) {
  parent_.resize(size);
  for (decltype(parent_)::size_type index{}; index < parent_.size(); ++index)
    parent_[index] = index;
}

bool UnionFind::Connected(int x, int y) { return FindRoot(x) == FindRoot(y); }

int UnionFind::Count() const { return count_; }

}  // namespace cpp::union_find