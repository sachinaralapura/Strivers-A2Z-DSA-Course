#include "dpstrings.hpp"
#include "utils.hpp"
#include <algorithm>

using DP = Vecvec<long>;
long LongCommonSubStr::tabulation(const std::string& str1, const std::string& str2)
{
	size_t N = str1.size();
	size_t M = str2.size();
	DP dp(N + 1, std::vector<long>(M + 1, 0));
	long maxi = 0;

	for (size_t i = 1; i <= N; i++) {
		for (size_t j = 1; j <= M; j++) {
			if (str1[i - 1] == str2[j - 1]) {
				dp[i][j] = 1 + dp[i - 1][j - 1];
				maxi = std::max(maxi, dp[i][j]);
				continue;
			}
			dp[i][j] = 0;
		}
	}
	return maxi;
}

void LongCommonSubStr::test(T_USED t_used)
{
	// std::string str1("bdefg");
	// std::string str2("bfg");

	std::string str1("mnop");
	std::string str2("mnq");

	// std::string str1("abc");
	// std::string str2("dafb");
	long res = 0;

	std::cout << "Problem : Longest common Substring" << std::endl;
	std::cout << "Technique used : " << t_used << std::endl;
	std::cout << "String 1 : " << str1 << std::endl;
	std::cout << "String 2 : " << str2 << std::endl;

	switch (t_used) {
	case T_USED::TABULATION:
		res = LongCommonSubStr::tabulation(str1, str2);
		break;
	default:
		break;
	}
	std::cout << "Result : " << res << std::endl;
}
