#include <bits/stdc++.h>
using namespace std;
// Problem Statement : Given an array of N integers,
//  write a program to return an element that occurs more than N / 2 times in the given array.
//  You may consider that such an element always exists in the array.
inline int majorityElement(vector<int> &arr) {
    int n = arr.size();
    map<int, int> mpp;
    for (int i = 0; i < n; i++) {
        mpp[arr[i]]++;
    }
    for (auto i : mpp) {
        if (i.second > floor(n / 2))
            return i.first;
    }
    return -1;
}

// Optimal Approach : Moore’s Voting Algorithm:
// https://takeuforward.org/data-structure/find-the-majority-element-that-occurs-more-than-n-2-times/
inline int majorityElement_moore(vector<int> &arr) {
    int n = arr.size();
    int element = arr[0];
    int count = 0;
    for (int i = 0; i < n; i++) {
        if (arr[i] == element)
            count++;
        else
            count--;

        if (count == 0) {
            count = 1;
            element = arr[i];
        }
    }
    int cnt1 = 0;
    for (int i = 0; i < n; i++) {
        if (arr[i] == element)
            cnt1++;
    }
    if (cnt1 > (n / 2))
        return element;
    return -1;
}
