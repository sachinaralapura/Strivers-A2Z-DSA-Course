#include <bits/stdc++.h>
#include <vector>
using namespace std;

vector<vector<int>> ans;

void allSUbSum(int i, int n, vector<int> &arr, vector<int> &ds, int currSum, int sum) {
    if (i == n) {
        if (currSum == sum)
            ans.push_back(ds);
        return;
    }
    ds.push_back(arr[i]);
    currSum += arr[i];
    allSUbSum(i + 1, n, arr, ds, currSum, sum);
    currSum -= arr[i];
    ds.pop_back();
    allSUbSum(i + 1, n, arr, ds, currSum, sum);
}

vector<vector<int>> subSum(vector<int> &arr, int sum) {
    vector<int> ds;
    allSUbSum(0, arr.size(), arr, ds, 0, sum);
    return ans;
}
