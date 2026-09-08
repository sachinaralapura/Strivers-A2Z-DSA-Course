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

// Given an array with N positive integers and an integer D, count the number of ways we can
// partition the given array into two subsets, S1 and S2 such that S1 - S2 = D and S1 is always
// greater than or equal to S2.
namespace CountPartitionsDiff
{
	int recursion(std::vector<int>& arr, int k);
	int memoization(std::vector<int>& arr, int k);
	int tabulation(std::vector<int>& arr, int k);
	void test(T_USED);
} // namespace CountPartitionsDiff

// Consider a scenario where a teacher wants to distribute cookies to students, with each student
// receiving at most one cookie. Given two arrays, student and cookie, the ith value in the student
// array describes the minimum size of cookie that the ith student can be assigned. The jth value in
// the cookie array represents the size of the jth cookie. If cookie[j] >= student[i], the jth
// cookie can be assigned to the ith student. Maximize the number of students assigned with cookies
// and output the maximum number.
namespace AssignCookie
{
	int optimal(std::vector<int>& students, std::vector<int>& cookie);
} // namespace AssignCookie

namespace MinimunCoins
{
	int recursion(std::vector<int>& arr, int k);
	int memoization(std::vector<int>& arr, int k);
	int tabulation(std::vector<int>& arr, int k);
	void test(T_USED);

} // namespace MinimunCoins
