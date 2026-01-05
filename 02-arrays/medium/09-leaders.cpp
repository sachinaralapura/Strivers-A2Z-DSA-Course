#include <bits/stdc++.h>
using namespace std;
// Leaders in an Array
// Problem Statement : Given an array,print all the elements which are
// leaders. A Leader is an element that is greater than all of the elements on its
// right side in the array.
inline vector<int> printLeadersBruteForce(vector<int> &arr) {
    int n = arr.size();
    vector<int> ans;
    for (int i = 0; i < n; i++) {
        bool flag = true;
        for (int j = i + 1; j < n; j++)
            if (arr[i] < arr[j]) {
                flag = false;
                break;
            }
        if (flag)
            ans.push_back(arr[i]);
    }
    return ans;
}

inline vector<int> printLeadersOptimal(vector<int> &arr) {
    int n = arr.size();
    vector<int> ans;
    int maxi = arr[n - 1];
    ans.push_back(arr[n - 1]);
    for (int i = n - 2; i >= 0; i--) {
        if (arr[i] > maxi) {
            ans.push_back(arr[i]);
            maxi = max(maxi, arr[i]);
        }
    }
    return ans;
}
