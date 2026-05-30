#include "1d.hpp"
#include <algorithm>
#include <cstdint>
#include <cstdlib>
#include <unordered_map>
#include <vector>

using Um = std::unordered_map<int, int>;
int recursive(int ind, std::vector<int>& height, Um& dp)
{
	if (ind == 0)
		return 0;
	if (dp.contains(ind))
		return dp[ind];
	int left = recursive(ind - 1, height, dp) + abs(height[ind] - height[ind - 1]);
	int right = INTMAX_MAX;
	if (ind > 1)
		right = recursive(ind - 2, height, dp) + abs(height[ind] - height[ind - 2]);
	return dp[ind] = std::min(left, right);
}

int frog_jump_recursion(std::vector<int>& height)
{
	Um dp;
	return recursive(height.size() - 1, height, dp);
}

int tabulation(std::vector<int>& height, Um& dp)
{
	dp[0] = 0;
	for (int i = 1; i < height.size(); i++) {
		int fs = dp[i - 1] + abs(height[i] - height[i - 1]);
		int ss = INTMAX_MAX;
		if (i > 1)
			ss = dp[i - 2] + abs(height[i] - height[i - 2]);
		dp[i] = std::min(fs, ss);
	}
	return dp[height.size() - 1];
}

int frog_jump_tabulation(std::vector<int>& height)
{
	Um dp;
	return tabulation(height, dp);
}
