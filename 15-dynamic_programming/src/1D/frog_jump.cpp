#include "1d.hpp"
#include <algorithm>
#include <climits>
#include <cstdint>
#include <cstdlib>
#include <vector>

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

int frog_jump_k_recursion(int ind, std::vector<int>& height, Um& dp, int k)
{
	if (ind == 0)
		return 0;
	if (dp.contains(ind))
		return dp[ind];

	int minJump = INT_MAX;
	for (int i = 1; i <= k; i++) {
		if ((ind - i) < 0)
			break;
		int res = frog_jump_k_recursion(ind - i, height, dp, k);
		if (res != INT_MAX) {
			int jumps = res + abs(height[ind] - height[ind - i]);
			minJump = std::min(minJump, jumps);
		}
	}
	return dp[ind] = minJump;
}

int frog_jum_K(std::vector<int>& height, int k)
{
	Um dp;
	return frog_jump_k_recursion(height.size() - 1, height, dp, k);
}
