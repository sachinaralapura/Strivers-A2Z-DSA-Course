#include <bits/stdc++.h>
using namespace std;

// 3 Sum : Find triplets that add up to a zero
// Problem Statement : Given an array of N integers, your task is to find unique
// triplets that add up to give a sum of zero.In short, you need to return an
// array of all the unique triplets[arr[a], arr[b], arr[c]] such that i != j, j
// != k, k != i, and their sum is equal to zero.
vector<vector<int>> threeSum_brute(vector<int> &arr) {
    int n = arr.size();
    set<vector<int>> st;
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            for (int k = j + 1; k < n; k++) {
                if (arr[i] + arr[j] + arr[k] == 0) {
                    vector<int> temp = {arr[i], arr[j], arr[k]};
                    sort(temp.begin(), temp.end());
                    st.insert(temp);
                }
            }
        }
    }
    vector<vector<int>> ans(st.begin(), st.end());
    return ans;
}

vector<vector<int>> threeSum_better(vector<int> &arr) {
    int n = arr.size();
    set<vector<int>> st;
    for (int i = 0; i < n; i++) {
        set<int> hashset;
        for (int j = i + 1; j < n; j++) {
            int third = -(arr[i] + arr[j]);
            if (hashset.find(third) != hashset.end()) {
                vector<int> temp = {arr[i], arr[j], third};
                sort(temp.begin(), temp.end());
                st.insert(temp);
            }
            hashset.insert(arr[j]);
        }
    }
    vector<vector<int>> ans(st.begin(), st.end());
    return ans;
}

vector<vector<int>> threeSum_Opt(vector<int> &arr) {
    int n = arr.size();
    sort(arr.begin(), arr.end());

    vector<vector<int>> ans;

    for (int i = 0; i < n; i++) {
        if (i != 0 && arr[i - 1] == arr[i])
            continue;
        int j = i + 1;
        int k = n - 1;
        while (j < k) {
            int sum = arr[i] + arr[j] + arr[k];
            if (sum > 0)
                k--;
            else if (sum < 0)
                j++;
            else {
                vector<int> temp = {arr[i], arr[j], arr[k]};
                ans.push_back(temp);
                j++;
                k--;
                while (j < k && arr[j - 1] == arr[j])
                    j++;
                while (j < k && arr[k + 1] == arr[k])
                    k--;
            }
        }
    }
    return ans;
}
