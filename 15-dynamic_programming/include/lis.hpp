#include "utils.hpp"
#include <string>

// Given an array of n integers arr, return the Longest Increasing Subsequence (LIS) that is Index -
// wise Lexicographically Smallest.The Longest Increasing Subsequence(LIS) is the longest
// subsequence where all elements are in strictly increasing order.A subsequence A1 is Index - wise
// Lexicographically Smaller than another subsequence A2 if, at the first position where A1 and A2
// differ, the element in A1 appears earlier in the array arr than corresponding element in S2.Your
// task is to return the LIS that is Index - wise Lexicographically Smallest from the given array.

namespace LongIncSubseq
{
	long recursion(std::vector<int>&);
	long memoization(std::vector<int>&);
	long tabulation(std::vector<int>&);
	long spaceOptimization(std::vector<int>&);
	long spaceOptimizationTwo(std::vector<int>&);
	void test(T_USED);
} // namespace LongIncSubseq

// Given an integer array nums, return the length of the longest strictly increasing subsequence. A
// subsequence is a sequence derived from an array by deleting some or no elements without changing
// the order of the remaining elements. For example, [3, 6, 2, 7] is a subsequence of [0, 3, 1, 6,
// 2, 2, 7]. The task is to find the length of the longest subsequence in which every element is
// greater than the previous one.
namespace LongIncSubseqPrint
{
	// long recursion(std::vector<int>&);
	// long memoization(std::vector<int>&);
	void tabulation(std::vector<int>&, std::vector<int>&);
	// long spaceOptimization(std::vector<int>&);
	// long spaceOptimizationTwo(std::vector<int>&);

	void test();
} // namespace LongIncSubseqPrint

// Given an array nums of positive integers, the task is to find the largest subset such that every
// pair (a, b) of elements in the subset satisfies a % b == 0 or b % a == 0. Return the subset in
// any order. If there are multiple solutions, return any one of them.
//
// Note: As there can be multiple correct answers, the compiler returns 1 if the answer is valid,
// else 0.
namespace LongDivSubseq
{
	// long recursion(std::vector<int>&);
	// long memoization(std::vector<int>&);
	void tabulation(std::vector<int>&, std::vector<int>&);
	// long spaceOptimization(std::vector<int>&);
	// long spaceOptimizationTwo(std::vector<int>&);
	void test();
} // namespace LongDivSubseq

// You are given an array of words where each word consists of lowercase English letters.
//
// wordA is a predecessor of wordB if and only if we can insert exactly one letter anywhere in wordA
// without changing the order of the other characters to make it equal to wordB.
//
// For example, "abc" is a predecessor of "abac", while "cba" is not a predecessor of "bcad". A word
// chain is a sequence of words [word1, word2, ..., wordk] with k >= 1, where word1 is a predecessor
// of word2, word2 is a predecessor of word3, and so on. A single word is trivially a word chain
// with k == 1.
//
// Return the length of the longest possible word chain with words chosen from the given list of
// words.
namespace LongStringChain
{
	// long recursion(std::vector<int>&);
	// long memoization(std::vector<int>&);
	void tabulation(std::vector<std::string>&, std::vector<std::string>&);
	// long spaceOptimization(std::vector<int>&);
	// long spaceOptimizationTwo(std::vector<int>&);
	void test();
} // namespace LongStringChain

// Given an array arr of n integers, the task is to find the length of the longest bitonic sequence.
// A sequence is considered bitonic if it is strictly increasing, strictly decreasing, or strictly
// increases and then strictly decreases.. The sequence does not have to be contiguous.
namespace LongBitonicSubseq
{
	long tabulation(std::vector<int>&);
	void test();
} // namespace LongBitonicSubseq


// Given an integer array nums, find the number of Longest Increasing Subsequences (LIS) in the array.

namespace NumberOfLis
{
    long tabulation(std::vector<int>&);
	void test();
}
