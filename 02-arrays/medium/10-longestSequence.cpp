#include <bits/stdc++.h>
using namespace std;
// Longest Consecutive Sequence in an Array
// Problem Statement : You are given an array of ‘N’ integers.
// You need to find the length of the longest sequence which contains the
// consecutive elements.
inline int longestSuccessiveElements(vector<int> &arr) {
    unordered_set<int> st;
    int maxCnt = 0;
    for (auto i : arr)
        st.insert(i);
    for (auto it : st) {
        if (st.find(it - 1) == st.end()) {
            int count = 1;
            int x = it;
            while (st.find(x + 1) != st.end()) {
                x = x + 1;
                count++;
            }
            maxCnt = max(maxCnt, count);
        }
    }
    return maxCnt;
}
