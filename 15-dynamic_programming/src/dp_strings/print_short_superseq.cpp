#include "dpstrings.hpp"
#include "utils.hpp"
#include <algorithm>

using DP = Vecvec<long>;
std::string PrintShortestSuperSeq::tabulation(const std::string& str1, const std::string& str2)
{
	size_t N = str1.size();
	size_t M = str2.size();
	std::string res;

	DP dp(N + 1, std::vector<long>(M + 1, 0));

	for (size_t i = 1; i <= N; i++) {
		for (size_t j = 1; j <= M; j++) {
			if (str1[i - 1] == str2[j - 1]) {
				dp[i][j] = 1 + dp[i - 1][j - 1];
			} else {
				dp[i][j] = std::max(dp[i][j - 1], dp[i - 1][j]);
			}
		}
	}

	size_t i = N + 1;
	size_t j = M + 1;
	while (i > 0 && j > 0) {
		if (str1[i - 1] == str2[j - 1]) {
			res += str1[i - 1];
			i -= 1;
			j -= 1;
		} else if (dp[i - 1][j] > dp[i][j - 1]) {
			res += str1[i - 1];
			i--;
		} else {
			res += str2[j - 1];
			j--;
		}
	}

	while (i > 0) {
		res += str1[i - 1];
		i--;
	}

	while (j > 0) {
		res += str2[j - 1];
		j--;
	}
	std::reverse(res.begin(), res.end());
	return res;
}

void PrintShortestSuperSeq::test()
{
	// std::string str1("dynamic");
	// std::string str2("program");

	std::string str1("ALGORITHM");
	std::string str2("LOGARITHM");

	std::cout << "String 1 : " << str1 << std::endl;
	std::cout << "string 2 : " << str2 << std::endl;

	std::cout << PrintShortestSuperSeq::tabulation(str1, str2) << std::endl;
}
