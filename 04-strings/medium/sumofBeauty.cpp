#include <bits/stdc++.h>
using namespace std;

int beauty(string &str, int low, int high) {
    unordered_map<char, int> mpp;
    for (int i = low; i <= high; i++) {
        mpp[str[i]]++;
    }
    int maxi = INT_MIN;
    int mini = INT_MAX;
    for (auto it : mpp) {
        maxi = max(maxi, it.second);
        mini = min(mini, it.second);
    }
    return maxi - mini;
}

int SumOfBeauty(string str) {
    int n = str.size();
    int sum = 0;
    for (int i = 0; i < n; i++) {
        for (int j = i; j < n; j++) {
            sum += beauty(str, i, j);
        }
    }
    return sum;
}