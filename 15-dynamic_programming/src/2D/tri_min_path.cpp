#include "twod.hpp"
#include <algorithm>
#include <climits>
#include <iomanip>

int tri_recursion(int row, int col, Vecvec& triangle)
{
	if (row == triangle.size() - 1)
		return triangle[row][col];
	if (col > triangle[row].size() - 1)
		return INT_MAX;
	int bottom = tri_recursion(row + 1, col, triangle);
	int bottom_right = tri_recursion(row + 1, col + 1, triangle);
	return triangle[row][col] + std::min(bottom, bottom_right);
}

int tri_recursion_memo(int row, int col, Vecvec& triangle, Vecvec& dp)
{
	if (row == triangle.size() - 1)
		return triangle[row][col];
	if (col > triangle[row].size() - 1)
		return INT_MAX;
	if (dp[row][col] != -1)
		return dp[row][col];
	int bottom = tri_recursion_memo(row + 1, col, triangle, dp);
	int bottom_right = tri_recursion_memo(row + 1, col + 1, triangle, dp);
	return dp[row][col] = triangle[row][col] + std::min(bottom, bottom_right);
}

int TriangleMinPathSum::recursion(Vecvec& triangle)
{
	return tri_recursion(0, 0, triangle);
}

int TriangleMinPathSum::memoization(Vecvec& triangle)
{
	Vecvec dp(triangle.size(), std::vector<int>(triangle[triangle.size() - 1].size(), -1));
	return tri_recursion_memo(0, 0, triangle, dp);
}

int TriangleMinPathSum::tabulation(Vecvec& triangle)
{
	int n = triangle.size();
	Vecvec dp(triangle.size(), std::vector<int>(triangle[triangle.size() - 1].size(), -1));
	for (int i = n - 1; i >= 0; i--) {
		for (int j = 0; j < triangle[i].size(); j++) {
			if (i == n - 1) {
				dp[i][j] = triangle[i][j];
				continue;
			}
			int bottom = triangle[i][j] + dp[i + 1][j];
			int bottom_right = triangle[i][j] + dp[i + 1][j + 1];
			dp[i][j] = std::min(bottom, bottom_right);
		}
	}
	return dp[0][0];
}

void TriangleMinPathSum::test(T_USED t_used)
{
	// Vecvec triangle = {{1}, {1, 2}, {1, 2, 4}};
	Vecvec triangle = {{1}, {4, 7}, {4, 10, 50}, {-50, 5, 6, -100}};
	int res = 0;
	std::cout << "Technique used : " << t_used << std::endl;
	switch (t_used) {
	case T_USED::RECURSION:
		res = TriangleMinPathSum::recursion(triangle);
		break;
	case T_USED::RECURSION_MEMO:
		res = TriangleMinPathSum::memoization(triangle);
		break;
	case T_USED::TABULATION:
		res = TriangleMinPathSum::tabulation(triangle);
		break;
	}
	std::cout << std::setw(2) << triangle << std::endl;
	std::cout << "RESULT :" << res;
}
