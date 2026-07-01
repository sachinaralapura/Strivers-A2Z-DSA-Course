#include "utils.hpp"
#include <vector>

// We are given an array ‘ARR’ with N positive integers. We need to find if there is a subset in
// “ARR” with a sum equal to K. If there is, return true else return false. A subset/subsequence is
// a contiguous or non-contiguous part of an array, where elements appear in the same order as the
// original array. For example, for the array: [2,3,1] , the subsequences will be
// [{2},{3},{1},{2,3},{2,1},{3,1},{2,3,1} } but{3, 2} is not a subsequence because its elements are
// not in the same order as the original array.
namespace SubsetKSum
{
	bool recursion(std::vector<int>& arr, int k);
	bool memoization(std::vector<int>& arr, int k);
	bool tabulation(std::vector<int>& arr, int k);
	void test(T_USED);
} // namespace SubsetKSum

// Given an array arr of n integers, return true if the array can be partitioned into two subsets
// such that the sum of elements in both subsets is equal else return false.
namespace EqualSubsetSum
{
	bool recursion(std::vector<int>& arr);
	bool memoization(std::vector<int>& arr);
	bool tabulation(std::vector<int>& arr);
	void test(T_USED);
} // namespace EqualSubsetSum

// Given an array of n integers, partition the array into two
// subsets such that the absolute difference between their sums is minimized.
namespace MinSumDiffPartition
{
	// bool recursion(std::vector<int>& arr);
	// bool memoization(std::vector<int>& arr);
	long long tabulation(std::vector<int>& arr);
	void test(T_USED);
} // namespace MinSumDiffPartition

namespace CountSubsetSumK
{
	int recursion(std::vector<int>& arr, int k);
	int memoization(std::vector<int>& arr, int k);
	int tabulation(std::vector<int>& arr, int k);
	void test(T_USED);
} // namespace CountSubsetSumK
