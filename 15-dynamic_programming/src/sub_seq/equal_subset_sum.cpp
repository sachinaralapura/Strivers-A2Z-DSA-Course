#include "sub_seq.hpp"
#include <numeric>

bool equal_subset_recursion(int ind, int target, std::vector<int>& arr)
{
	if (target == 0)
		return true;
	if (ind == 0)
		return (arr[0] == target);
	bool not_taken = equal_subset_recursion(ind - 1, target, arr);
	if (not_taken)
		return not_taken;
	bool taken = false;
	if (arr[ind] <= target)
		taken = equal_subset_recursion(ind - 1, target - arr[ind], arr);
	return (not_taken || taken);
}

long long findK(std::vector<int>& arr)
{
	long long sum = std::reduce(arr.begin(), arr.end(), 0LL);
	// std::cout << "Sum : " << sum << std::endl;
	if (sum % 2 == 1)
		return false;
	long long k = sum / 2;
	// std::cout << "K : " << k << std::endl;
	return k;
}

bool EqualSubsetSum::recursion(std::vector<int>& arr)
{
	long long k = findK(arr);
	return equal_subset_recursion(arr.size() - 1, k, arr);
}

bool EqualSubsetSum::memoization(std::vector<int>& arr)
{
	long long k = findK(arr);
	return SubsetKSum::memoization(arr, k);
}

bool EqualSubsetSum::tabulation(std::vector<int>& arr)
{
	long long k = findK(arr);
	return SubsetKSum::tabulation(arr, k);
}

void EqualSubsetSum::test(T_USED t_used)
{
	std::vector<int> arr = {2, 3, 3, 3, 4, 5};
	bool res = false;
	switch (t_used) {
	case T_USED::RECURSION:
		res = EqualSubsetSum::recursion(arr);
		break;
	case T_USED::RECURSION_MEMO:
		res = EqualSubsetSum::memoization(arr);
		break;
	case T_USED::TABULATION:
		res = EqualSubsetSum::tabulation(arr);
		break;
	}
	if (res)
		std::cout << "TRUE" << std::endl;
	else
		std::cout << "FALSE" << std::endl;
}
