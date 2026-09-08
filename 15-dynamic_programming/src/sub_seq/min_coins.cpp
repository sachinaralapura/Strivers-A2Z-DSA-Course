#include "sub_seq.hpp"
#include <algorithm>
#include <climits>
#include <vector>

int recursion(std::vector<int>& arr, int ind, int k)
{
	// base cases
	if (ind == 0) {
		if (k % arr[ind] == 0)
			return k / arr[ind];
		else
			return INT_MAX;
	}

	int not_take = 0 + recursion(arr, ind - 1, k);
	int take = INT_MAX;
	if (k >= arr[ind])
		take = 1 + recursion(arr, ind, k - arr[ind]);
	return std::min(take, not_take);
}

int MinimunCoins::recursion(std::vector<int>& arr, int k)
{
	int n = arr.size();
	return ::recursion(arr, n - 1, k);
}

void MinimunCoins::test(T_USED t_used)
{
	// std::vector<int> arr = {1, 2, 2, 3};
	std::vector<int> arr = {1, 2, 5};
	int k = 11;
	int res = 0;
	std::cout << "Technique used : " << t_used << std::endl;
	switch (t_used) {
	case T_USED::RECURSION:
		res = MinimunCoins::recursion(arr, k);
		break;
	case T_USED::RECURSION_MEMO:
		// res = CountSubsetSumK::memoization(arr, k);
		break;
	case T_USED::TABULATION:
		// res = CountSubsetSumK::tabulation(arr, k);
		break;
	}
	std::cout << "Result : " << res << std::endl;
}
