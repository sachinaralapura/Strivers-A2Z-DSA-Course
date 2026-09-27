#include "sub_seq.hpp"
#include <numeric>

static int getK(std::vector<int>& arr, int d)
{
	int sum = std::reduce(arr.begin(), arr.end());
	if ((sum - d) % 2 != 0 || d > sum || (sum - d) < 0)
		return 0;
	return (sum - d) / 2;
}

int TargetSum::recursion(std::vector<int>& arr, int d)
{
	int k = getK(arr, d);
	if (k > 0)
		CountSubsetSumK::recursion(arr, k);
	return 0;
}

int TargetSum::memoization(std::vector<int>& arr, int d)
{
	int k = getK(arr, d);
	if (k > 0)
		CountSubsetSumK::memoization(arr, k);
	return 0;
}

int TargetSum::tabulation(std::vector<int>& arr, int d)
{
	int k = getK(arr, d);
	if (k > 0)
		CountSubsetSumK::tabulation(arr, k);
	return 0;
}
