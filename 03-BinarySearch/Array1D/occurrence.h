// Problem Statement : You are given a sorted array containing N integers and a number X,
// you have to find the occurrences of X in the given array.
#include <bits/stdc++.h>
using namespace std;
int Occurrence_brute(vector<int> a, int k) {
    int o = 0;
    for (int i = 0; i < a.size(); i++) {
        if (k = a[i])
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

int LastOccurence(vector<int> a, int k) {
    int n = a.size();
    int low = 0;
    int high = n - 1;
    int index = -1;
    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (a[mid] == k) {
            index = mid;
            low = mid + 1;
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
    int lo = LastOccurence(a, k);
    return lo - fo + 1;
}