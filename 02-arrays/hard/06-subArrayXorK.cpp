#include <bits/stdc++.h>
using namespace std;
// Count the number of subarrays with given xor K
// Problem Statement : Given an array of integers A and an integer B.
// Find the total number of subarrays having bitwise XOR of all elements equal to k.

int subarraysWithXorKOpt(vector<int> arr, int k) {
    int n = arr.size();
    unordered_map<int, int> mpp;
    mpp[0] = 1;
    int cnt = 0;
    int totalXor = 0;
    for (int i = 0; i < n; i++) {
        totalXor = totalXor ^ arr[i];
        int x = totalXor ^ k;
        cnt = cnt + mpp[x];
        mpp[totalXor]++;
    }
    return cnt;
}
