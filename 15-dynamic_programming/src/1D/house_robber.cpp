#include "1d.hpp"

int house_robber(std::vector<int>& houses)
{
	if (houses.size() == 1)
		return houses[0];
	std::vector<int> temp_one(houses.begin(), houses.end() - 1);
	std::vector<int> temp_two(houses.begin() + 1, houses.end());
	return std::max(max_sum_non_adjacent(temp_one), max_sum_non_adjacent(temp_two));
}
