#include "variance/variance.hpp"
#include <algorithm>
#include <cmath>
#include <iostream>
#include <numeric>
#include <vector>

Variance::Variance(decltype(cur_data) init_data)
    : Variance::Variance() {
  Variance::setCurData(init_data);
}
Variance::~Variance() {
}

template<typename T>
std::vector<T> operator+(const std::vector<T> &A, const std::vector<T> &B) {
  std::vector<T> AB;
  AB.reserve(A.size() + B.size());          // preallocate memory
  AB.insert(AB.end(), A.begin(), A.end());  // add A;
  AB.insert(AB.end(), B.begin(), B.end());  // add B;
  return AB;
}

template<typename T>
std::vector<T> &operator+=(std::vector<T> &A, const std::vector<T> &B) {
  A.reserve(A.size() + B.size());  // preallocate memory without erase original data
  A.insert(A.end(), B.begin(), B.end());  // add B;
  return A;                               // here A could be named AB
}

void Variance::setCurData(decltype(cur_data) data) {
  if (!cur_data.empty())
    history += cur_data;
  cur_data = data;
  cur_mean = 0;
  cur_var = 0;
  history_mean = mean;
  history_var = var;
  calculate();
}

double calMean(std::vector<double> data) {
  return std::accumulate(data.begin(), data.end(), 0.0) / data.size();
}

double calVar(std::vector<double> data, double mean) {
  std::vector<double> diff(data.size());
  std::transform(data.begin(), data.end(), diff.begin(),
                 [mean](double x) {return x - mean;});
  return std::inner_product(diff.begin(), diff.end(), diff.begin(), 0.0)
      / data.size();
}

double Variance::calculate() {
  if (!cur_data.empty()) {
    cur_mean = calMean(cur_data);
    cur_var = calVar(cur_data, cur_mean);
    if (!history.empty()) {
      mean = (history.size() * history_mean + cur_data.size() * cur_mean)
          / (history.size() + cur_data.size());
      var = (history.size() * (history_var + pow(mean - history_mean, 2))
          + cur_data.size() * (cur_var + pow(mean - cur_mean, 2)))
          / (history.size() + cur_data.size());
    } else {
      mean = cur_mean;
      var = cur_var;
    }
  }
  return var;
}

double Variance::getVariance() {
  return var;
}

void Variance::present() {
  for (double v : cur_data)
    std::cout << v << " <- cur_data" << std::endl;
  for (double v : history)
    std::cout << v << " <- history" << std::endl;
  std::cout << mean << " <- mean" << std::endl;
  std::cout << var << " <- var" << std::endl;
  std::cout << history_mean << " <- history_mean" << std::endl;
  std::cout << history_var << " <- history_var" << std::endl;
  std::cout << cur_mean << " <- cur_mean" << std::endl;
  std::cout << cur_var << " <- cur_var" << std::endl;
}
