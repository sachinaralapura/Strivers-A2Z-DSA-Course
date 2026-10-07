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
#endif
