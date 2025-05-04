#include <bits/stdc++.h>
#include <iostream>
using namespace std;
// Problem Statement : Given an array consisting of only 0s, 1s, and 2s.
// Write a program to in-place sort the array without using inbuilt sort
// functions.(Expected : Single pass - O(N) and constant space)
void sort012(vector<int> &arr) {
    int n = arr.size();
    int ones = 0, twos = 0, zeros = 0;
    for (int i = 0; i < n; i++) {
        if (arr[i] == 0)
            zeros++;
        else if (arr[i] == 1)
            ones++;
        else
            twos++;
    }
    for (int i = 0; i < zeros; i++)
        arr[i] = 0;
    for (int i = zeros; i < zeros + ones; i++)
        arr[i] = 1;
    for (int i = zeros + ones; i < n; i++)
        arr[i] = 2;
}

// Dutch National flag algorithm.
void sort012_pointers(vector<int> &arr) {
    int n = arr.size();
    int low = 0;
    int mid = 0;
    int high = n - 1;
    while (mid <= high) {
        if (arr[mid] == 0) {
            swap(arr[low], arr[mid]);
            low++;
            mid++;
        } else if (arr[mid] == 1)
            mid++;
        else {
            swap(arr[high], arr[mid]);
            high--;
        }
    }
}
