#include "partition_dp.hpp"
#include "utils.hpp"
#include <climits>

using DP = Vecvec<long>;
static long recursion(size_t i, size_t j, std::vector<long>& arr)
{
	if (i == j)
		return 0;
	long min_mul = LONG_MAX;
	for (size_t k = i; k < j; k++) {
		min_mul = std::min(min_mul, (arr[i - 1] * arr[k] * arr[j]) + recursion(i, k, arr) +
										recursion(k + 1, j, arr));
	}
	return min_mul;
}

long MatrixChainMul::recursion(std::vector<long>& arr)
{
	return ::recursion(1, arr.size() - 1, arr);
}

static long memoization(size_t i, size_t j, std::vector<long>& arr, DP& dp)
{
	if (i == j)
		return 0;
	long min_mul = LONG_MAX;
	if (dp[i][j] != -1)
		return dp[i][j];
	for (size_t k = i; k < j; k++) {
		min_mul = std::min(min_mul, (arr[i - 1] * arr[k] * arr[j]) + memoization(i, k, arr, dp) +
										memoization(k + 1, j, arr, dp));
	}
	return dp[i][j] = min_mul;
}

long MatrixChainMul::memoization(std::vector<long>& arr)
{
	int N = arr.size();
	DP dp(N, std::vector<long>(N, -1));
	return ::memoization(1, arr.size() - 1, arr, dp);
}

long MatrixChainMul::tabulation(std::vector<long>& arr)
{
	int N = arr.size();
	DP dp(N, std::vector<long>(N, 0));

	for (size_t i = N - 1; i >= 1; i--) {
		for (size_t j = i + 1; j < N; j++) {
			long min_mul = LONG_MAX;
			for (size_t k = i; k < j; k++) {
				min_mul =
					std::min(min_mul, (arr[i - 1] * arr[k] * arr[j]) + dp[i][k] + dp[k + 1][j]);
			}
			dp[i][j] = min_mul;
		}
	}
	std::cout << dp << std::endl;
	return dp[1][N - 1];
}

void MatrixChainMul::test(T_USED t_used)
{
	long res = 0;
	// std::vector<long> arr = {10, 15, 20, 25};
	std::vector<long> arr = {1, 2, 3, 4, 5};
	
	res = MatrixChainMul::recursion(arr);
	std::cout << "Problem : Minimum Matrix chain multiplication " << std::endl;
	std::cout << "Technique used : " << t_used << std::endl;
	std::cout << "Array " << arr << std::endl;

	switch (t_used) {
	case T_USED::RECURSION:
		res = MatrixChainMul::recursion(arr);
		break;
	case T_USED::RECURSION_MEMO:
		res = MatrixChainMul::memoization(arr);
		break;
	case T_USED::TABULATION:
		res = MatrixChainMul::tabulation(arr);
		break;
	default:
		break;
	}

	std::cout << "Result : " << res << std::endl;
}
