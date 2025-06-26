#include <bits/stdc++.h>
using namespace std;
// Length of the longest subarray with zero Sum
// Problem Statement : Given an array containing both positive and negative
// integers, we have to find the length of the longest subarray with the sum of
// all elements equal to zero.
int maxLen(vector<int> &arr) {
    int n = arr.size();
    unordered_map<int, int> mpp;
    int maxi = 0;
    int sum = 0;
    int startIndex = 0;
    int endIndex = 0;
    for (int i = 0; i < n; i++) {
        sum += arr[i];
        if (sum == 0) {
            startIndex = 0;
            endIndex = i;
            maxi = i + 1;
        } else if (mpp.find(sum) != mpp.end()) {
            startIndex = mpp[sum] + 1;
            endIndex = i;
            maxi = max(maxi, i - mpp[sum]);
        } else
            mpp[sum] = i;
    }
    cout << startIndex << " " << endIndex << endl;
    return maxi;
}
