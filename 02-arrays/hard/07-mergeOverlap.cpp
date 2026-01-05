#include <bits/stdc++.h>
using namespace std;
// Merge Overlapping Sub - intervals
// Problem Statement : Given an array of intervals,
//  merge all the overlapping intervals and return an array of non - overlapping
//  intervals.
vector<vector<int>> mergeOverlappingIntervalsOpt(vector<vector<int>> &arr) {
    int n = arr.size();
    vector<vector<int>> ans;
    sort(arr.begin(), arr.end());
    for (int i = 0; i < n; i++)
        if (ans.empty() || ans.back()[1] < arr[i][0])
            ans.push_back(arr[i]);
        else
            ans.back()[1] = max(ans.back()[1], arr[i][1]);

    return ans;
}

// Merge two Sorted Arrays Without Extra Space
// Problem statement: Given two sorted arrays arr1[] and arr2[] of sizes n and m
// in non-decreasing order. Merge them in sorted order. Modify arr1 so that it
// contains the first N elements and modify arr2 so that it contains the last M
// elements.
void merge(vector<long long> &arr1, vector<long long> &arr2) {
    int n = arr1.size();
    int m = arr2.size();
    int left = n - 1;
    int right = 0;
    while (left >= 0 && right < m) {
        if (arr1[left] > arr2[right]) {
            swap(arr1[left], arr2[right]);
            left--;
            right++;
        } else
            break;
    }
    sort(arr1.begin(), arr1.end());
    sort(arr2.begin(), arr2.end());
}

void swapIfGreater(vector<long long> &arr1, vector<long long> &arr2, int index1, int index2) {
    if (arr1[index1] > arr2[index2])
        swap(arr1[index1], arr2[index2]);
}

void Merge_gap(vector<long long> &arr1, vector<long long> &arr2) {
    int n = arr1.size();
    int m = arr2.size();
    int len = (n + m);
    int gap = (len / 2) + (len % 2);

    while (gap > 0) {
        int left = 0;
        int right = left + gap;
        while (right < len) {
            // arr1 && arr2
            if (left < n && right >= n)
                swapIfGreater(arr1, arr2, left, right - n);
            // arr2 && arr2
            else if (left >= n)
                swapIfGreater(arr2, arr2, left - n, right - n);
            // arr1 && arr1
            else
                swapIfGreater(arr1, arr1, left, right);
            left++;
            right++;
        }
        if (gap == 1)
            break;
        gap = (gap / 2) + (gap % 2);
    }
}
