#include "sub_seq.hpp"

using Dp = Vecvec<int>;
int count_subset_recursion(int ind, int target, std::vector<int>& arr)
{
	if (target == 0)
		return 1;
	if (ind == 0) {
		if (arr[0] == target)
			return 1;
		return 0;
	}
	int not_taken = count_subset_recursion(ind - 1, target, arr);
	int taken = 0;
	if (arr[ind] <= target)
		taken = count_subset_recursion(ind - 1, target - arr[ind], arr);
	return not_taken + taken;
}

int CountSubsetSumK::recursion(std::vector<int>& arr, int k)
{
	return count_subset_recursion(arr.size() - 1, k, arr);
}

int count_subset_memo(int ind, int target, std::vector<int>& arr, Dp& dp)
{
	if (target == 0)
		return 1;
	if (ind == 0) {
		if (arr[0] == target)
			return 1;
		return 0;
	}
	if (dp[ind][target] != -1)
		return dp[ind][target];
	int not_taken = count_subset_recursion(ind - 1, target, arr);
	int taken = 0;
	if (arr[ind] <= target)
		taken = count_subset_recursion(ind - 1, target - arr[ind], arr);
	return dp[ind][target] = (not_taken + taken);
}
int CountSubsetSumK::memoization(std::vector<int>& arr, int k)
{
	Dp dp(arr.size(), std::vector<int>(k + 1, -1));
	return count_subset_memo(arr.size() - 1, k, arr, dp);
}

int CountSubsetSumK::tabulation(std::vector<int>& arr, int k)
{
	const int n = arr.size();
	Dp dp(n + 1, std::vector<int>(k + 1, 0));
	for (int i = 0; i < n; i++)
		dp[i][0] = 1;
	if (arr[0] <= k)
		dp[0][arr[0]] = 1;
	for (int i = 1; i < n; i++) {
		for (int j = 1; j <= k; j++) {
			int not_taken = dp[i - 1][j];
			int taken = 0;
			if (arr[i] <= j)
				taken = dp[i - 1][j - arr[i]];
			dp[i][j] = not_taken + taken;
		}
	}
	return dp[n - 1][k];
}

void CountSubsetSumK::test(T_USED t_used)
{
	// std::vector<int> arr = {1, 2, 2, 3};
	std::vector<int> arr = {1, 2, 3, 4, 5};
	int k = 5;
	int res = false;
	std::cout << "Technique used : " << t_used << std::endl;
	switch (t_used) {
	case T_USED::RECURSION:
		res = CountSubsetSumK::recursion(arr, k);
		break;
	case T_USED::RECURSION_MEMO:
		res = CountSubsetSumK::memoization(arr, k);
		break;
	case T_USED::TABULATION:
		res = CountSubsetSumK::tabulation(arr, k);
		break;
	}
	std::cout << "Result : " << res << std::endl;
}
