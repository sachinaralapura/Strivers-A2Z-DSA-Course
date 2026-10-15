#ifndef DO_ON_STRING
#define DO_ON_STRING

#include "utils.hpp"
#include <string>

// Given two strings str1 and str2, find the length of their longest common subsequence.
// A subsequence is a sequence that appears in the same relative order but not necessarily
// contiguous and a common subsequence of two strings is a subsequence that is common to both
// strings.
namespace LongCommonSubSeq
{
	long recursion(const std::string&, const std::string&);
	long memoization(const std::string&, const std::string&);
	long tabulation(const std::string&, const std::string&);

	void test(T_USED);
} // namespace LongCommonSubSeq

// Given two strings str1 and str2, find the length of their longest common substring.
// A substring is a contiguous sequence of characters within a string.
namespace LongCommonSubStr
{
	long tabulation(const std::string&, const std::string&);
	void test(T_USED);
} // namespace LongCommonSubStr

// Given a string, Find the longest palindromic subsequence length in given string.
// A palindrome is a sequence that reads the same backwards as forward.
// A subsequence is a sequence that can be derived from another sequence by deleting some or no
// elements without changing the order of the remaining elements.
namespace LongPalidrome
{
	long recursion(const std::string&);
	long memoization(const std::string&);
	long tabulation(const std::string&);
	void test(T_USED);
} // namespace LongPalidrome

// Given two strings str1 and str2, find the minimum number of insertions and deletions in string
// str1 required to transform str1 into str2.
// Insertion and deletion of characters can take place at any position in the string.
namespace MinInstDelAtoB
{
	long recursion(const std::string&, const std::string&);
	long memoization(const std::string&, const std::string&);
	long tabulation(const std::string&, const std::string&);
	void test(T_USED);
} // namespace MinInstDelAtoB

// Given two strings str1 and str2, find the shortest common supersequence.
// The shortest common supersequence is the shortest string that contains both str1 and str2 as
// subsequences.
//
// Note: The problem may have multiple valid answers. Since the return type is a string, the judge
// will output 1 if your returned string is a valid shortest common supersequence and 0 otherwise.
namespace PrintShortestSuperSeq
{
	std::string tabulation(const std::string&, const std::string&);
	void test();
} // namespace PrintShortestSuperSeq

// Given two strings s and t, return the number of distinct subsequences of s that equal t.
// A subsequence of a string is a new string generated from the original string with some characters
// (can be none) deleted without changing the relative order of the remaining characters. For
// example, "ace" is a subsequence of "abcde" while "aec" is not.
// The task is to count how many different ways we can form t from s by deleting some (or no)
// characters from s. Return the result modulo 109+7.
namespace DistinctSubsequences
{
	long recursion(const std::string&, const std::string&);
	long memoization(const std::string&, const std::string&);
	long tabulation(const std::string&, const std::string&);
	void test(T_USED);

} // namespace DistinctSubsequences

// Given two strings start and target, you need to determine the minimum number of operations
// required to convert the string start into the string target. The operations you can use are:
// Insert a character: Add any single character at any position in the string.
// Delete a character: Remove any single character from the string.
// Replace a character: Change any single character in the string to another character.
// The goal is to transform start into target using the fewest number of these operations.
namespace EditDistance
{
	long recursion(const std::string&, const std::string&);
	long memoization(const std::string&, const std::string&);
	long tabulation(const std::string&, const std::string&);
	void test(T_USED);
} // namespace EditDistance

namespace WildcardMatching
{
	bool recursion(const std::string&, const std::string&);
	bool memoization(const std::string&, const std::string&);
	bool tabulation(const std::string&, const std::string&);
	void test(T_USED);
} // namespace WildcardMatching
#endif
