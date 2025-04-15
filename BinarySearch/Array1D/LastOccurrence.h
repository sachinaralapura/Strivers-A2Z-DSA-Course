// Given a sorted array of N integers, write a program to find the index of the last occurrence of
// the target key.If the target is not found then return -1.
#include <bits/stdc++.h>
using namespace std;

template <typename T> int LastOccurrence_brute(vector<T> a, T k) {
    int n = a.size();
    for (int i = n - 1; i >= 0; i--) {
        if (a[i] == k)
            return i;
    }
    return -1;
}

template <typename T> int LastOccurrence_opt(vector<T> a, T k) {
    int n = a.size();
    int low = 0;
    int high = n - 1;
    int res = -1;
    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (a[mid] == k) {
            res = mid;
            low = mid + 1;
        } else if (a[mid] > k)
            high = mid - 1;
        else
            low = mid + 1;
    }
    return res;
}