#include <algorithm>
#include <bits/stdc++.h>

using namespace std;
vector<vector<int>> ans;

inline void combinationSum(int index, int n, int target, vector<int> &ds, vector<int> &arr) {
    if (index == n) {
        if (target == 0) {
            ans.push_back(ds);
        }
        return;
    }
    if (arr[index] <= target) {
        ds.push_back(arr[index]);
        combinationSum(index, n, target - arr[index], ds, arr);
        ds.pop_back();
    }
    combinationSum(index + 1, n, target, ds, arr);
}

inline vector<vector<int>> comSum(vector<int> arr, int sum) {
    vector<int> ds;
    combinationSum(0, arr.size(), sum, ds, arr);
    return ans;
}
// --------------------------------- combination sum two --------------------------------------
inline void combinationSumTwo(int index, int n, int target, vector<int> &ds, vector<int> &arr) {
    if (target == 0) {
        ans.push_back(ds);
        return;
    }
    for (int i = index; i < n; i++) {
        if (i > index && arr[i - 1] == arr[i])
            continue;
        if (arr[i] <= target) {
            ds.push_back(arr[i]);
            combinationSumTwo(i + 1, n, target - arr[i], ds, arr);
            ds.pop_back();
        }
    }
}

inline vector<vector<int>> comSumtwo(vector<int> arr, int sum) {
    sort(arr.begin(), arr.end());
    vector<int> ds;
    combinationSumTwo(0, arr.size(), sum, ds, arr);
    return ans;
}
