#include "twod.hpp"
#include <iostream>
#include <vector>
using namespace GridUniquePath;

int recursive(int rows, int cols)
{
	if (rows == 0 && cols == 0)
		return 1;
	if (rows < 0 || cols < 0)
		return 0;

	int up = recursive(rows - 1, cols);
	int left = recursive(rows, cols - 1);
	return up + left;
}

int recursion_memo(int rows, int cols, Vecvec& dp)
{
	if (rows == 0 && cols == 0)
		return 1;
	if (rows < 0 || cols < 0)
		return 0;
	if (dp[rows][cols] != -1)
		return dp[rows][cols];
	int up = recursive(rows - 1, cols);
	int left = recursive(rows, cols - 1);
	return dp[rows][cols] = up + left;
}

int GridUniquePath::recursion(int rows, int cols)
{
	return recursive(rows, cols);
}

int GridUniquePath::memoization(int rows, int cols)
{
	Vecvec dp(rows + 1, std::vector<int>(cols + 1, -1));
	return recursion_memo(rows, cols, dp);
}

int GridUniquePath::tabulation(int rows, int cols)
{
	Vecvec dp(rows, std::vector<int>(cols, 0));
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			if (i == 0 && j == 0) {
				dp[i][j] = 1;
				continue;
			}
			int up = 0;
			int left = 0;
			if (i > 0)
				up = dp[i - 1][j];
			if (j > 0)
				left = dp[i][j - 1];
			dp[i][j] = up + left;
		}
	}
	// std::cout << dp << std::endl;
	return dp[rows - 1][cols - 1];
}

void GridUniquePath::test(T_USED t_used)
{
	int n = 10;
	int m = 10;
	int res = 0;
	std::cout << "Technique used : " << t_used << std::endl;
	switch (t_used) {
	case T_USED::RECURSION:
		res = GridUniquePath::recursion(n - 1, m - 1);
		break;
	case T_USED::RECURSION_MEMO:
		res = GridUniquePath::memoization(n - 1, m - 1);
		break;
	case T_USED::TABULATION:
		res = GridUniquePath::tabulation(n, m);
		break;
	}
	std::cout << "ROWS :" << n << " | COLS :" << m << " | RESULT :" << res;
}

// 1,2,6,20,70,252,924,3432,12870,48620
