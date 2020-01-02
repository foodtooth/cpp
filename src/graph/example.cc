//
// Created by dx on 10/30/19.
//

#include <cstdio>

#include "binary_tree.h"
#include "trie.h"

int main() {
  BinaryTree<float> bt;

  bt.Insert(3);
  bt.Insert(1);
  bt.Insert(4);
  bt.Insert(5);
  bt.Insert(12);
  bt.Insert(-4);
  bt.Insert(2);
  bt.Insert(4.5);

  bt.BreadthFirstTraversal();
  bt.PreOrderTraversal();
  bt.PreOrderTraversalIterative();
  bt.InOrderTraversal();
  bt.InOrderTraversalIterative();
  bt.PostOrderTraversal();

  Trie trie({"l", "la", "last", "begin"});
  trie.Insert("others");
  std::printf("%s\n", trie.Search("last") ? "true" : "false");
  std::printf("%s\n", trie.StartsWith("othersd") ? "true" : "false");

  return 0;
}