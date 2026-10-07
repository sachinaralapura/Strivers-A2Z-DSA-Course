#include "dpstrings.hpp"
#include "utils.hpp"
#include <algorithm>
#include <cstddef>
#include <string>

using DP = Vecvec<long>;

static long recursion(int ind1, int ind2, const std::string& str1, const std::string& str2)
{
	if (ind1 < 0 || ind2 < 0)
		return 0;
	if (str1[ind1] == str2[ind2]) {
		return 1 + recursion(ind1 - 1, ind2 - 1, str1, str2);
	}
	return std::max(recursion(ind1 - 1, ind2, str1, str2), recursion(ind1, ind2 - 1, str1, str2));
}

static long memoization(int ind1, int ind2, const std::string& str1, const std::string& str2,
						DP& dp)
{
	if (ind1 < 0 || ind2 < 0)
		return 0;
	if (dp[ind1][ind2] != -1)
		return dp[ind1][ind2];
	if (str1[ind1] == str2[ind2]) {
		return 1 + memoization(ind1 - 1, ind2 - 1, str1, str2, dp);
	}
	return std::max(memoization(ind1 - 1, ind2, str1, str2, dp),
					memoization(ind1, ind2 - 1, str1, str2, dp));
}

long LongCommonSubSeq::recursion(const std::string& str1, const std::string& str2)
{
	size_t N = str1.size();
	size_t M = str2.size();
	return ::recursion(N - 1, M - 1, str1, str2);
}

long LongCommonSubSeq::memoization(const std::string& str1, const std::string& str2)
{
	size_t N = str1.size();
	size_t M = str2.size();
	DP dp(N, std::vector<long>(M, -1));
	return ::memoization(N - 1, M - 1, str1, str2, dp);
}

long LongCommonSubSeq::tabulation(const std::string& str1, const std::string& str2)
{
	size_t N = str1.size();
	size_t M = str2.size();
	DP dp(N + 1, std::vector<long>(M + 1, 0));

	for (size_t i = 1; i <= N; i++) {
		for (size_t j = 1; j <= M; j++) {
			if (str1[i - 1] == str2[j - 1]) {
				dp[i][j] = 1 + dp[i - 1][j - 1];
				continue;
			}
			dp[i][j] = std::max(dp[i - 1][j], dp[i][j - 1]);
		}
	}
	// std::cout << dp << std::endl;
	return dp[N][M];
}

void LongCommonSubSeq::test(T_USED t_used)
{
	// std::string str1("bdefg");
	// std::string str2("bfg");

	// std::string str1("mnop");
	// std::string str2("mnq");

	std::string str1("abc");
	std::string str2("dafb");
	long res = 0;

	std::cout << "Problem : Longest common subsequence" << std::endl;
	std::cout << "Technique used : " << t_used << std::endl;
	std::cout << "String 1 : " << str1 << std::endl;
	std::cout << "String 2 : " << str2 << std::endl;

	switch (t_used) {
	case T_USED::RECURSION:
		res = LongCommonSubSeq::recursion(str1, str2);
		break;
	case T_USED::RECURSION_MEMO:
		res = LongCommonSubSeq::memoization(str1, str2);
		break;
	case T_USED::TABULATION:
		res = LongCommonSubSeq::tabulation(str1, str2);
		break;
	default:
		break;
	}
	std::cout << "Result : " << res << std::endl;
}
