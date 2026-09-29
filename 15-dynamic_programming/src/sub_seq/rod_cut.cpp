#include "sub_seq.hpp"
#include "utils.hpp"
#include <algorithm>
#include <climits>

using DP = Vecvec<long>;

long recursion(int ind, int k, std::vector<int>& costs)
{
	if (ind == 0)
		return costs[0] * k;
	long not_take = recursion(ind - 1, k, costs);
	long take = LONG_MIN;
	if (ind + 1 <= k)
		take = costs[ind] + recursion(ind, k - (ind + 1), costs);
	return std::max(not_take, take);
}

long memoization(int ind, int k, std::vector<int>& costs, DP& dp)
{
	if (ind == 0)
		return costs[0] * k;
	if (dp[ind][k] != -1)
		return dp[ind][k];
	long not_take = memoization(ind - 1, k, costs, dp);
	long take = LONG_MIN;
	if (ind + 1 <= k)
		take = costs[ind] + memoization(ind, k - (ind + 1), costs, dp);
	return dp[ind][k] = std::max(not_take, take);
}

long RodCut::recursion(std::vector<int>& costs, int k)
{
	int n = costs.size();
	return ::recursion(n - 1, k, costs);
}

long RodCut::memoization(std::vector<int>& costs, int k)
{
	int n = costs.size();
	DP dp(n, std::vector<long>(k + 1, -1));
	return ::memoization(n - 1, k, costs, dp);
}

long RodCut::tabulation(std::vector<int>& costs, int k)
{
	int n = costs.size();
	DP dp(n, std::vector<long>(k + 1, 0));
	for (int i = 1; i <= k; i++)
		dp[0][i] = costs[0] * i;

	for (int i = 1; i < n; i++) {
		for (int j = 1; j <= k; j++) {
			long not_take = dp[i - 1][j];
			long take = 0;
			if (i + 1 <= j)
				take = costs[i] + dp[i][j - (i + 1)];
			dp[i][j] = std::max(not_take, take);
		}
	}
	return dp[n - 1][k];
}

long RodCut::spaceOptimization(std::vector<int>& costs, int k)
{
	int n = costs.size();
	std::vector<long> prev(k + 1, 0);
	std::vector<long> curr(k + 1, 0);
	for (int i = 1; i <= k; i++)
		prev[i] = costs[0] * i;

	for (int i = 1; i < n; i++) {
		for (int j = 1; j <= k; j++) {
			long not_take = prev[j];
			long take = 0;
			if (i + 1 <= j)
				take = costs[i] + curr[j - (i + 1)];
			curr[j] = std::max(not_take, take);
		}
		prev = curr;
	}
	return prev[k];
}

void RodCut::test(T_USED t_used)
{
	std::vector<int> v = {
		5, 5, 8, 9, 10, 17, 17, 20,
	};

	int k = 8;
	long res = 0;
	std::cout << "Problem : Rod cut" << std::endl;
	std::cout << "costs : " << v << std::endl;
	std::cout << "Rod length : " << k << std::endl;

	if (t_used == T_USED::ALL) {
		for (int i = 0; i < static_cast<int>(T_USED::ALL); i++) {
			auto type = static_cast<T_USED>(i);

			if (type != T_USED::ALL)
				std::cout << "Technique used : " << type << std::endl;

			switch (type) {
			case T_USED::RECURSION:
				res = RodCut::recursion(v, k);
				break;
			case T_USED::RECURSION_MEMO:
				res = RodCut::memoization(v, k);
				break;
			case T_USED::TABULATION:
				res = RodCut::tabulation(v, k);
				break;
			case T_USED::SPACEOPTIMIZATION:
				res = RodCut::spaceOptimization(v, k);
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
		res = RodCut::recursion(v, k);
		break;
	case T_USED::RECURSION_MEMO:
		res = RodCut::memoization(v, k);
		break;
	case T_USED::TABULATION:
		res = RodCut::tabulation(v, k);
		break;
	case T_USED::SPACEOPTIMIZATION:
		res = RodCut::spaceOptimization(v, k);
		break;
	default:
		break;
	}
	std::cout << "Result : " << res << std::endl;
}
