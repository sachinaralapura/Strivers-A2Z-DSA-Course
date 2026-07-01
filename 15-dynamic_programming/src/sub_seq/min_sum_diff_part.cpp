#include "sub_seq.hpp"
#include <climits>
#include <cmath>
#include <cstdlib>
#include <numeric>

using Dp = Vecvec<bool>;

long long MinSumDiffPartition::tabulation(std::vector<int>& arr)
{
	int n = arr.size();
	long long sum = std::reduce(arr.begin(), arr.end(), 0LL);
	long long k = sum / 2;

	int rows = arr.size() + 1; // 10^3 + 1
	int cols = k + 1;

	Dp dp(rows, std::vector<bool>(cols, false));
	// base case
	for (int i = 0; i < n; i++)
		dp[i][0] = true;
	dp[0][arr[0]] = true;
	for (int i = 1; i < n; i++) {
		for (int target = 1; target <= k; target++) {
			bool not_taken = dp[i - 1][target];
			bool taken = false;
			if (arr[i] <= target)
				taken = dp[i - 1][target - arr[i]];
			dp[i][target] = (not_taken || taken);
		}
	}

	long long mini = INT_MAX;
	for (int i = cols - 1; i >= 0; i--) {
		if (dp[n - 1][i] == true) {
			long long s1 = i;
			long long s2 = sum - i;
			mini = std::min(mini, std::abs(s1 - s2));
		}
	}
	return mini;
}

void MinSumDiffPartition::test(T_USED t_used)
{
	// std::vector<int> arr = {4, 3, 5, 2};
	std::vector<int> arr = {8, 6, 5};

	long long res = false;
	switch (t_used) {
	case T_USED::RECURSION:
		// res = MinSumDiffPartition::recursion(arr, k);
		std::cout << "NO IMPLEMENTATION";
		exit(-1);
		break;
	case T_USED::RECURSION_MEMO:
		// res = MinSumDiffPartition::memoization(arr, k);
		std::cout << "NO IMPLEMENTATION";
		exit(-1);
		break;
	case T_USED::TABULATION:
		res = MinSumDiffPartition::tabulation(arr);
		break;
	}
	std::cout << "Result : " << res << std::endl;
}
