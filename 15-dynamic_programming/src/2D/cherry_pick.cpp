#include "twod.hpp"
#include <climits>
#include <iomanip>
#include <vector>

int changes[3] = {-1, 0, 1};
using DP = cube;
int cherry_pick_recursion(int row, int a_col, int b_col, Vecvec<int>& grid)
{
	if (a_col < 0 || a_col >= grid[row].size() || b_col < 0 || b_col >= grid[row].size())
		return INT_MIN;
	if (row >= grid.size() - 1) {
		if (a_col == b_col)
			return grid[row][a_col];
		return grid[row][a_col] + grid[row][b_col];
	}
	int maxi = 0;
	for (int i : changes)
		for (int j : changes) {
			maxi = std::max(maxi, cherry_pick_recursion(row + 1, a_col + i, b_col + j, grid));
		}
	if (a_col == b_col)
		return grid[row][a_col] + maxi;
	return grid[row][a_col] + grid[row][b_col] + maxi;
}

int cherry_pick_memo(int row, int a_col, int b_col, Vecvec<int>& grid, DP& dp)
{
	if (a_col < 0 || a_col >= grid[row].size() || b_col < 0 || b_col >= grid[row].size())
		return INT_MIN;
	if (row >= grid.size() - 1) {
		if (a_col == b_col)
			return grid[row][a_col];
		return grid[row][a_col] + grid[row][b_col];
	}
	if (dp[row][a_col][b_col] != -1)
		return dp[row][a_col][b_col];
	int maxi = 0;
	for (int i : changes)
		for (int j : changes) {
			maxi = std::max(maxi, cherry_pick_memo(row + 1, a_col + i, b_col + j, grid, dp));
		}
	if (a_col == b_col)
		return grid[row][a_col] + maxi;
	return dp[row][a_col][b_col] = grid[row][a_col] + grid[row][b_col] + maxi;
}

int CherryPicking::recursion(Vecvec<int>& grid)
{
	return cherry_pick_recursion(0, 0, grid[0].size() - 1, grid);
}

int CherryPicking::memoization(Vecvec<int>& grid)
{
	const int cols = grid[0].size();
	DP dp(grid.size(), std::vector<std::vector<int>>(cols, std::vector<int>(cols, -1)));
	return cherry_pick_memo(0, 0, grid[0].size() - 1, grid, dp);
}

void CherryPicking::test(T_USED t_used)
{
	Vecvec<int> vec = {{2, 3, 1, 2}, {3, 4, 2, 2}, {5, 6, 3, 5}};
	// Vecvec<int> vec = {{4, 1, 2}, {7, 3, 5}};
	int res = 0;
	std::cout << "Technique used : " << t_used << std::endl;
	switch (t_used) {
	case T_USED::RECURSION:
		res = CherryPicking::recursion(vec);
		break;
	case T_USED::RECURSION_MEMO:
		res = CherryPicking::memoization(vec);
		break;
	case T_USED::TABULATION:
		// res = CherryPicking::tabulation(triangle);
		break;
	}
	std::cout << std::setw(2) << vec << std::endl;
	std::cout << "RESULT :" << res;
}
