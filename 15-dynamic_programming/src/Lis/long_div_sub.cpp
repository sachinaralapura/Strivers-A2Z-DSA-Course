#include "lis.hpp"
#include <algorithm>

void LongDivSubseq::tabulation(std::vector<int>& arr, std::vector<int>& res)
{
	int N = arr.size();
	std::sort(arr.begin(), arr.end());
	std::vector<long> dp(N, 1);
	std::vector<int> bt(N);
	long maxi = 1;
	int maxInd = 0;

	for (int i = 0; i < N; i++) {
		bt[i] = i;
		for (int j = 0; j < i; j++) {
			if ((arr[i] % arr[j]) == 0 && dp[i] < 1 + dp[j]) {
				dp[i] = 1 + dp[j];
				bt[i] = j;
			}
		}
		if (maxi < dp[i]) {
			maxi = dp[i];
			maxInd = i;
		}
	}

	res.push_back(arr[maxInd]);
	while (maxInd != bt[maxInd]) {
		maxInd = bt[maxInd];
		res.push_back(arr[maxInd]);
	}
}

void LongDivSubseq::test()
{
	std::vector<int> v = {7, 14, 28, 3};
	// std::vector<int> v = {16, 8, 2, 4, 32};
	// std::vector<int> v = {3, 5, 10, 20};
	std::vector<int> res;

	std::cout << "Problem : Longest Divisible Subset" << std::endl;
	std::cout << "Arr : " << v << std::endl;
	LongDivSubseq::tabulation(v, res);
	while (!res.empty()) {
		std::cout << res.back() << std::endl;
		res.pop_back();
	}
}
