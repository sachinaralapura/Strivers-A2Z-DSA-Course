#include "twod.hpp"
#include <algorithm>
#include <climits>
#include <iomanip>
#include <iostream>
#include <vector>
int grid_min_recursion(int row, int col, Vecvec<int>& grid)
{
	if (row == 0 && col == 0)
		return grid[row][col];
	if (row < 0 || col < 0)
		return INT_MAX;
	int up = grid_min_recursion(row - 1, col, grid);
	int left = grid_min_recursion(row, col - 1, grid);
	return grid[row][col] + std::min(up, left);
}

int grid_min_memo(int row, int col, Vecvec<int>& grid, Vecvec<int>& dp)
{
	if (row == 0 && col == 0)
		return grid[row][col];
	if (row < 0 || col < 0)
		return INT_MAX;
	if (dp[row][col] != -1)
		return dp[row][col];
	int up = grid_min_memo(row - 1, col, grid, dp);
	int left = grid_min_memo(row, col - 1, grid, dp);
	return dp[row][col] = grid[row][col] + std::min(up, left);
}

int GridMinPathSum::recursion(Vecvec<int>& grid)
{
	return grid_min_recursion(grid.size(), grid[0].size(), grid);
}

int GridMinPathSum::memoization(Vecvec<int>& grid)
{
    Vecvec<int> dp(grid.size(), std::vector<int>(grid[0].size(), -1));
	return grid_min_memo(grid.size() - 1, grid[0].size() - 1, grid, dp);
}

int GridMinPathSum::tabulation(Vecvec<int>& grid)
{
    Vecvec<int> dp(grid.size(), std::vector<int>(grid[0].size(), -1));
	for (int i = 0; i < grid.size(); i++) {
		for (int j = 0; j < grid[0].size(); j++) {
			if (i == 0 && j == 0) {
				dp[i][j] = grid[i][j];
				continue;
			}
			int up = grid[i][j];
			int left = grid[i][j];
			if (i > 0)
				up = up + dp[i - 1][j];
			else
				up = INT_MAX;
			if (j > 0)
				left = left + dp[i][j - 1];
			else
				left = INT_MAX;
			dp[i][j] = std::min(up, left);
		}
	}
	return dp[grid.size() - 1][grid[0].size() - 1];
}

void GridMinPathSum::test(T_USED t_used)
{
	Vecvec<int> grid = {{5, 9, 6}, {11, 5, 2}};
	// Vecvec<int> grid = {{1, 2, 3}, {4, 5, 6}};
	int res = 0;
	std::cout << "Technique used : " << t_used << std::endl;
	switch (t_used) {
	case T_USED::RECURSION:
		res = GridMinPathSum::recursion(grid);
		break;
	case T_USED::RECURSION_MEMO:
		res = GridMinPathSum::memoization(grid);
		break;
	case T_USED::TABULATION:
		res = GridMinPathSum::tabulation(grid);
		break;
	}
	std::cout << std::setw(2) << grid << std::endl;
	std::cout << "RESULT :" << res;
}
