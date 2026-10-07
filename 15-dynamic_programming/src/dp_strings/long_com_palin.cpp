#include "dpstrings.hpp"
#include <algorithm>
#include <string>

long LongComPalidrome::recursion(const std::string& str1)
{
	std::string s = str1;
	std::string t = s;
	std::reverse(t.begin(), t.end());
	return LongCommonSubSeq::recursion(s, t);
}

long LongComPalidrome::memoization(const std::string& str1)
{
	std::string s = str1;
	std::string t = s;
	std::reverse(t.begin(), t.end());
	return LongCommonSubSeq::memoization(s, t);
}

long LongComPalidrome::tabulation(const std::string& str1)
{
	std::string s = str1;
	std::string t = s;
	std::reverse(t.begin(), t.end());
	return LongCommonSubSeq::tabulation(s, t);
}

void LongComPalidrome::test(T_USED t_used)
{
	std::string str1("eeeme");
	long res = 0;
	std::cout << "Problem : Longest common Palindromic subsequence" << std::endl;
	std::cout << "Technique used : " << t_used << std::endl;
	std::cout << "String 1 : " << str1 << std::endl;

	switch (t_used) {
	case T_USED::RECURSION:
		res = LongComPalidrome::recursion(str1);
		break;
	case T_USED::RECURSION_MEMO:
		res = LongComPalidrome::memoization(str1);
		break;
	case T_USED::TABULATION:
		res = LongComPalidrome::tabulation(str1);
		break;
	default:
		break;
	}
	std::cout << "Result : " << res << std::endl;
}
