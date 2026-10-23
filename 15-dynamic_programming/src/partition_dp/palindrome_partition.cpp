#include "partition_dp.hpp"
#include <algorithm>
#include <climits>
#include <string>

int N = 0;
bool checkPalindrome(int i, int j, std::string& str)
{
	while (i < j) {
		if (str[i] != str[j])
			return false;
		i++;
		j--;
	}
	return true;
}

static long recursion(int ind, std::string& str)
{
	if (ind == N)
		return 0;

	long minCost = LONG_MAX;
	for (int i = ind; i < N; i++) {
		if (checkPalindrome(ind, i, str)) {
			minCost = std::min(minCost, 1 + recursion(i + 1, str));
		}
	}
	return minCost;
}

long PalindromePartition::recursion(std::string& str)
{
	N = str.length();
	return ::recursion(0, str) - 1;
}

void PalindromePartition::test(T_USED t_used)
{
	// std::string str = "bababcbadcede";
	std::string str = "aab";
	std::cout << "Problem : Palindrome Partition" << std::endl;
	std::cout << "Technique used : " << t_used << std::endl;
	std::cout << "String " << str << std::endl;

	long res = 0;
	switch (t_used) {
	case T_USED::RECURSION:
		res = PalindromePartition::recursion(str);
		break;
	case T_USED::RECURSION_MEMO:
		// res = PalindromePartition::memoization(arr);
		break;
	case T_USED::TABULATION:
		// res = PalindromePartition::tabulation(arr);
		break;
	default:
		break;
	}
	std::cout << "Result : " << res << std::endl;
}
