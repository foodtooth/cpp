#include "variance/variance.hpp"

#include "gmock/gmock.h"
#include "gtest/gtest.h"

class VarianceTest : public ::testing::Test {
 protected:
  VarianceTest() {}
  ~VarianceTest() override {}
  void SetUp() override {}
  void TearDown() override {}

  Variance var1_, var2_;
  std::vector<double> vec1_, vec2_;
};

TEST_F(VarianceTest, ZeroInput) {
  var1_.calculate();
  EXPECT_DOUBLE_EQ(var1_.getVariance(), 0)
      << "Variance calculation with default value 0 is wrong";

  vec1_.push_back(1);
  vec1_.push_back(2);
  vec1_.push_back(3);
  vec1_.push_back(4);
  vec1_.push_back(5);
  vec2_.push_back(6);
  vec2_.push_back(7);
  var1_.setCurData(vec1_);
  EXPECT_DOUBLE_EQ(var1_.getVariance(), 2);
  var1_.setCurData(vec2_);
  EXPECT_DOUBLE_EQ(var1_.getVariance(), 4);
  vec1_.insert(vec1_.end(), vec2_.begin(), vec2_.end());
  var2_.setCurData(vec1_);
  var2_.present();
  EXPECT_DOUBLE_EQ(var1_.getVariance(), var2_.getVariance());
}

TEST_F(VarianceTest, PieceMode) {}
