#include "1d.hpp"
#include <unordered_map>
using namespace std;

size_t fib_recursion(size_t num, unordered_map<size_t, size_t>& mpp)
{
	if (num <= 1)
		return num;
	if (mpp.contains(num))
		return mpp[num];
	return mpp[num] = fib_recursion(num - 2, mpp) + fib_recursion(num - 1, mpp);
}

size_t fib_bottom_up(size_t num, unordered_map<size_t, size_t>& mpp)
{
	if (num <= 1)
		return num;
	mpp[0] = 0;
	mpp[1] = 1;
	for (size_t i = 2; i <= num; i++)
		mpp[i] = mpp[i - 1] + mpp[i - 2];
	return mpp[num];
}

size_t fib_bottom_up_optimized(size_t num)
{
	if (num <= 1)
		return num;
	size_t p = 1;
	size_t pp = 0;
	size_t curr = 0;
	for (size_t i = 2; i <= num; i++) {
		curr = p + pp;
		pp = p;
		p = curr;
	}
	return p;
}
