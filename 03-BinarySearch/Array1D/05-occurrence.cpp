// Problem Statement : You are given a sorted array containing N integers and a number X,
// you have to find the occurrences of X in the given array.
#include <bits/stdc++.h>
using namespace std;

// Given a sorted array of N integers, write a program to find the index of the last occurrence of
// the target key.If the target is not found then return -1.
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

int Occurrence_brute(vector<int> a, int k) {
    int o = 0;
    for (int i = 0; i < a.size(); i++) {
        if (k == a[i])
            o++;
    }
    return o;
}

int FirstOccurence(vector<int> a, int k) {
    int n = a.size();
    int low = 0;
    int high = n - 1;
    int index = -1;
    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (a[mid] == k) {
            index = mid;
            high = mid - 1;
        } else if (a[mid] < k) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }
    return index;
}

int Occurrence_opt(vector<int> a, int k) {
    int fo = FirstOccurence(a, k);
    int lo = LastOccurrence_opt(a, k);
    return lo - fo + 1;
}
