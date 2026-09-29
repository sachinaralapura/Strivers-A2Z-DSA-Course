#include "lis.hpp"
#include "utils.hpp"
#include <algorithm>
#include <climits>

using DP = Vecvec<long>;
static int N;

static long recursion(int ind, int prevInd, std::vector<int>& arr)
{
	if (ind == N)
		return 0;
	long not_take = recursion(ind + 1, ind, arr);
	long take = LONG_MIN;
	if (prevInd == -1 || arr[prevInd] < arr[ind]) {
		take = 1 + recursion(ind + 1, ind, arr);
	}
	return std::max(not_take, take);
}

static long memoization(int ind, int prevInd, std::vector<int>& arr, DP& dp)
{
	if (ind == N)
		return 0;
	if (prevInd >= 0 && dp[ind][prevInd] != -1)
		return dp[ind][prevInd];

	long not_take = memoization(ind + 1, ind, arr, dp);
	long take = LONG_MIN;
	if (prevInd == -1 || arr[prevInd] < arr[ind]) {
		take = 1 + memoization(ind + 1, ind, arr, dp);
	}
	long max_res = std::max(not_take, take);
	if (prevInd >= 0)
		return dp[ind][prevInd] = max_res;
	else
		return max_res;
}

long LongIncSubseq::recursion(std::vector<int>& arr)
{
	N = arr.size();
	return ::recursion(0, -1, arr);
}

long LongIncSubseq::memoization(std::vector<int>& arr)
{
	N = arr.size();
	DP dp(N, std::vector<long>(N, -1));
	return ::memoization(0, -1, arr, dp);
}

long LongIncSubseq::tabulation(std::vector<int>& arr)
{
	N = arr.size();
	DP dp(N + 1, std::vector<long>(N + 1, 0));

	for (int i = N - 1; i >= 0; i--) {
		for (int j = i - 1; j >= -1; j--) {
			long len = dp[i + 1][j + 1];
			if (j == -1 || arr[i] > arr[j]) {
				len = std::max(len, 1 + dp[i + 1][i + 1]);
			}
			dp[i][j + 1] = len;
		}
	}
	std::cout << dp << std::endl;
	return dp[0][0];
}

void LongIncSubseq::test(T_USED t_used)
{
	std::vector<int> v = {10, 9, 2, 5, 3, 7, 101, 18};
	// std::vector<int> v = {0, 1, 0, 3, 2, 3};

	long res = 0;
	std::cout << "Problem : Longest increasion subsequence" << std::endl;
	std::cout << "Arr : " << v << std::endl;

	if (t_used == T_USED::ALL) {
		for (int i = 0; i < static_cast<int>(T_USED::ALL); i++) {
			auto type = static_cast<T_USED>(i);

			if (type != T_USED::ALL)
				std::cout << "Technique used : " << type << std::endl;

			switch (type) {
			case T_USED::RECURSION:
				res = LongIncSubseq::recursion(v);
				break;
			case T_USED::RECURSION_MEMO:
				res = LongIncSubseq::memoization(v);
				break;
			case T_USED::TABULATION:
				res = LongIncSubseq::tabulation(v);
				break;
			case T_USED::SPACEOPTIMIZATION:
				// res = LongIncSubseq::spaceOptimization(v);
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
		res = LongIncSubseq::recursion(v);
		break;
	case T_USED::RECURSION_MEMO:
		res = LongIncSubseq::memoization(v);
		break;
	case T_USED::TABULATION:
		res = LongIncSubseq::tabulation(v);
		break;
	case T_USED::SPACEOPTIMIZATION:
		// res = LongIncSubseq::spaceOptimization(v);
		break;
	default:
		break;
	}
	std::cout << "Result : " << res << std::endl;
}
