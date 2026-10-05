#include "lis.hpp"
#include <algorithm>
#include <cstddef>
#include <string>

static bool isPredecessor(const std::string& word, const std::string& prev)
{
	size_t N = word.size();
	size_t M = prev.size();
	if (N != M + 1)
		return false;

	size_t i = 0;
	size_t j = 0;

	while (i < N && j < M) {
		if (word[i] == prev[j]) {
			j++;
		}
		i++;
	}
	if (j == M)
		return true;
	return false;
}

void LongStringChain::tabulation(std::vector<std::string>& arr, std::vector<std::string>& res)
{
	int N = arr.size();
	std::sort(arr.begin(), arr.end());
	std::vector<long> dp(N, 1);
	std::vector<long> bt(N, 0);
	int maxi = 0;
	int maxInd = 0;

	for (int i = 0; i < N; i++) {
		bt[i] = i;
		for (int prev = 0; prev < i; prev++) {
			if (isPredecessor(arr[i], arr[prev]) && dp[i] < 1 + dp[prev]) {
				dp[i] = 1 + dp[prev];
				bt[i] = prev;
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

void LongStringChain::test()
{
	std::vector<std::string> v = {"a", "aa", "aaa", "aaaa", "b", "bb", "bbb"};
	std::vector<std::string> res;

	std::cout << "Problem : Longest string chain" << std::endl;
	std::cout << "Arr : " << v << std::endl;

	LongStringChain::tabulation(v, res);
	while (!res.empty()) {
		std::cout << res.back() << std::endl;
		res.pop_back();
	}
}
