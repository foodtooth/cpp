//
// Created by dx on 10/30/19.
//

#ifndef CPP_BINARY_TREE_H
#define CPP_BINARY_TREE_H

#include <iostream>
#include <memory>
#include <queue>
#include <stack>
#include <vector>

template <typename T>
class BinaryTree {
 public:
  BinaryTree() : root_{nullptr} {}
  ~BinaryTree() = default;

  BinaryTree(BinaryTree const&) = default;
  BinaryTree& operator=(BinaryTree const&) = default;

  BinaryTree(BinaryTree&&) noexcept = default;
  BinaryTree& operator=(BinaryTree&&) noexcept = default;

  void Insert(const T& value) { Insert(root_, value); }
  bool Contains(const T& value) { return Contains(root_, value); }

  void BreadthFirstTraversal() {
    BreadthFirstTraversal(root_);
    std::cout << std::endl;
  }
  void PreOrderTraversal() {
    PreOrderTraversal(root_);
    std::cout << std::endl;
  }
  void PreOrderTraversalIterative() {
    PreOrderTraversalIterative(root_);
    std::cout << std::endl;
  }
  void InOrderTraversal() {
    InOrderTraversal(root_);
    std::cout << std::endl;
  }
  void InOrderTraversalIterative() {
    InOrderTraversalIterative(root_);
    std::cout << std::endl;
  }
  void PostOrderTraversal() {
    PostOrderTraversal(root_);
    std::cout << std::endl;
  }

 private:
  struct Node {
    explicit Node(const T& value) : value{value} {}
    T value{};
    std::shared_ptr<Node> left{};
    std::shared_ptr<Node> right{};
  };

  std::shared_ptr<Node> root_{};

  void Insert(std::shared_ptr<Node>& node, const T& value);
  bool Contains(std::shared_ptr<Node>& node, const T& value);

  void BreadthFirstTraversal(std::shared_ptr<Node>& node);
  void PreOrderTraversal(std::shared_ptr<Node>& node);
  void PreOrderTraversalIterative(std::shared_ptr<Node>& node);
  void InOrderTraversal(std::shared_ptr<Node>& node);
  void InOrderTraversalIterative(std::shared_ptr<Node>& node);
  void PostOrderTraversal(std::shared_ptr<Node>& node);
};

template <typename T>
void BinaryTree<T>::Insert(std::shared_ptr<Node>& node, const T& value) {
  if (node == nullptr) {
    node = std::make_shared<Node>(value);
  } else {
    if (value <= node->value) {
      Insert(node->left, value);
    } else {
      Insert(node->right, value);
    }
  }
}
template <typename T>
bool BinaryTree<T>::Contains(std::shared_ptr<Node>& node, const T& value) {
  if (node == nullptr)
    return false;
  else if (node->value == value)
    return true;
  else {
    if (value <= node->value)
      return Contains(node->left, value);
    else
      return Contains(node->right, value);
  }
}
template <typename T>
void BinaryTree<T>::BreadthFirstTraversal(std::shared_ptr<Node>& node) {
  std::queue<std::shared_ptr<Node>> q{};
  if (node == nullptr) return;
  q.push(node);
  while (!q.empty()) {
    const auto n = q.front();
    q.pop();
    std::cout << " " << n->value;
    if (n->left) q.push(n->left);
    if (n->right) q.push(n->right);
  }
}
template <typename T>
void BinaryTree<T>::PreOrderTraversal(std::shared_ptr<Node>& node) {
  if (node == nullptr) return;
  std::cout << " " << node->value;
  PreOrderTraversal(node->left);
  PreOrderTraversal(node->right);
}
template <typename T>
void BinaryTree<T>::PreOrderTraversalIterative(std::shared_ptr<Node>& node) {
  if (node == nullptr) return;
  std::stack<std::shared_ptr<Node>> s{};
  s.emplace(node);
  while (!s.empty()) {
    const auto n = s.top();
    s.pop();
    std::cout << " " << n->value;
    if (n->right) s.emplace(n->right);
    if (n->left) s.emplace(n->left);
  }
}
template <typename T>
void BinaryTree<T>::InOrderTraversal(std::shared_ptr<Node>& node) {
  if (node == nullptr) return;
  InOrderTraversal(node->left);
  std::cout << " " << node->value;
  InOrderTraversal(node->right);
}
template <typename T>
void BinaryTree<T>::InOrderTraversalIterative(std::shared_ptr<Node>& node) {
  if (node == nullptr) return;
  std::stack<std::shared_ptr<Node>> s{};
  auto n = node;
  while (!s.empty() || n != nullptr) {
    while (n != nullptr) {
      s.emplace(n);
      n = n->left;
    }
    n = s.top();
    s.pop();
    std::cout << " " << n->value;
    n = n->right;
  }
}
template <typename T>
void BinaryTree<T>::PostOrderTraversal(std::shared_ptr<Node>& node) {
  if (node == nullptr) return;
  PostOrderTraversal(node->left);
  PostOrderTraversal(node->right);
  std::cout << " " << node->value;
}

#endif  // CPP_BINARY_TREE_H
