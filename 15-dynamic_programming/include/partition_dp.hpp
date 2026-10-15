#ifndef PARTITION_DP
#define PARTITION_DP

#include "utils.hpp"

namespace MatrixChainMul
{
	long recursion(std::vector<long>&);
	long memoization(std::vector<long>&);
	long tabulation(std::vector<long>&);
	void test(T_USED);
} // namespace MatrixChainMul

// Given n balloons, indexed from 0 to n - 1, each balloon is painted with a number on it
// represented by an array nums. Burst all the balloons.
// If the ith balloon is burst, the coins obtained are nums[i - 1] * nums[i] * nums[i + 1]. If i - 1
// or i + 1 goes out of bounds of the array, treat it as if there is a balloon with a 1 painted on
// it.
// Return the maximum coins that can be collected by bursting the balloons wisely.
namespace BurstBalloons
{
	long recursion(std::vector<long>&);
	long memoization(std::vector<long>&);
	long tabulation(std::vector<long>&);
	void test(T_USED);

} // namespace BurstBalloons

#endif
