
#include "lis.hpp"
#include <algorithm>
#include <iostream>
long NumberOfLis::tabulation(std::vector<int>& arr)
{
	int N = arr.size();
	std::vector<long> dp(N, 1), cnt(N, 1);

	long maxi = 1;
	for (int i = 0; i < N; i++) {
		for (int prev = 0; prev < i; prev++) {
			if (arr[prev] < arr[i]) {
				if (dp[i] < 1 + dp[prev]) {
					dp[i] = 1 + dp[prev];
					// inherit
					cnt[i] = cnt[prev];
				} else if (dp[i] == 1 + dp[prev]) {
					// increase count
					cnt[i] += cnt[prev];
				}
			}
		}
		maxi = std::max(maxi, dp[i]);
	}

	long nos = 0;
	for (int i = 0; i < N; i++) {
		if (maxi == dp[i])
			nos += cnt[i];
	}
	// std::cout << "DP : " << dp << std::endl;
	// std::cout << "COUNT : " << cnt << std::endl;
	return nos;
}

void NumberOfLis::test()
{
	std::vector<int> v = {10, 9, 2, 5, 3, 7, 101, 18};
	long res = 0;

	std::cout << "Problem : Number of Lis" << std::endl;
	std::cout << "Arr : " << v << std::endl;
	res = NumberOfLis::tabulation(v);
	std::cout << "Result : " << res << std::endl;
}
