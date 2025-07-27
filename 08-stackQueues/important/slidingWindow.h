#ifndef SLIDING_WINDOW
#define SLIDING_WINDOW

#include "../../00-common/common.h"
#include <bits/stdc++.h>
#include <exception>
#include <string>
#include <vector>
using namespace common;
// Given an array of integers arr, there is a sliding window of size k which is moving
// from the very left of the array to the very right. You can only see the k numbers in the window.
// Each time the sliding window moves right by one position. Return the max sliding window.

void GetMax(const std::vector<int>, int, int, std::vector<int> &);
std::vector<int> SlidingWindow(std::vector<int>, int);
std::vector<int> SlidingWindowDequeue(std::vector<int>, int);

#endif
