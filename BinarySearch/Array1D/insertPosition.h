// given a sorted array arr of distinct values and a target value x.
// You need to search for the index of the target value in the array.

// If the value is present in the array, then return its index.Otherwise, determine the index
// where it would be inserted in the array while maintaining the sorted order. basically find the
// lower bound;
#include <bits/stdc++.h>
using namespace std;

template <typename T> int InsertPostion(vector<T> a, int k) {
    int n = a.size();
    int l = 0;
    int h = n - 1;
    int i = n;
    while (l <= h) {
        int m = l + (h - l) / 2;
        if (a[m] >= k) {
            i = m;
            h = m - 1;
        } else
            l = m + 1;
    }
    return i;
}
