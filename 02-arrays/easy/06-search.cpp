// Given an array, and an element num the task is to find if num is present in the given array or
// not. If present print the index of the element or print -1.
#include <bits/stdc++.h>
using namespace std;
template <typename T> bool Linear_search(vector<T> &arr, int num) {
    int i;
    int n = arr.size();
    for (i = 0; i < n; i++) {
        if (arr[i] == num)
            return true;
    }
    return false;
}
