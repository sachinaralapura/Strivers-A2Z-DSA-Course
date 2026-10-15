#include "dpstrings.hpp"
#include "utils.hpp"

using DP = Vecvec<long>;
static long recursion(int i, int j, const std::string& str1, const std::string& str2)
{
	// std::cout << i<< " " << j << std::endl;
	if ((i < 0 && j < 0) || j < 0)
		return 1;
	if (i < 0)
		return 0;

	if (str1[i] == str2[j]) {
		return (recursion(i - 1, j - 1, str1, str2) + recursion(i - 1, j, str1, str2));
	}
	return recursion(i - 1, j, str1, str2);
}

 static long memoization(int i, int j, const std::string& str1, const std::string& str2, DP& dp)
{
	// std::cout << i<< " " << j << std::endl;
	if ((i < 0 && j < 0) || j < 0)
		return 1;
	if (i < 0)
		return 0;

	if (dp[i][j] != -1)
		return dp[i][j];
	if (str1[i] == str2[j]) {
		return dp[i][j] = (memoization(i - 1, j - 1, str1, str2, dp) +
						   memoization(i - 1, j, str1, str2, dp));
	}
	return dp[i][j] = memoization(i - 1, j, str1, str2, dp);
}
long DistinctSubsequences::recursion(const std::string& str1, const std::string& str2)
{
	int N = str1.size();
	int M = str2.size();
	if (N < M)
		return 0;
	return ::recursion(N - 1, M - 1, str1, str2);
}

long DistinctSubsequences::memoization(const std::string& str1, const std::string& str2)
{
	int N = str1.size();
	int M = str2.size();
	if (N < M)
		return 0;
	DP dp(N + 1, std::vector<long>(M + 1, -1));
	return ::memoization(N - 1, M - 1, str1, str2, dp);
}

long DistinctSubsequences::tabulation(const std::string& str1, const std::string& str2)
{
	int N = str1.size();
	int M = str2.size();
	if (N < M)
		return 0;
	DP dp(N + 1, std::vector<long>(M + 1, 0));

	for (int i = 0; i <= N; i++) {
		dp[i][0] = 1;
	}

	for (size_t i = 1; i <= N; i++) {
		for (size_t j = 1; j <= M; j++) {
			if (str1[i - 1] == str2[j - 1]) {
				dp[i][j] = (dp[i - 1][j - 1] + dp[i - 1][j]);
				continue;
			}
			dp[i][j] = dp[i - 1][j];
		}
	}
	return dp[N][M];
}

void DistinctSubsequences::test(T_USED t_used)
{
	std::string str1("babgbag");
	std::string str2("bag");

	// std::string str1("abcde");
	// std::string str2("ace");
	long res = 0;
	std::cout << "Problem : Distinct Subsequences" << std::endl;
	std::cout << "Technique used : " << t_used << std::endl;
	std::cout << "String 1 : " << str1 << std::endl;
	std::cout << "String 2 : " << str2 << std::endl;

	switch (t_used) {
	case T_USED::RECURSION:
		res = DistinctSubsequences::recursion(str1, str2);
		break;
	case T_USED::RECURSION_MEMO:
		res = DistinctSubsequences::memoization(str1, str2);
		break;
	case T_USED::TABULATION:
		res = DistinctSubsequences::tabulation(str1, str2);
		break;
	default:
		break;
	}
	std::cout << "Result : " << res << std::endl;
}
