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
namespace LongComPalidrome
{
	long recursion(const std::string&);
	long memoization(const std::string&);
	long tabulation(const std::string&);
	void test(T_USED);
} // namespace LongComPalidrome
#endif
