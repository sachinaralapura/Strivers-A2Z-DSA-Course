#ifndef TWO_DIMENSION
#define TWO_DIMENSION
#include "utils.hpp"
#include <algorithm>
#include <array>
#include <cstddef>
#include <unordered_map>
#include <utility>

// Ninja is planing this ‘N’ days-long training schedule. Each day, he can perform any one of
// these three activities. (Running, Fighting Practice or Learning New Moves). Each activity has
// some merit points on each day. As Ninja has to improve all his skills, he can’t do the same
// activity in two consecutive days. Can you help Ninja find out the maximum merit points Ninja
// can earn? You are given a 2D array of size N*3 ‘POINTS’ with the points corresponding to each
// day and activity. Your task is to calculate the maximum number of merit points that Ninja can
// earn.
namespace NinjaTraining
{
	template <typename T> struct TaskScore {
		std::array<T, 3> scores;
		T maxExpectPrev(std::size_t prev)
		{
			if (prev == 0)
				return std::max(scores[1], scores[2]);
			if (prev == 1)
				return std::max(scores[0], scores[2]);
			if (prev == 2)
				return std::max(scores[0], scores[1]);
			return *std::max_element(scores.begin(), scores.end());
		}
	};
	using DailyTasks = std::vector<TaskScore<int>>;
	struct DefaultArray {
		std::array<int, 4> data = {-1, -1, -1, -1}; // In-class initialization
	};
	using Dp = std::unordered_map<int, DefaultArray>;
	int recursion(DailyTasks&);
	int memoization(DailyTasks& dailyTasks);
	int tabulation(DailyTasks& dailyTasks);
	void test(T_USED);
} // namespace NinjaTraining

// Given two integers m and n, representing the number of rows and columns of a 2d array named
// matrix. Return the number of unique ways to go from the top-left cell (matrix[0][0]) to the
// bottom-right cell (matrix[m-1][n-1]).
namespace GridUniquePath
{
	int recursion(int, int);
	int memoization(int, int);
	int tabulation(int, int);
	void test(T_USED);
} // namespace GridUniquePath

namespace GridUniquePathTwo
{
	int recursion(int, int, std::pair<int, int>& deadcell);
	int memoization(int, int, std::pair<int, int>& deadcell);
	int tabulation(int, int, std::pair<int, int>& deadcell);
	void test(T_USED);
} // namespace GridUniquePathTwo

// Given a m x n grid filled with non-negative numbers, find a path from top left to bottom right,
// which minimizes the sum of all numbers along its path.
// Note : You can only move either down or right at any point in time.
namespace GridMinPathSum
{
	int recursion(Vecvec& grid);
	int memoization(Vecvec& grid);
	int tabulation(Vecvec& grid);
	void test(T_USED);
} // namespace GridMinPathSum

// Given a 2D integer array named triangle with n rows. Its first row has 1 element and each
// succeeding row has one more element in it than the row above it. Return the minimum falling path
// sum from the first row to the last. Movement is allowed only to the bottom or bottom - right cell
// from the current cell.
namespace TriangleMinPathSum
{
	int recursion(Vecvec& grid);
	int memoization(Vecvec& grid);
	int tabulation(Vecvec& grid);
	void test(T_USED);
} // namespace TriangleMinPathSum
#endif
