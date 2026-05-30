#include "1d.hpp"

size_t climbing_stairs(size_t n)
{
	if (n <= 1)
		return 1;
	int prev2 = 1;
	int prev1 = 1;
	for (int i = 2; i <= n; i++) {
		size_t curr = prev2 + prev1;
		prev2 = prev1;
		prev1 = curr;
	}
	return prev1;
}
