#include "lis.hpp"
#include <algorithm>
long LongBitonicSubseq::tabulation(std::vector<int>& arr)
{
	int N = arr.size();
	std::vector<long> dp1(N, 1);
	std::vector<long> dp2(N, 1);

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < i; j++)
			if (arr[i] > arr[j] && dp1[i] < 1 + dp1[j])
				dp1[i] = 1 + dp1[j];
	}

	for (int i = N - 1; i >= 0; i--) {
		for (int j = N - 1; j > i; j--)
			if (arr[i] > arr[j] && dp2[i] < 1 + dp2[j])
				dp2[i] = 1 + dp2[j];
	}

	long maxi = 0;
	for (int i = 0; i < N; i++)
		maxi = std::max(maxi, dp1[i] + dp2[i] - 1);
	return maxi;
}

void LongBitonicSubseq::test()
{
	// std::vector<int> v = {5, 1, 4, 2, 3, 6, 8, 7};
	// std::vector<int> v = {10, 20, 30, 40, 50, 40, 30, 20};
	std::vector<int> v = {12, 11, 10, 15, 18, 17, 16, 14};
	long res = 0;
	std::cout << "Problem : Longest Bitonic subsequence" << std::endl;
	std::cout << "Arr : " << v << std::endl;
	res = LongBitonicSubseq::tabulation(v);
	std::cout << "Result : " << res << std::endl;
}
