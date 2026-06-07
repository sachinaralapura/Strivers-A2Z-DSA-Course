#include "1d.hpp"
#include <algorithm>

int max_sum_recursion(int ind, std::vector<int>& a, Um& dp)
{
	if (ind == 0)
		return a[ind];
	if (ind < 0)
		return 0;
	if (dp.contains(ind))
		return dp[ind];
	int pick = a[ind] + max_sum_recursion(ind - 2, a, dp);
	int not_pick = 0 + max_sum_recursion(ind - 1, a, dp);
	return dp[ind] = std::max(pick, not_pick);
}

int max_sum_non_adjacent(std::vector<int>& a)
{
	Um dp;
	return max_sum_recursion(a.size() - 1, a, dp);
}

int max_sum_tabulated(std::vector<int>& a, bool space_optimized)
{
	if (a.empty())
		return 0;
	if (a.size() == 1)
		return a[0];
	if (space_optimized) {
		int pp = 0;
		int p = a[0];
		for (int i = 1; i < a.size(); i++) {
			int pick = a[i] + pp;
			int non_pick = 0 + p;
			int curr = std::max(pick, non_pick);
			pp = p;
			p = curr;
		}
		return p;
	}

	Um dp;
	dp[0] = a[0];
	dp[1] = std::max(a[0], a[1]);
	for (int i = 1; i < a.size(); i++) {
		int pick = a[i] + dp[i - 2];
		int non_pick = 0 + dp[i - 1];
		dp[i] = std::max(pick, non_pick);
	}
	return dp[a.size() - 1];
}
