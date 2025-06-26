#include <bits/stdc++.h>
#include <vector>
using namespace std;
void recursive(int i, int n, vector<int> &arr, vector<vector<int>> &ans, vector<int> &ds) {
    if (i == n) {
        ans.push_back(ds);
        return;
    }
    ds.push_back(arr[i]);
    recursive(i + 1, n, arr, ans, ds);
    ds.pop_back();
    recursive(i + 1, n, arr, ans, ds);
}

// using bit manipulation
vector<vector<int>> subsets(vector<int> arr) {
    int n = arr.size();
    int numSubsets = (1 << n);
    vector<vector<int>> ans;
    for (int i = 0; i < numSubsets; i++) {
        vector<int> temp;
        for (int j = 0; j < n; j++) {
            if ((i & (1 << j))) {
                temp.push_back(arr[j]);
            }
        }
        ans.push_back(temp);
    }
    return ans;
}
