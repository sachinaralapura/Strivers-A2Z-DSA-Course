#include "sub_seq.hpp"
#include <algorithm>
#include <cassert>
#include <climits>
#include <vector>

using Dp = Vecvec<int>;
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

int recursion_memo(std::vector<int>& arr, int ind, int k, Dp& dp)
{
	// base cases
	if (ind == 0) {
		if (k % arr[ind] == 0)
			return k / arr[ind];
		else
			return INT_MAX;
	}

	if (dp[ind][k] != -1)
		return dp[ind][k];

	int not_take = 0 + recursion(arr, ind - 1, k);
	int take = INT_MAX;
	if (k >= arr[ind])
		take = 1 + recursion(arr, ind, k - arr[ind]);
	return dp[ind][k] = std::min(take, not_take);
}

int MinimunCoins::memoization(std::vector<int>& arr, int k)
{
	int n = arr.size();
	Dp dp(arr.size(), std::vector<int>(k + 1, -1));
	return recursion_memo(arr, n - 1, k, dp);
}

int MinimunCoins::tabulation(std::vector<int>& arr, int k)
{
	int n = arr.size();
	Dp dp(arr.size(), std::vector<int>(k + 1, -1));

	for (int i = 0; i <= k; i++) {
		if (k % arr[0] == 0)
			dp[0][i] = i / arr[0];
		else
			dp[0][i] = INT_MAX;
	}

	for (int i = 1; i < n; i++) {
		for (int j = 0; j <= k; j++) {
			int not_take = 0 + dp[i - 1][j];
			int take = INT_MAX;
			if (j >= arr[i])
				take = 1 + dp[i][j - arr[i]];
			dp[i][j] = std::min(take, not_take);
		}
	}
	int ans = dp[n - 1][k];
	if (ans >= INT_MAX)
		return -1;
	return ans;
}

void MinimunCoins::test(T_USED t_used)
{
	std::vector<int> arr = {1, 2, 5};
	int k = 11;
	int res = 0;
	std::cout << "Technique used : " << t_used << std::endl;
	switch (t_used) {
	case T_USED::RECURSION:
		res = MinimunCoins::recursion(arr, k);
		break;
	case T_USED::RECURSION_MEMO:
		res = MinimunCoins::memoization(arr, k);
		break;
	case T_USED::TABULATION:
		res = MinimunCoins::tabulation(arr, k);
		break;
	}
	assert(res == 3);
	std::cout << "Result : " << res << std::endl;
}
