#include "sub_seq.hpp"
#include <vector>

using Dp = Vecvec<bool>;
bool subset_sum_recursion(int ind, int target, std::vector<int>& arr)
{
	if (target == 0)
		return true;
	if (ind == 0)
		return (arr[0] == target);
	bool not_taken = subset_sum_recursion(ind - 1, target, arr);
	if (not_taken)
		return not_taken;
	bool taken = false;
	if (arr[ind] <= target)
		taken = subset_sum_recursion(ind - 1, target - arr[ind], arr);
	return (not_taken || taken);
}

bool SubsetKSum::recursion(std::vector<int>& arr, int k)
{
	return subset_sum_recursion(arr.size() - 1, k, arr);
}

bool subset_sum_memo(int ind, int target, std::vector<int>& arr, Dp& dp)
{
	if (target == 0)
		return true;
	if (ind == 0)
		return (arr[0] == target);
	if (dp[ind][target])
		return true;
	bool not_taken = subset_sum_recursion(ind - 1, target, arr);
	if (not_taken)
		return not_taken;
	bool taken = false;
	if (arr[ind] <= target)
		taken = subset_sum_recursion(ind - 1, target - arr[ind], arr);
	return dp[ind][target] = (not_taken || taken);
}
bool SubsetKSum::memoization(std::vector<int>& arr, int k)
{
	size_t rows = 1001; // 10^3 + 1
	size_t cols = 1001; // 10^3 + 1
	Dp dp(rows, std::vector<bool>(cols, false));
	return subset_sum_memo(arr.size() - 1, k, arr, dp);
}

bool SubsetKSum::tabulation(std::vector<int>& arr, int k)
{
	int n = arr.size();
	size_t rows = n + 1; // 10^3 + 1
	size_t cols = k + 1; // 10^3 + 1
	Dp dp(rows, std::vector<bool>(cols, false));
	// base case
	for (int i = 0; i < n; i++)
		dp[i][0] = true;
	dp[0][arr[0]] = true;
	for (int i = 1; i < n; i++) {
		for (int target = 1; target <= k; target++) {
			bool not_taken = dp[i - 1][target];
			bool taken = false;
			if (arr[i] <= target)
				taken = dp[i - 1][target - arr[i]];
			dp[i][target] = (not_taken || taken);
		}
	}
	return dp[n - 1][k];
}

void SubsetKSum::test(T_USED t_used)
{
	std::vector<int> arr = {4, 3, 5, 2};
	int k = 13;
	bool res = false;
	switch (t_used) {
	case T_USED::RECURSION:
		res = SubsetKSum::recursion(arr, k);
		break;
	case T_USED::RECURSION_MEMO:
		res = SubsetKSum::memoization(arr, k);
		break;
	case T_USED::TABULATION:
		res = SubsetKSum::tabulation(arr, k);
		break;
	}
	if (res)
		std::cout << "TRUE" << std::endl;
	else
		std::cout << "FALSE" << std::endl;
}
