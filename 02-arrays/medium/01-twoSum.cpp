#include <bits/stdc++.h>
using namespace std;
// Problem Statement : Given an array of integers arr[] and an integer target.
// 1st variant : Return YES if there exist two numbers such that their sum is
// equal to the target.Otherwise, return NO. 2nd variant : Return indices of the
// two numbers such that their sum is equal to the target.Otherwise, we will
// return {-1, -1}. Note : You are not allowed to use the same element
// twice.Example : If the target is equal to 6 and num[1] = 3, then nums[1] +
// nums[1] = target is not a solution. first variant
inline string twoSum1_brute(vector<int> &arr, int k) {
    int n = arr.size();
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (arr[i] + arr[j] == k)
                return "YES";
        }
    }
    return "NO";
}

// second variant
inline vector<int> twoSum2(vector<int> &arr, int target) {
    int n = arr.size();
    vector<int> ans;
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (arr[i] + arr[j] == target) {
                ans.push_back(i);
                ans.push_back(j);
                return ans;
            }
        }
    }
    return {-1, -1};
}

// using hash
inline string twoSum_hash(vector<int> &arr, int target) {
    int n = arr.size();
    unordered_map<int, int> mpp;
    for (int i = 0; i < n; i++) {
        int num = arr[i];
        int needed = target - num;
        if (mpp.find(needed) != mpp.end()) {
            return "YES";
        }
        mpp[num] = i;
    }
    return "NO";
}
