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
  if (!this->cur_data.empty())
    this->history += this->cur_data;
  this->cur_data = data;
  this->cur_mean = 0;
  this->cur_var = 0;
  this->history_mean = this->mean;
  this->history_var = this->var;
  this->calculate();
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
  if (!this->cur_data.empty()) {
    this->cur_mean = calMean(this->cur_data);
    this->cur_var = calVar(this->cur_data, this->cur_mean);
    if (!this->history.empty()) {
      this->mean = (this->history.size() * this->history_mean
          + this->cur_data.size() * this->cur_mean)
          / (this->history.size() + this->cur_data.size());
      this->var = (this->history.size()
          * (this->history_var + pow(this->mean - this->history_mean, 2))
          + this->cur_data.size()
              * (this->cur_var + pow(this->mean - this->cur_mean, 2)))
          / (this->history.size() + this->cur_data.size());
    } else {
      this->mean = this->cur_mean;
      this->var = this->cur_var;
    }
  }
  return this->var;
}

double Variance::getVariance() {
  return this->var;
}

void Variance::present() {
  for (double v : this->cur_data)
    std::cout << v << " <- cur_data" << std::endl;
  for (double v : this->history)
    std::cout << v << " <- history" << std::endl;
  std::cout << this->mean << " <- mean" << std::endl;
  std::cout << this->var << " <- var" << std::endl;
  std::cout << this->history_mean << " <- history_mean" << std::endl;
  std::cout << this->history_var << " <- history_var" << std::endl;
  std::cout << this->cur_mean << " <- cur_mean" << std::endl;
  std::cout << this->cur_var << " <- cur_var" << std::endl;
}
