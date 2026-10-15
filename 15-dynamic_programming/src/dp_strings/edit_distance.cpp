#include "dpstrings.hpp"
#include "utils.hpp"

using DP = Vecvec<long>;
static long recursion(int i, int j, const std::string& str1, const std::string& str2)
{
	// std::cout << i<< " " << j << std::endl;
	if (i < 0)
		return j + 1;
	if (j < 0)
		return i + 1;

	if (str1[i] == str2[j]) {
		return recursion(i - 1, j - 1, str1, str2);
	}
	// insert
	long ins = recursion(i, j - 1, str1, str2);
	// delete
	long del = recursion(i - 1, j, str1, str2);
	// replace
	long rep = recursion(i - 1, j - 1, str1, str2);
	return 1 + std::min(ins, std::min(del, rep));
}

long memoization(int i, int j, const std::string& str1, const std::string& str2, DP& dp)
{
	if (i < 0)
		return j + 1;
	if (j < 0)
		return i + 1;

	if (dp[i][j] != -1)
		return dp[i][j];

	if (str1[i] == str2[j]) {
		return dp[i][j] = memoization(i - 1, j - 1, str1, str2, dp);
	}
	// insert
	long ins = memoization(i, j - 1, str1, str2, dp);
	// delete
	long del = memoization(i - 1, j, str1, str2, dp);
	// replace
	long rep = memoization(i - 1, j - 1, str1, str2, dp);
	return dp[i][j] = 1 + std::min(ins, std::min(del, rep));
}

long EditDistance::recursion(const std::string& str1, const std::string& str2)
{
	int N = str1.size();
	int M = str2.size();
	if (N < M)
		return 0;
	return ::recursion(N - 1, M - 1, str1, str2);
}

long EditDistance::memoization(const std::string& str1, const std::string& str2)
{
	int N = str1.size();
	int M = str2.size();
	if (N < M)
		return 0;
	DP dp(N + 1, std::vector<long>(M + 1, -1));
	return ::memoization(N - 1, M - 1, str1, str2, dp);
}

long EditDistance::tabulation(const std::string& str1, const std::string& str2)
{
	int N = str1.size();
	int M = str2.size();
	if (N < M)
		return 0;
	DP dp(N + 1, std::vector<long>(M + 1, 0));

	// base cases
	for (int j = 0; j <= M; j++) {
		dp[0][j] = j;
	}
	for (int i = 0; i <= N; i++) {
		dp[i][0] = i;
	}

	for (size_t i = 1; i <= N; i++) {
		for (size_t j = 1; j <= M; j++) {
			if (str1[i - 1] == str2[j - 1]) {
				dp[i][j] = dp[i - 1][j - 1];
				continue;
			}
			// insert
			long ins = dp[i][j - 1];
			// delete
			long del = dp[i - 1][j];
			// replace
			long rep = dp[i - 1][j - 1];
			dp[i][j] = 1 + std::min(ins, std::min(del, rep));
		}
	}
	return dp[N][M];
}

void EditDistance::test(T_USED t_used)
{
	// std::string str1("planet");
	// std::string str2("plan");

	std::string str1("saturday");
	std::string str2("sunday");
	long res = 0;
	std::cout << "Problem : Edit Distance" << std::endl;
	std::cout << "Technique used : " << t_used << std::endl;
	std::cout << "String 1 : " << str1 << std::endl;
	std::cout << "String 2 : " << str2 << std::endl;

	switch (t_used) {
	case T_USED::RECURSION:
		res = EditDistance::recursion(str1, str2);
		break;
	case T_USED::RECURSION_MEMO:
		res = EditDistance::memoization(str1, str2);
		break;
	case T_USED::TABULATION:
		res = EditDistance::tabulation(str1, str2);
		break;
	default:
		break;
	}
	std::cout << "Result : " << res << std::endl;
}
