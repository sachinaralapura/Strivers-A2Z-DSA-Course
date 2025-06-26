// Problem Statement : You are given an array 'arr' of size 'n' which denotes the position of
// stalls.You are also given an integer 'k' which denotes the number of aggressive cows.You are
// given the task of assigning stalls to 'k' cows such that the minimum distance between any two
// of them is the maximum  possible.Find the maximum possible minimum distance.

#include <bits/stdc++.h>
using namespace std;

bool possible(vector<int> a, int distance, int cows) {
    int n = a.size();
    int cntCows = 1;
    int last = a[0];
    for (int i = 1; i < n; i++)
        if (a[i] - last >= distance) {
            last = a[i];
            cntCows++;
        }

    if (cntCows >= cows)
        return true;
    return false;
}

int AggressiveCows(vector<int> a, int cows) {
    int low = 0;
    int high = a.size();
    sort(a.begin(), a.end());
    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (possible(a, mid, cows)) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }
    return high;
}