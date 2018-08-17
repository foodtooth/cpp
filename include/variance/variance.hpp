#ifndef VARIANCE_HPP
#define VARIANCE_HPP

#include <vector>

class Variance {
 private:
  std::vector<double> cur_data;
  std::vector<double> history;
  double mean, var, history_mean, history_var, cur_mean, cur_var;

 public:
  Variance()
      : cur_data({}),
        history({}),
        mean(0),
        var(0),
        history_mean(0),
        history_var(0),
        cur_mean(0),
        cur_var(0) {}
  Variance(decltype(cur_data) init_data);
  ~Variance();
  double calculate();
  void setCurData(decltype(cur_data) data);
  decltype(cur_data) getCurData();
  double getVariance();
  void present();
};

#endif  // VARIANCE_HPP
