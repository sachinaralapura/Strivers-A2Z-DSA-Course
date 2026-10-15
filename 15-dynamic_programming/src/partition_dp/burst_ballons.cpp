#include "partition_dp.hpp"
#include "utils.hpp"

using DP = Vecvec<long>;

long recursion(long i, long j, std::vector<long>& arr)
{
	if (i > j)
		return 0;
	long res = 0;
	long n = arr.size() - 1;
	for (long k = i; k <= j; k++) {
		long left = i <= 0 ? 1 : arr[i - 1];
		long right = j >= n ? 1 : arr[j + 1];
		long burst = left * arr[k] * right;

		long leftRec = recursion(i, k - 1, arr);
		long rightRec = recursion(k + 1, j, arr);

		long cost = burst + leftRec + rightRec;
		res = std::max(res, cost);
	}
	return res;
}

long BurstBalloons::recursion(std::vector<long>& arr)
{
	int N = arr.size();
	return ::recursion(0, N - 1, arr);
}

long memoization(long i, long j, std::vector<long>& arr, DP& dp)
{
	if (i > j)
		return 0;
	if (dp[i][j] != -1)
		return dp[i][j];

	long res = 0;
	long n = arr.size() - 1;
	for (long k = i; k <= j; k++) {
		long left = i <= 0 ? 1 : arr[i - 1];
		long right = j >= n ? 1 : arr[j + 1];
		long burst = left * arr[k] * right;

		long leftRec = memoization(i, k - 1, arr, dp);
		long rightRec = memoization(k + 1, j, arr, dp);

		long cost = burst + leftRec + rightRec;
		res = std::max(res, cost);
	}
	return dp[i][j] = res;
}

long BurstBalloons::memoization(std::vector<long>& arr)
{
	int N = arr.size();
	DP dp(N + 1, std::vector<long>(N + 1, -1));
	return ::memoization(0, N - 1, arr, dp);
}

long BurstBalloons::tabulation(std::vector<long>& arr)
{
	int N = arr.size();
	DP dp(N + 1, std::vector<long>(N + 1, 0));
	for (int i = N - 1; i >= 0; i--) {
		for (int j = i; j <= N - 1; j++) {
			long res = 0;
			for (long k = i; k <= j; k++) {
				long left = i <= 0 ? 1 : arr[i - 1];
				long right = j >= N - 1 ? 1 : arr[j + 1];
				long burst = left * arr[k] * right;

				long leftRec = k > i ? dp[i][k - 1] : 0;
				long rightRec = k < j ? dp[k + 1][j] : 0;

				long cost = burst + leftRec + rightRec;
				res = std::max(res, cost);
			}
			dp[i][j] = res;
		}
	}
	return dp[0][N - 1];
}

void BurstBalloons::test(T_USED t_used)
{
	long res = 0;
	// std::vector<long> arr = {10, 15, 20, 25};
	std::vector<long> arr = {3, 1, 5, 8};

	res = BurstBalloons::recursion(arr);
	std::cout << "Problem : Burst Ballons " << std::endl;
	std::cout << "Technique used : " << t_used << std::endl;
	std::cout << "Array " << arr << std::endl;

	switch (t_used) {
	case T_USED::RECURSION:
		res = BurstBalloons::recursion(arr);
		break;
	case T_USED::RECURSION_MEMO:
		res = BurstBalloons::memoization(arr);
		break;
	case T_USED::TABULATION:
		res = BurstBalloons::tabulation(arr);
		break;
	default:
		break;
	}
	std::cout << "Result : " << res << std::endl;
}
