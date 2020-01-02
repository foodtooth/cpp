//
// Created by dx on 11/7/19.
//

#ifndef CPP_TRIE_H
#define CPP_TRIE_H

#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

class Trie {
 public:
  Trie() : root_{nullptr} {}
  explicit Trie(const std::vector<std::string>& words) : root_{nullptr} {
    for (const auto& word : words) {
      Insert(word);
    }
  }
  ~Trie() = default;

  Trie(Trie const&) = default;
  Trie& operator=(Trie const&) = default;

  Trie(Trie&&) noexcept = default;
  Trie& operator=(Trie&&) noexcept = default;

  void Insert(const std::string& word) { Insert(root_, word); }
  bool Search(const std::string& word) { return Search(root_, word); }
  bool StartsWith(const std::string& prefix) {
    return StartsWith(root_, prefix);
  }

 private:
  struct Node {
    explicit Node(const bool& end_of_word) : end_of_word{end_of_word} {}
    bool end_of_word;
    std::unordered_map<char, std::shared_ptr<Node>> children{};
  };
  std::shared_ptr<Node> root_{};

  void Insert(std::shared_ptr<Node>& node, const std::string& word);
  bool Search(std::shared_ptr<Node>& node, const std::string& word);
  bool StartsWith(std::shared_ptr<Node>& node, const std::string& prefix);
};

void Trie::Insert(std::shared_ptr<Node>& node, const std::string& word) {
  if (node == nullptr) {
    node = std::make_shared<Node>(false);
  }
  auto n = node;
  for (auto c : word) {
    if (n->children[c] == nullptr) {
      n->children[c] = std::make_shared<Node>(false);
    }
    n = n->children[c];
  }
  n->end_of_word = true;
}
bool Trie::Search(std::shared_ptr<Node>& node, const std::string& word) {
  auto n = node;
  if (n == nullptr) return false;
  for (auto c : word) {
    if (n->children.find(c) != n->children.end()) {
      n = n->children[c];
    } else {
      return false;
    }
  }
  return n->end_of_word;
}
bool Trie::StartsWith(std::shared_ptr<Node>& node, const std::string& prefix) {
  auto n = node;
  if (n == nullptr) return false;
  for (auto c : prefix) {
    if (n->children.find(c) != n->children.end()) {
      n = n->children[c];
    } else {
      return false;
    }
  }
  return true;
}

#endif  // CPP_TRIE_H
