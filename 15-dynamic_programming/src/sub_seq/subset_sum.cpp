#include "sub_seq.hpp"
#include <vector>

bool subset_sum_recursion(int ind, int target, std::vector<int>& arr)
{
	if (target == 0)
		return true;
	if (ind == 0)
		return (arr[0] == target);
	bool not_taken = subset_sum_recursion(ind - 1, target, arr);
	bool taken = false;
	if (arr[ind] <= target)
		taken = subset_sum_recursion(ind - 1, target - arr[ind], arr);
	return (not_taken || taken);
}

bool SubsetKSum::recursion(std::vector<int> &arr, int k)
{
	return subset_sum_recursion(arr.size() - 1, k, arr);
}

void SubsetKSum::test(T_USED t_used)
{
	std::vector<int> arr = {4, 3, 5, 2};
	int k = 6;
	bool res = false;
	switch (t_used) {
	case T_USED::RECURSION:
		res = SubsetKSum::recursion(arr, k);
		break;
	case T_USED::RECURSION_MEMO:
		// res = GridUniquePathTwo::memoization(n, m, deadcell);
		break;
	case T_USED::TABULATION:
		// res = GridUniquePathTwo::tabulation(n, m, deadcell);
		break;
	}
	if (res)
		std::cout << "TRUE" << std::endl;
	else
		std::cout << "FALSE" << std::endl;
}
