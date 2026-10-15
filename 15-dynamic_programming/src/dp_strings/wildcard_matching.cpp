#include "dpstrings.hpp"
#include "utils.hpp"
#include <cstddef>

using DP = Vecvec<long>;
using DPBool = Vecvec<bool>;

static bool recursion(int i, int j, const std::string& pattern, const std::string& str)
{
	if (i < 0 && j < 0)
		return true;
	if (i < 0 && j >= 0)
		return false;
	if (j < 0 && i >= 0) {
		while (i >= 0) {
			if (pattern[i] != '*')
				return false;
			i--;
		}
		return true;
	}

	if (pattern[i] == str[j] || pattern[i] == '?') {
		return recursion(i - 1, j - 1, pattern, str);
	} else if (pattern[i] == '*') {
		return (recursion(i, j - 1, pattern, str) || recursion(i - 1, j, pattern, str));
	}
	return false;
}

static bool memoization(int i, int j, const std::string& pattern, const std::string& str, DP& dp)
{
	if (i < 0 && j < 0)
		return true;
	if (i < 0)
		return false;
	if (j < 0) {
		while (i >= 0) {
			if (pattern[i] != '*')
				return false;
			i--;
		}
		return true;
	}

	if (dp[i][j] != -1)
		return dp[i][j] ? true : false;
	if (pattern[i] == str[j] || pattern[i] == '?') {
		return dp[i][j] = memoization(i - 1, j - 1, pattern, str, dp);
	} else if (pattern[i] == '*') {
		return dp[i][j] = (memoization(i, j - 1, pattern, str, dp) ||
						   memoization(i - 1, j, pattern, str, dp));
	}
	return dp[i][j] = false;
}

bool WildcardMatching::recursion(const std::string& str1, const std::string& str2)
{
	int N = str1.size();
	int M = str2.size();
	return ::recursion(N - 1, M - 1, str1, str2);
}

bool WildcardMatching::memoization(const std::string& str1, const std::string& str2)
{
	int N = str1.size();
	int M = str2.size();
	DP dp(N + 1, std::vector<long>(M + 1, -1));
	bool res = ::memoization(N - 1, M - 1, str1, str2, dp);
	std::cout << dp << std::endl;
	return res;
}

bool WildcardMatching::tabulation(const std::string& pattern, const std::string& str)
{
	int N = pattern.size();
	int M = str.size();
	DPBool dp(N + 1, std::vector<bool>(M + 1, 0));

	dp[0][0] = true;
	// base cases
	for (size_t j = 1; j <= M; j++) {
		dp[0][j] = false;
	}
	for (size_t i = 1; i <= N; i++) {
		if (pattern[i - 1] != '*')
			break;
		dp[i][0] = true;
	}

	for (size_t i = 1; i <= N; i++) {
		for (size_t j = 1; j <= M; j++) {
			if (pattern[i - 1] == str[j - 1] || pattern[i - 1] == '?') {
				dp[i][j] = dp[i - 1][j - 1];
			} else if (pattern[i - 1] == '*') {
				dp[i][j] = (dp[i][j - 1] || dp[i - 1][j]);
			} else {
				dp[i][j] = false;
			}
		}
	}
	return dp[N][M];
}

void WildcardMatching::test(T_USED t_used)
{
	std::string str1("****x?y*z");
	std::string str2("xaylmz");
	// std::string str1("xyza");
	// std::string str2("x*z");
	bool res = 0;
	std::cout << "Problem : Wildcard matching" << std::endl;
	std::cout << "Technique used : " << t_used << std::endl;
	std::cout << "String 1 : " << str1 << std::endl;
	std::cout << "String 2 : " << str2 << std::endl;

	switch (t_used) {
	case T_USED::RECURSION:
		res = WildcardMatching::recursion(str1, str2);
		break;
	case T_USED::RECURSION_MEMO:
		res = WildcardMatching::memoization(str1, str2);
		break;
	case T_USED::TABULATION:
		res = WildcardMatching::tabulation(str1, str2);
		break;
	default:
		break;
	}

	if (res)
		std::cout << "Result : True" << std::endl;
	else
		std::cout << "Result : False" << std::endl;
}
