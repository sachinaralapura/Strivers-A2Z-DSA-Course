#include "lis.hpp"
#include <iostream>

void LongIncSubseqPrint::tabulation(std::vector<int>& arr, std::vector<int>& lis)
{
	int N = arr.size();
	std::vector<long> dp(N, 1);
	std::vector<long> bt(N, 1);
	long maxi = 0;
	int maxInd = 0;

	for (int i = 0; i < N; i++) {
		bt[i] = i;
		for (int prev = 0; prev < i; prev++) {
			if (arr[prev] < arr[i]) {
				if (dp[i] < 1 + dp[prev]) {
					dp[i] = 1 + dp[prev];
					bt[i] = prev;
				}
			}
		}
		if (maxi < dp[i]) {
			maxi = dp[i];
			maxInd = i;
		}
	}

	int i = maxInd;
	lis.push_back(arr[i]);
	while (i != bt[i]) {
		i = bt[i];
		lis.push_back(arr[i]);
	}
}

void LongIncSubseqPrint::test()
{
	std::vector<int> v = {10, 9, 2, 5, 3, 7, 101, 18};
	std::vector<int> res;

	std::cout << "Problem : Longest increasion subsequence" << std::endl;
	std::cout << "Arr : " << v << std::endl;
	LongIncSubseqPrint::tabulation(v, res);
	while (!res.empty()) {
		std::cout << res.back() << std::endl;
		res.pop_back();
	}
}
