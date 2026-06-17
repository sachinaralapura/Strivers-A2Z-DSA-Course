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

int TriangleMinPathSum::recursion(Vecvec& triangle)
{
	return tri_recursion(0, 0, triangle);
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
		// res = TriangleMinPathSum::memoization(triangle);
		break;
	case T_USED::TABULATION:
		// res = TriangleMinPathSum::tabulation(triangle);
		break;
	}
	std::cout << std::setw(2) << triangle << std::endl;
	std::cout << "RESULT :" << res;
}
