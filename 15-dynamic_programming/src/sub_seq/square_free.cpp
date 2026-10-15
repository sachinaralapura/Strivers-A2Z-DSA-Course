#include "sub_seq.hpp"
#include "utils.hpp"

int primes[] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29};
std::vector<int> maskOf(31, 0);
using DP = Vecvec<long>;
static const int MOD = 1e9 + 7;

static int findMaskOf(int num)
{
	bool ok = true;
	int m = 0;
	for (int j = 0; j < 10; j++) {
		if (num % primes[j] == 0) {
			num = num / primes[j];
			if (num % primes[j] == 0) {
				ok = false;
				break;
			}
			m |= (1 << j);
		}
	}
	return ok ? m : -1;
}

static void buildMask(std::vector<int>& mask)
{
	for (int i = 2; i < 31; i++) {
		mask[i] = findMaskOf(i);
	}
}

static long recursion(int ind, long long product_mask, std::vector<int>& nums)
{
	if (ind == nums.size())
		return 1;
	long not_take = recursion(ind + 1, product_mask, nums);
	long take = 0;
	int num_mask = maskOf[nums[ind]];
	if (num_mask != -1 && (product_mask & num_mask) == 0)
		take = recursion(ind + 1, product_mask | num_mask, nums);
	return take + not_take;
}

static long memoization(int ind, long long product_mask, std::vector<int>& nums, DP& dp)
{
	if (ind == nums.size())
		return 1;
	if (dp[ind][product_mask] != -1)
		return dp[ind][product_mask];
	long not_take = memoization(ind + 1, product_mask, nums, dp);
	long take = 0;
	int num_mask = maskOf[nums[ind]];
	if (num_mask != -1 && (product_mask & num_mask) == 0)
		take = memoization(ind + 1, product_mask | num_mask, nums, dp);
	return dp[ind][product_mask] = (take + not_take) % MOD;
}

long SquareFreeSubset::recursion(std::vector<int>& nums)
{
	buildMask(maskOf);
	return ::recursion(0, 0, nums) - 1;
}

long SquareFreeSubset::memoization(std::vector<int>& nums)
{
	buildMask(maskOf);
	DP dp(nums.size() + 1, std::vector<long>(1 << 10, -1));
	return ::memoization(0, 0, nums, dp) - 1;
}

long SquareFreeSubset::tabulation(std::vector<int>& nums)
{
	const int FULL = (1 << 10);
	std::vector<int> freq(31, 0);
	for (int x : nums)
		freq[x]++;

	std::vector<long long> dp(FULL, 0);
	dp[0] = 1;
	for (int num = 2; num <= 30; num++) {
		if (freq[num] == 0)
			continue;
		int num_mask = findMaskOf(num);
		if (num_mask == -1)
			continue;
		for (int mask = FULL - 1; mask >= 0; mask--) {
			if ((mask & num_mask) == 0 && dp[mask]) {
				dp[mask | num_mask] = (dp[mask | num_mask] + dp[mask] * freq[num]) % MOD;
			}
		}
	}
	long res = 0;
	for (int mask = FULL - 1; mask >= 0; mask--) {
		res = (res + dp[mask]) % MOD;
	}
	for (int i = 0; i < freq[1]; i++) {
		res = (res * 2) % MOD;
	}

	return (res - 1 + MOD) % MOD;
}

void SquareFreeSubset::test(T_USED t_used)
{
	// std::vector<int> arr = {22, 2,	5,	26, 28, 8,	4,	11, 12, 17, 11,
	// 						3,	19, 29, 19, 7,	24, 12, 22, 5,	8,	22};
	// std::vector<int> arr = {11, 2, 19, 7, 9, 27};
	// std::vector<int> arr = {3,4,4,5};

	std::vector<int> arr = {14, 5,	21, 22, 20, 21, 22, 29, 25, 22, 18, 13, 8,	6,	2,	1,
							23, 25, 1,	2,	1,	14, 24, 1,	4,	22, 12, 26, 12, 12, 16, 23,
							14, 27, 1,	14, 10, 24, 25, 10, 8,	8,	26, 26, 10, 15, 11, 3,
							29, 29, 19, 26, 10, 5,	15, 29, 15, 9,	27, 20, 14, 29, 22, 28,
							1,	4,	11, 21, 30, 30, 26, 19, 14, 11, 29, 12, 24, 18, 9,	23,
							15, 18, 9,	11, 1,	18, 8,	10, 13, 3,	17, 22, 1,	10, 22, 11};
	long res = 0;
	std::cout << "Technique used : " << t_used << std::endl;
	switch (t_used) {
	case T_USED::RECURSION:
		res = 0;
		res = SquareFreeSubset::recursion(arr);
		break;
	case T_USED::RECURSION_MEMO:
		res = SquareFreeSubset::memoization(arr);
		break;
	case T_USED::TABULATION:
		res = SquareFreeSubset::tabulation(arr);
		break;
	default:
		break;
	}
	std::cout << "Result : " << res << std::endl;
}
