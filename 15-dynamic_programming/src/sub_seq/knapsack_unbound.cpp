#include "sub_seq.hpp"
#include "utils.hpp"
#include <algorithm>
#include <climits>
#include <cmath>

static int recursion(int ind, std::vector<int>& v, std::vector<int>& w, int k)
{
	if (ind == 0) {
		if (k >= w[0])
			return std::floor(k / w[0]) * v[0];
		else
			return 0;
	}

	if (k == 0)
		return k;

	int not_take = 0 + recursion(ind - 1, v, w, k);
	int take = INT_MIN;
	if (w[ind] <= k)
		take = v[ind] + recursion(ind, v, w, k - w[ind]);
	return std::max(take, not_take);
}

long KnapsackUnbounded::recursion(std::vector<int>& v, std::vector<int>& w, int k)
{
	int n = v.size();
	int m = w.size();
	if (n != m)
		return -1;
	return ::recursion(n - 1, v, w, k);
}

using DP = Vecvec<long>;
static int memoization(int ind, std::vector<int>& v, std::vector<int>& w, int k, DP& dp)
{
	if (ind == 0) {
		if (k >= w[0])
			return std::floor(k / w[0]) * v[0];
		else
			return 0;
	}
	if (k == 0)
		return k;

	if (dp[ind][k] != -1)
		return dp[ind][k];
	int not_take = 0 + memoization(ind - 1, v, w, k, dp);
	int take = INT_MIN;
	if (w[ind] <= k)
		take = v[ind] + memoization(ind, v, w, k - w[ind], dp);
	return dp[ind][k] = std::max(take, not_take);
}

long KnapsackUnbounded::memoization(std::vector<int>& v, std::vector<int>& w, int k)
{
	int n = v.size();
	int m = w.size();
	if (n != m)
		return -1;
	DP dp(n, std::vector<long>(k + 1, -1));
	return ::memoization(n - 1, v, w, k, dp);
}

long KnapsackUnbounded::tabulation(std::vector<int>& v, std::vector<int>& w, int k)
{
	int n = v.size();
	int m = w.size();
	if (n != m)
		return -1;
	DP dp(n, std::vector<long>(k + 1, 0));
	for (int i = 0; i <= k; i++) {
		if (i >= w[0])
			dp[0][i] = std::floor(i / w[0]) * v[0];
	}

	for (int i = 1; i < n; i++) {
		for (int j = 0; j <= k; j++) {
			long not_take = dp[i - 1][j];
			long take = INT_MIN;
			if (w[i] <= j)
				take = v[i] + dp[i][j - w[i]];
			dp[i][j] = std::max(take, not_take);
		}
	}
	return dp[n - 1][k];
}

long KnapsackUnbounded::spaceOptimization(std::vector<int>& v, std::vector<int>& w, int k)
{
	int n = v.size();
	int m = w.size();
	if (n != m)
		return -1;
	std::vector<long> prev(k + 1, 0);
	std::vector<long> curr(k + 1, 0);

	// DP dp(n, std::vector<long>(k + 1, 0));
	for (int i = 0; i <= k; i++) {
		if (i >= w[0])
			prev[i] = std::floor(i / w[0]) * v[0];
	}

	for (int i = 1; i < n; i++) {
		for (int j = 0; j <= k; j++) {
			long not_take = prev[j];
			long take = INT_MIN;
			if (w[i] <= j)
				take = v[i] + curr[j - w[i]];
			curr[j] = std::max(take, not_take);
		}
		prev = curr;
	}
	return prev[k];
}

void KnapsackUnbounded::test(T_USED t_used)
{
	std::vector<int> v = {
		10,
		40,
		50,
		70,
	};
	std::vector<int> w = {
		1,
		3,
		4,
		5,
	};

	int k = 8;
	long res = 0;
	std::cout << "Problem : Knapsack unbounded" << std::endl;
	std::cout << "values : " << v << std::endl;
	std::cout << "Weights : " << w << std::endl;

	if (t_used == T_USED::ALL) {
		for (int i = 0; i < static_cast<int>(T_USED::ALL); i++) {
			auto type = static_cast<T_USED>(i);

			if (type != T_USED::ALL)
				std::cout << "Technique used : " << type << std::endl;

			switch (type) {
			case T_USED::RECURSION:
				res = KnapsackUnbounded::recursion(v, w, k);
				break;
			case T_USED::RECURSION_MEMO:
				res = KnapsackUnbounded::memoization(v, w, k);
				break;
			case T_USED::TABULATION:
				res = KnapsackUnbounded::tabulation(v, w, k);
				break;
			case T_USED::SPACEOPTIMIZATION:
				res = KnapsackUnbounded::spaceOptimization(v, w, k);
				break;
			case T_USED::ALL:
				break;
			default:
				break;
			}
			std::cout << "Result : " << res << std::endl;
			res = 0;
		}
		return;
	}

	std::cout << "Technique used : " << t_used << std::endl;
	switch (t_used) {
	case T_USED::RECURSION:
		res = KnapsackUnbounded::recursion(v, w, k);
		break;
	case T_USED::RECURSION_MEMO:
		res = KnapsackUnbounded::memoization(v, w, k);
		break;
	case T_USED::TABULATION:
		res = KnapsackUnbounded::tabulation(v, w, k);
		break;
	case T_USED::SPACEOPTIMIZATION:
		res = KnapsackUnbounded::spaceOptimization(v, w, k);
		break;
	default:
		break;
	}
	std::cout << "Result : " << res << std::endl;
}
