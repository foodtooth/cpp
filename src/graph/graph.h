//
// Created by dx on 11/11/19.
//

#ifndef CPP_GRAPH_H
#define CPP_GRAPH_H

#include <cstdio>
#include <utility>
#include <vector>

template <typename T>
class Graph {
 public:
  Graph() : root_{nullptr} {}
  explicit Graph(const std::vector<std::pair<T, T>>& edges) : root_{nullptr} {
    AddEdges(edges);
  }
  ~Graph() = default;

  Graph(Graph const&) = default;
  Graph& operator=(Graph const&) = default;

  Graph(Graph&&) noexcept = default;
  Graph& operator=(Graph&&) noexcept = default;

  void AddEdges(const std::vector<std::pair<T, T>>& edges) {
    for (const auto& edge : edges) {
      adj_list_[edge.first].push_back(edge.second);
      adj_list_[edge.second].push_back(edge.first);
    }
  }

  void BFS(T start) { std::vector<bool> visited(adj_list_.size(), false); }

 private:
  std::vector<std::vector<T>> adj_list_{};  // our adjacency list for the graph
};

#endif  // CPP_GRAPH_H
