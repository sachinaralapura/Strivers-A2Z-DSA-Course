#include <bits/stdc++.h>
using namespace std;
// 4 Sum | Find Quads that add up to a target value
// Problem Statement : Given an array of N integers, your task is to find
// unique quads that add up to give a target value. In short, you need to
// return an array of all the unique quadruplets[arr[a], arr[b], arr[c]
// ,arr[d]] such that their sum is equal to a given target.
vector<vector<int>> fourSum_Opt(vector<int> &arr, int target) {
    int n = arr.size();
    sort(arr.begin(), arr.end());
    vector<vector<int>> ans;

    for (int i = 0; i < n; i++) {
        if (i > 0 && arr[i - 1] == arr[i])
            continue;
        for (int j = i + 1; j < n; j++) {
            if (j > i + 1 && arr[j - 1] == arr[j])
                continue;
            int k = j + 1;
            int l = n - 1;
            while (k < l) {
                long long sum = (long long)arr[i] + arr[j] + arr[k] + arr[l];
                if (sum == target) {
                    vector<int> temp = {arr[i] + arr[j] + arr[k] + arr[l]};
                    ans.push_back(temp);
                    k++;
                    l--;
                    while (k < l && arr[k - 1] == arr[k])
                        k++;
                    while (k < l && arr[l + 1] == arr[l])
                        l--;
                } else if (sum < target)
                    k++;
                else
                    l--;
            }
        }
    }
    return ans;
}
