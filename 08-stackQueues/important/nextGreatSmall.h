#ifndef NEXT_GREAT_SMALL
#define NEXT_GREAT_SMALL

#include <vector>

std::vector<int> NextGreaterBrute(std::vector<int> arr);

std::vector<int> NextGreaterCircluar(std::vector<int> arr);

std::vector<int> PreviousGreatorCircular(std::vector<int> arr);

std::vector<int> NextSmallerCircular(std::vector<int> arr);

std::vector<int> PreviousSmallerCircular(std::vector<int> arr);

// returns the index of the previous smaller element
// for elements that doesn't have a previous smaller element it's -1
std::vector<int> PreviousSmaller(std::vector<int> arr);

// returns the index of the next smaller element
// for elements that doesn't have a next smaller element it's -1
std::vector<int> NextSmaller(std::vector<int>);

#endif
