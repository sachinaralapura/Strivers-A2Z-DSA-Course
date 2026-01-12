#include <bits/stdc++.h>
using namespace std;

// Given an unsorted array that contains even number of occurrences for all numbers except two
// numbers. The task is to find the two numbers which have odd occurrences
vector<int> SingleNumber(vector<int> arr) {
    int n = arr.size();
    int xorVal = 0;
    for (int i : arr)
        xorVal ^= i;

    // Get its last set bit
    int mask = xorVal & (-xorVal);
    vector<int> ans(2, 0);
    for (int i = 0; i < n; i++) {
        int num = arr[i];
        if (num & mask)
            ans[0] ^= num;
        else
            ans[1] ^= num;
    }
    return ans;
}
