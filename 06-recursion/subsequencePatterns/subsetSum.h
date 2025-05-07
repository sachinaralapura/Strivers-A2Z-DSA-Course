#include <algorithm>
#include <bits/stdc++.h>
#include <vector>
using namespace std;

inline void subSum(int index, int n, int sum, vector<int> &ds, vector<int> &arr) {
    if (index == n) {
        ds.push_back(sum);
        return;
    }
    subSum(index + 1, n, sum + arr[index], ds, arr);
    subSum(index + 1, n, sum, ds, arr);
}

inline vector<int> subsetSum(vector<int> arr) {
    vector<int> ds;
    subSum(0, arr.size(), 0, ds, arr);
    sort(ds.begin(), ds.end());
    return ds;
}
