#ifndef ONE_DIMENSION
#define ONE_DIMENSION

#include <cstddef>
#include <cstdlib>
#include <unordered_map>
#include <vector>

using Um = std::unordered_map<int, int>;
// -------------- FIBONACCI ----------------
size_t fib_recursion(size_t, std::unordered_map<size_t, size_t>&);

size_t fib_bottom_up(size_t, std::unordered_map<size_t, size_t>&);

size_t fib_bottom_up_optimized(size_t);

size_t climbing_stairs(size_t n);

// Given a number of stairs and a frog, the frog wants to climb from the 0th stair to the (N-1)th
// stair. At a time the frog can climb either one or two steps. A height[N] array is also given.
// Whenever the frog jumps from a stair i to stair j, the energy consumed in the jump is
// abs(height[i]- height[j]). We need to return the minimum energy
// that can be used by the frog to jump from stair 0 to stair N-1..
int frog_jump_recursion(std::vector<int>& height);

// Given a number of stairs and a frog, the frog wants to climb from the 0th stair to the (N-1)th
// stair. At a time the frog can climb either one or two steps. A height[N] array is also given.
// Whenever the frog jumps from a stair i to stair j, the energy consumed in the jump is
// abs(height[i]- height[j]). We need to return the minimum energy
// that can be used by the frog to jump from stair 0 to stair N-1..
int frog_jump_tabulation(std::vector<int>&);

// A frog wants to climb a staircase with n steps.Given an integer array heights,
// where heights[i] contains the height of the ith step,
// and an integer k.To jump from the ith step to the jth step, the frog requires abs
// (heights[i] - heights[j]) energy, where abs() denotes the absolute difference
// .The frog can jump from the ith step to any step in the range[i + 1, i + k], provided it exists
// .Return the minimum amount of energy required by the frog to go from the 0th step to
// the(n - 1) th step.
int frog_jum_K(std::vector<int>&, int);

// Given an array of N positive integers, we need to return the maximum sum of the subsequence such
// that no two elements of the subsequence are adjacent elements in the array.
// Note : A subsequence of an array is a list with elements of the array where some elements are
// deleted(or not deleted at all) and the elements should be in the same order in the subsequence as
// in the array.
int max_sum_non_adjacent(std::vector<int>&);
int max_sum_tabulated(std::vector<int>&, bool);

// A thief needs to rob money in a street. The houses in the street are arranged in a circular
// manner. Therefore the first and the last house are adjacent to each other. The security system
// in the street is such that if adjacent houses are robbed, the police will get notified.
// Given an array of integers “Arr'' which represents money at each house, 	we need to return the
// maximum amount of money that the thief can rob without alerting the police.
int house_robber(std::vector<int>&);

#endif
