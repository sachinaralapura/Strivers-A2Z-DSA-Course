#include <bits/stdc++.h>
using namespace std;
// // Stock Buy And Sell
// // Problem Statement : You are given an array of prices where prices[i] is
// the price of a given stock on an ith day.
inline int BuySell(vector<int> &arr) {
    int n = arr.size();
    int maxDiff = 0;
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (arr[j] > arr[i]) {
                maxDiff = max(maxDiff, arr[j] - arr[i]);
            }
        }
    }
    return maxDiff;
}

inline int BuySell_Opt(vector<int> &arr) {
    int n = arr.size();
    int maxProfit = 0;
    int minPrice = INT_MAX;
    for (int i = 0; i < n; i++) {
        minPrice = min(arr[i], minPrice);
        maxProfit = max(maxProfit, arr[i] - minPrice);
    }
    return maxProfit;
}
