#include "twod.hpp"
#include <algorithm>
#include <array>
#include <iostream>

int ninja_recursive_memoization(int index, int prev, DailyTasks& dailytasks, Dp& dp)
{
	if (index == 0)
		return dailytasks[0].maxExpectPrev(prev);
	if (dp.contains(index) && dp[index].data[prev] != -1)
		return dp[index].data[prev];
	int maxi = 0;
	for (auto j = 0; j <= 2; j++) {
		if (j != prev) {
			int points = dailytasks[index].scores[j] +
						 ninja_recursive_memoization(index - 1, j, dailytasks, dp);
			maxi = std::max(maxi, points);
		}
	}
	return dp[index].data[prev] = maxi;
}

int ninja_recursive(int index, int prev, DailyTasks& dailytasks)
{
	if (index == 0) {
		return dailytasks[0].maxExpectPrev(prev);
	}
	int maxi = 0;
	for (auto j = 0; j <= 2; j++) {
		if (j != prev) {
			int points = dailytasks[index].scores[j] + ninja_recursive(index - 1, j, dailytasks);
			maxi = std::max(maxi, points);
		}
	}
	return maxi;
}

int ninja_training_recursion(DailyTasks& dailyTasks)
{
	return ninja_recursive(dailyTasks.size() - 1, 3, dailyTasks);
}

int ninja_training_recursion_memo(DailyTasks& dailyTasks)
{
	Dp dp;
	return ninja_recursive_memoization(dailyTasks.size() - 1, 3, dailyTasks, dp);
}

int ninja_training_tab(DailyTasks& dailyTasks)
{
	int n = dailyTasks.size() - 1;
	Dp dp;
	dp[0].data[0] = std::max(dailyTasks[0].scores[1], dailyTasks[0].scores[2]);
	dp[0].data[1] = std::max(dailyTasks[0].scores[0], dailyTasks[0].scores[2]);
	dp[0].data[2] = std::max(dailyTasks[0].scores[1], dailyTasks[0].scores[0]);
	dp[0].data[3] = std::max(dailyTasks[0].scores[0],
							 std::max(dailyTasks[0].scores[1], dailyTasks[0].scores[2]));

	for (auto day = 1; day <= n; day++) {
		for (auto last = 0; last < 4; last++) {
			int maxi = 0;
			for (auto task = 0; task < 3; task++) {
				if (task != last) {
					int point = dailyTasks[day].scores[task] + dp[day - 1].data[task];
					maxi = std::max(maxi, point);
				}
			}
			dp[day].data[last] = maxi;
		}
	}
	return dp[n].data[3];
}

int test()
{
	DailyTasks dailytask = {
		{{10, 40, 70}},
		{{20, 50, 80}},
		{{30, 60, 90}},
	};
	int res = ninja_training_tab(dailytask);
	std::cout << "RESULT : " << res << std::endl;
	return 0;
}
