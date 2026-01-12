// There are several cards arranged in a row, and each card has an associated number of points.
// The points are given in the integer array cardPoints.

// In one step, you can take one card from the beginning or from the end of the row.
// You have to take exactly k cards.

// Your score is the sum of the points of the cards you have taken.

// Given the integer array cardPoints and the integer k, return the maximum score you can obtain.

#include <algorithm>
#include <iostream>
#include <vector>

int maxPoints(std::vector<int> arr, int k) {
    int left = 0;
    int right = arr.size() - 1;
    int left_sum = 0;
    int right_sum = 0;
    int max_sum = 0;
    for (int i = 0; i < k; i++)
        left_sum = left_sum + arr[i];
    max_sum = left_sum;

    for (left = k - 1; left >= 0; left--) {
        left_sum = left_sum - arr[left];
        right_sum = right_sum + arr[right];
        right = right - 1;
        max_sum = std::max(max_sum, left_sum + right_sum);
    }
    return max_sum;
}

int main() {
    std::vector<int> arr = {9, 7, 7, 9, 7, 7, 9};
    const int max_points = maxPoints(arr, 7);
    std::cout << "Max Points : " << max_points << std::endl;
    return 0;
}
