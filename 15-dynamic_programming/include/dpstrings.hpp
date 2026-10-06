#ifndef DO_ON_STRING
#define DO_ON_STRING

#include "utils.hpp"
#include <string>
namespace LongCommonSubSeq
{
	long recursion(const std::string&, const std::string&);
	long memoization(const std::string&, const std::string&);
	long tabulation(const std::string&, const std::string&);
	
	void test(T_USED);
} // namespace LongCommonSubSeq

#endif
