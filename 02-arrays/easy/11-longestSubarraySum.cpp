#include <bits/stdc++.h>
using namespace std;

// // Problem Statement : Given an array and a sum k, we need to print the
// //  length of the longest subarray that sums to k.
int getLongestSubarray(vector<int> &arr, long long k) {
    int n = arr.size();
    int len = 0;
    for (int i = 0; i < n; i++) {
        long long sum = 0;
        for (int j = i; j < n; j++) {
            sum += arr[j];
            if (sum == k)
                len = max(len, j - i + 1);
        }
    }
    return len;
}

int getLongestSubarray_PrifixSum(vector<int> &arr, long long k) {
    int n = arr.size();
    int maxLen = 0;
    long long sum = 0;
    map<long long, int> prefixSum;

    for (int i = 0; i < n; i++) {
        // calculate the prefix sum till index i:
        sum += arr[i];
        if (sum == k)
            maxLen = max(maxLen, i + 1);
        long long rem = sum - k;
        if (prefixSum.find(rem) != prefixSum.end())
            maxLen = max(maxLen, i - prefixSum[rem]);
        if (prefixSum.find(sum) == prefixSum.end())
            prefixSum[sum] = i;
    }
    return maxLen;
}

int getLongestSubarray_LRPointer(vector<int> &arr, long long k) {
    int n = arr.size();
    int left = 0;
    int right = 0;
    int maxLen = 0;
    long long sum = arr[0];

    while (right < n) {
        while (sum > k && left <= right) {
            sum = sum - arr[left];
            left++;
        }
        if (sum == k)
            maxLen = max(maxLen, right - left + 1);

        right++;
        if (right < n)
            sum += arr[right];
    }
    return maxLen;
}
