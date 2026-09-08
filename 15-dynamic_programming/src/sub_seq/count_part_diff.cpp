#include "sub_seq.hpp"
#include <numeric>

int CountPartitionsDiff::recursion(std::vector<int>& arr, int d)
{
	int sum = std::reduce(arr.begin(), arr.end());
	if ((sum + d) % 2 != 0 || d > sum)
		return 0;
	int k = (sum + d) / 2;
	return CountSubsetSumK::recursion(arr, k);
}

int CountPartitionsDiff::memoization(std::vector<int>& arr, int d)
{
	return 0;
}

int CountPartitionsDiff ::tabulation(std::vector<int>& arr, int d)
{
	return 0;
}

void CountPartitionsDiff::test(T_USED t_used)
{
	// std::vector<int> arr = {1, 2, 2, 3};
	std::vector<int> arr = {1, 1, 2, 3};
	int k = 1;
	int res = 0;
	std::cout << "Technique used : " << t_used << std::endl;
	switch (t_used) {
	case T_USED::RECURSION:
		res = CountPartitionsDiff::recursion(arr, k);
		break;
	case T_USED::RECURSION_MEMO:
		res = CountPartitionsDiff::memoization(arr, k);
		break;
	case T_USED::TABULATION:
		res = CountPartitionsDiff::tabulation(arr, k);
		break;
	}
	std::cout << "Result : " << res << std::endl;
}
