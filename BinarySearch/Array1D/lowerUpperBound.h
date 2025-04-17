// Problem Statement: Given a sorted array of N integers and an integer x
//  find the lower bound of x.
// lower bound of x is 'i' at which arr[i] >= x
#include <bits/stdc++.h>
using namespace std;

template <typename T> T lowbound(vector<T> a, T target) {
    int n = a.size();
    int low = 0;
    int high = n - 1;
    int ans = n;
    while (low <= high) {
        int mid = (low + high) / 2;
        if (a[mid] >= target) {
            ans = mid;
            high = mid - 1;
        } else
            low = mid + 1;
    }
    return ans;
}

// Problem Statement: Given a sorted array of N integers and an integer x
//  find the upper bound of x.
// lower bound of x is 'i' at which arr[i] > x

template <typename T> T upperBound(vector<T> a, T target) {
    int n = a.size();
    int low = 0;
    int high = n - 1;
    int ans = n;
    while (low <= high) {
        int mid = (low + high) / 2;
        if (a[mid] > target) {
            ans = mid;
            high = mid - 1;
        } else
            low = mid + 1;
    }

    return ans;
}
