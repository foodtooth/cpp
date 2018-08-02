#include "variance/variance.hpp"
#include <gtest/gtest.h>
#include <vector>

TEST(VarianceTest, testPieceMode) {
  Variance var1;
  var1.calculate();
  EXPECT_DOUBLE_EQ(var1.getVariance(), 0);

  std::vector<double> vec1, vec2;
  vec1.push_back(1);
  vec1.push_back(2);
  vec1.push_back(3);
  vec1.push_back(4);
  vec1.push_back(5);
  vec2.push_back(6);
  vec2.push_back(7);
  var1.setCurData(vec1);
  EXPECT_DOUBLE_EQ(var1.getVariance(), 2);
  var1.setCurData(vec2);
  EXPECT_DOUBLE_EQ(var1.getVariance(), 4);
  Variance var2;
  vec1.insert(vec1.end(), vec2.begin(), vec2.end());
  var2.setCurData(vec1);
  var2.present();
  EXPECT_DOUBLE_EQ(var1.getVariance(), var2.getVariance());
}
