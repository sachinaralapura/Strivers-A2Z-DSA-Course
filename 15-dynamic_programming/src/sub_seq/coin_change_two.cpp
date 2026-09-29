#include "sub_seq.hpp"

using Dp = Vecvec<long>;
static long recursion(int ind, std::vector<int>& arr, int k)
{
	if (ind == 0) {
		if (k % arr[0] == 0)
			return 1;
		else
			return 0;
	}

	if (k == 0)
		return 1;

	long not_take = recursion(ind - 1, arr, k);
	long take = 0;
	if (k >= arr[ind])
		take = recursion(ind, arr, k - arr[ind]);
	return not_take + take;
}

long CoinChangeTwo::recursion(std::vector<int>& arr, int k)
{
	int n = arr.size();
	return ::recursion(n - 1, arr, k);
}

static long memoization(int ind, std::vector<int>& arr, int k, Dp& dp)
{
	if (ind == 0) {
		if (k % arr[0] == 0)
			return 1;
		else
			return 0;
	}
	if (dp[ind][k] != -1)
		return dp[ind][k];

	if (k == 0)
		return 1;

	long not_take = memoization(ind - 1, arr, k, dp);
	long take = 0;
	if (k >= arr[ind])
		take = memoization(ind, arr, k - arr[ind], dp);
	return dp[ind][k] = not_take + take;
}

long CoinChangeTwo::memoization(std::vector<int>& arr, int k)
{
	int n = arr.size();
	Dp dp(n, std::vector<long>(k + 1, -1));
	return ::memoization(n - 1, arr, k, dp);
}

long CoinChangeTwo::tabulation(std::vector<int>& arr, int k)
{
	int n = arr.size();
	Dp dp(n, std::vector<long>(k + 1, 0));
	for (int i = 0; i <= k; i++) {
		if (i % arr[0] == 0)
			dp[0][i] = 1;
	}
	for (int i = 0; i < n; i++)
		dp[i][0] = 1;

	for (int i = 1; i < n; i++) {
		for (int j = 1; j <= k; j++) {
			long not_take = dp[i - 1][j];
			long take = 0;
			if (j >= arr[i])
				take = dp[i][j - arr[i]];
			dp[i][j] = take + not_take;
		}
	}
	return dp[n - 1][k];
}

long CoinChangeTwo::spaceOptimization(std::vector<int>& arr, int k)
{
	int n = arr.size();
	std::vector<long> prev(k + 1, 0);
	std::vector<long> curr(k + 1, 0);

	for (int i = 0; i <= k; i++) {
		if (i % arr[0] == 0)
			prev[i] = 1;
	}

	for (int i = 1; i < n; i++) {
		for (int j = 0; j <= k; j++) {
			long not_take = prev[j];
			long take = 0;
			if (j >= arr[i])
				take = curr[j - arr[i]];
			curr[j] = take + not_take;
		}
		prev = curr;
	}
	return prev[k];
}

void CoinChangeTwo::test(T_USED t_used)
{
	std::vector<int> v = {97, 40, 4,  31, 75, 87, 43, 60, 99, 27, 94, 34,
						  15, 3,  41, 95, 53, 76, 45, 12, 10, 73, 38, 5};
	int k = 789;
	long res = 0;
	std::cout << "Problem : Coin change two" << std::endl;
	std::cout << "Technique used : " << t_used << std::endl;

	switch (t_used) {
	case T_USED::RECURSION:
		res = CoinChangeTwo::recursion(v, k);
		break;
	case T_USED::RECURSION_MEMO:
		res = CoinChangeTwo::memoization(v, k);
		break;
	case T_USED::TABULATION:
		res = CoinChangeTwo::tabulation(v, k);
		break;
	case T_USED::SPACEOPTIMIZATION:
		res = CoinChangeTwo::spaceOptimization(v, k);
		break;
	default:
		break;
	}
	std::cout << "Coins : " << v << std::endl;
	std::cout << "Result : " << res << std::endl;
}
