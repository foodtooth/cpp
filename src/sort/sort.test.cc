//
// Created by dx on 7/28/20.
//

#include <algorithm>
#include <catch2/catch.hpp>
#include <vector>

#include "sort/sort.h"

TEST_CASE("Sorting tests", "[sort]") {
  auto data = GENERATE(chunk(100, take(100, random(-3000, 3000))));
  REQUIRE_FALSE(data.empty());
  REQUIRE_FALSE(std::is_sorted(data.begin(), data.end()));

  SECTION("Selection Sort") {
    std::vector<int> v{data};
    cpp::sort::SelectionSort(v.begin(), v.end());
    REQUIRE(std::is_sorted(v.begin(), v.end()));
  }
  SECTION("Insertion Sort") {
    std::vector<int> v{data};
    cpp::sort::InsertionSort(v.begin(), v.end());
    REQUIRE(std::is_sorted(v.begin(), v.end()));
  }
  SECTION("Merget Sort") {
    std::vector<int> v{data};
    cpp::sort::MergeSort(v.begin(), v.end());
    REQUIRE(std::is_sorted(v.begin(), v.end()));
  }
}