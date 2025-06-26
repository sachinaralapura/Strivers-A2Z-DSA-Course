#include <bits/stdc++.h>
using namespace std;
// Kadane's Algorithm : Maximum Subarray Sum in an Array
// Problem Statement : Given an integer array arr, find the contiguous
// subarray(containing at least one number) which has the largest sum and
// returns its sum and prints the subarray.
inline long long maxSubarraySum(vector<int> &arr) {
    int n = arr.size();
    long long maxi = LONG_MIN;
    long long sum = 0;
    int start = 0;
    int maxStart = -1;
    int maxEnd = -1;
    for (int i = 0; i < n; i++) {
        if (sum == 0)
            start = i;
        sum += arr[i];
        if (sum > maxi) {
            maxStart = start;
            maxEnd = i;
            maxi = sum;
        }
        if (sum < 0)
            sum = 0;
    }
    for (int i = maxStart; i <= maxEnd; i++)
        cout << arr[i] << ",";
    cout << endl;
    return maxi;
}
