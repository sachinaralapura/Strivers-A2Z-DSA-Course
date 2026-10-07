#include "dpstrings.hpp"
#include <algorithm>
#include <string>

long MinInstDelAtoB::recursion(const std::string& str1, const std::string& str2)
{
	size_t N = str1.size();
	size_t M = str2.size();
	return N + M - 2 * LongCommonSubSeq::recursion(str1, str2);
}

long MinInstDelAtoB::memoization(const std::string& str1, const std::string& str2)
{
	size_t N = str1.size();
	size_t M = str2.size();
	return N + M - 2 * LongCommonSubSeq::memoization(str1, str2);
}

long MinInstDelAtoB::tabulation(const std::string& str1, const std::string& str2)
{
	size_t N = str1.size();
	size_t M = str2.size();
	return  N + M - 2 * LongCommonSubSeq::tabulation(str1, str2);
}

void MinInstDelAtoB::test(T_USED t_used)
{
	std::string str1("kitten");
	std::string str2("sitting");
	long res = 0;
	std::cout << "Problem : Minimum Insertion Deletion to convert string  A to B" << std::endl;
	std::cout << "Technique used : " << t_used << std::endl;
	std::cout << "String 1 : " << str1 << std::endl;
	std::cout << "String 2 : " << str2 << std::endl;

	switch (t_used) {
	case T_USED::RECURSION:
		res = MinInstDelAtoB::recursion(str1, str2);
		break;
	case T_USED::RECURSION_MEMO:
		res = MinInstDelAtoB::memoization(str1, str2);
		break;
	case T_USED::TABULATION:
		res = MinInstDelAtoB::tabulation(str1, str2);
		break;
	default:
		break;
	}
	std::cout << "Result : " << res << std::endl;
}
