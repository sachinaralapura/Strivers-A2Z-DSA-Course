#include <bits/stdc++.h>
using namespace std;
// Count Subarray sum Equals K
// Problem Statement : Given an array of integers and an integer k,
// return the total number of subarrays whose sum equals k.
// A subarray is a contiguous non - empty sequence of elements within an array.
inline int findAllSubarraysWithGivenSum(vector<int> &arr, int k) {
    int n = arr.size();
    map<int, int> mpp;
    mpp[0] = 1;
    int count = 0;
    int PrefixSum = 0;
    for (int i = 0; i < n; i++) {
        PrefixSum += arr[i];
        int remove = PrefixSum - k;
        count += mpp[remove];
        mpp[PrefixSum] += 1;
    }
    return count;
}
