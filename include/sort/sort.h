//
// Created by dx on 7/27/20.
//

#ifndef CPP_SORT_SORT_H
#define CPP_SORT_SORT_H

#include <algorithm>
#include <functional>
#include <iterator>

namespace cpp::sort {
/*
 * 1. Running time is insensitive to input. Do not take advantage of initial
 * order in the input.
 * 2. Data movement is minimal.
 */
template <typename FwdIt, typename Compare = std::less<>>
void SelectionSort(FwdIt first, FwdIt last, Compare comp = Compare{}) {
  for (auto it = first; it != last; ++it) {
    std::iter_swap(it, std::min_element(it, last, comp));
  }
}

/*
 * Fit when the data is nearly sorted (because it is adaptive) or when the
 * problem size is small (because it has low overhead)
 */
template <typename FwdIt, typename Compare = std::less<>>
void InsertionSort(FwdIt first, FwdIt last, Compare comp = Compare{}) {
  for (auto it = first; it != last; ++it) {
    std::rotate(std::upper_bound(first, it, *it, comp), it, std::next(it));
  }
}

/*
 * The only stable $O(N log N)$ sorting algorithm. MergeSort is an
 * asymptotically optimal compare-based sorting algorithm
 *
 * Possible improvements:
 * 1. Use insertion sort for small subarrays
 * 2. Test whether the array is already in order to avoid `merge()`
 * 3. MergeSort is not optimal with respect to space usage
 * 4. Operations other than compares (such as array accesses) may be important
 * 4. One can sort certain data without using any compares
 * 5. Maybe try bottom-up MergeSort
 */
template <typename BidirIt, typename Compare = std::less<>>
void MergeSort(BidirIt first, BidirIt last, Compare comp = Compare{}) {
  if (last - first > 1) {
    auto const middle = first + (last - first) / 2;
    MergeSort(first, middle, comp);
    MergeSort(middle, last, comp);
    std::inplace_merge(first, middle, last);
  }
}

/*
 * Robust and $O(N log N)$ complexity. Excellent general-purpose sort.
 *
 * Possible improvements:
 * 1. Cutoff to insertion sort
 * 2. Median-of-three (sample items) partitioning
 * 3. Shuffle data at first
 */
template <typename FwdIt, typename Compare = std::less<>>
void QuickSort(FwdIt first, FwdIt last, Compare comp = Compare{}) {
  auto const N = std::distance(first, last);
  if (N <= 1) return;
  auto const pivot = *std::next(first, N / 2);
  auto const middle1 = std::partition(
      first, last,
      [pivot, comp](auto const &elem) { return comp(elem, pivot); });
  auto const middle2 = std::partition(
      middle1, last,
      [pivot, comp](auto const &elem) { return !comp(pivot, elem); });
  QuickSort(first, middle1, comp);
  QuickSort(middle2, last, comp);
}
}  // namespace cpp::sort

#endif  // CPP_SORT_SORT_H
