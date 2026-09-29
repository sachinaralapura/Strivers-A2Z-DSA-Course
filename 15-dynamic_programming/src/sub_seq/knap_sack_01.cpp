#include "sub_seq.hpp"
#include "utils.hpp"
#include <algorithm>
#include <climits>

static int recursion(int ind, std::vector<int>& v, std::vector<int>& w, int k)
{
	if (ind == 0) {
		if (w[0] <= k)
			return v[0];
		else
			return 0;
	}

	int not_take = 0 + recursion(ind - 1, v, w, k);
	int take = INT_MIN;
	if (w[ind] <= k)
		take = v[ind] + recursion(ind - 1, v, w, k - w[ind]);
	return std::max(take, not_take);
}

int Knapsack01::recursion(std::vector<int>& v, std::vector<int>& w, int k)
{
	int n = v.size();
	int m = w.size();
	if (n != m)
		return -1;
	return ::recursion(n - 1, v, w, k);
}

using DP = Vecvec<int>;
static int memoization(int ind, std::vector<int>& v, std::vector<int>& w, int k, DP& dp)
{
	if (ind == 0) {
		if (w[0] <= k)
			return v[0];
		else
			return 0;
	}
	if (dp[ind][k] != -1)
		return dp[ind][k];
	int not_take = 0 + memoization(ind - 1, v, w, k, dp);
	int take = INT_MIN;
	if (w[ind] <= k)
		take = v[ind] + memoization(ind - 1, v, w, k - w[ind], dp);
	return dp[ind][k] = std::max(take, not_take);
}

int Knapsack01::memoization(std::vector<int>& v, std::vector<int>& w, int k)
{
	int n = v.size();
	int m = w.size();
	if (n != m)
		return -1;
	DP dp(n, std::vector<int>(k + 1, -1));
	return ::memoization(n - 1, v, w, k, dp);
}

int Knapsack01::tabulation(std::vector<int>& v, std::vector<int>& w, int k)
{
	int n = v.size();
	int m = w.size();
	if (n != m)
		return -1;
	DP dp(n + 1, std::vector<int>(k + 1, 0));
	for (int i = w[0]; i <= k; i++)
		dp[0][i] = v[0];
	for (int i = 1; i < n; i++) {
		for (int j = 1; j <= k; j++) {
			int not_take = dp[i - 1][j];
			int take = INT_MIN;
			if (w[i] <= j)
				take = v[i] + dp[i - 1][j - w[i]];
			dp[i][j] = std::max(take, not_take);
		}
	}
	return dp[n - 1][k];
}

int Knapsack01::spaceOptimization(std::vector<int>& v, std::vector<int>& w, int k)
{
	int n = v.size();
	int m = w.size();
	if (n != m)
		return -1;

	std::vector<int> prev(k + 1, 0);
	std::vector<int> curr(k + 1, 0);

	for (int i = w[0]; i <= k; i++)
		prev[i] = v[0];

	for (int i = 1; i < n; i++) {
		for (int W = 1; W <= k; W++) {
			int not_take = prev[W];
			int take = INT_MIN;
			if (w[i] <= W)
				take = v[i] + prev[W - w[i]];
			curr[W] = std::max(take, not_take);
		}
		prev = curr;
	}
	return prev[k];
}

int Knapsack01::spaceOptimizationTwo(std::vector<int>& v, std::vector<int>& w, int k)
{
	int n = v.size();
	int m = w.size();
	if (n != m)
		return -1;

	std::vector<int> prev(k + 1, 0);

	for (int i = w[0]; i <= k; i++)
		prev[i] = v[0];

	for (int i = 1; i < n; i++) {
		for (int W = k; W >= 0; W--) {
			int not_take = prev[W];
			int take = INT_MIN;
			if (w[i] <= W)
				take = v[i] + prev[W - w[i]];
			prev[W] = std::max(take, not_take);
		}
	}
	return prev[k];
}

void Knapsack01::test(T_USED t_used)
{
	std::vector<int> v = {
		60,
		100,
		120,
	};
	std::vector<int> w = {
		10,
		20,
		30,
	};
	int k = 50;
	int res = 0;
	std::cout << "Problem : Knapsack 0/1" << std::endl;
	std::cout << "Technique used : " << t_used << std::endl;

	switch (t_used) {
	case T_USED::RECURSION:
		res = Knapsack01::recursion(v, w, k);
		break;
	case T_USED::RECURSION_MEMO:
		res = Knapsack01::memoization(v, w, k);
		break;
	case T_USED::TABULATION:
		res = Knapsack01::tabulation(v, w, k);
		break;
	case T_USED::SPACEOPTIMIZATION:
		res = Knapsack01::spaceOptimizationTwo(v, w, k);
		break;
	default:
		break;
	}
	std::cout << "values : " << v << std::endl;
	std::cout << "Weights : " << w << std::endl;
	std::cout << "Result : " << res << std::endl;
}
