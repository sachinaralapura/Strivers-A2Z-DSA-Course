// Problem Statement: Given an array of integers that may contain duplicates the task is to return
// all possible subsets. Return only unique subsets and they can be in any order.
#include <bits/stdc++.h>
#include <vector>
using namespace std;
vector<vector<int>> ans;
inline void setsetRecursive(int index, int n, vector<int> &arr, vector<int> &ds) {
    ans.push_back(ds);
    for (int i = index; i < n; i++) {
        if (i != index && arr[i] == arr[i - 1])
            continue;
        ds.push_back(arr[i]);
        setsetRecursive(i + 1, n, arr, ds);
        ds.pop_back();
    }
}
inline vector<vector<int>> subsetTwo(vector<int> arr) {
    vector<int> ds;
    sort(arr.begin(), arr.end());
    setsetRecursive(0, arr.size(), arr, ds);
    return ans;
}
