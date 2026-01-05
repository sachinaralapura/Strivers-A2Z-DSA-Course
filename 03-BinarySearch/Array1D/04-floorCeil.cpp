#include <bits/stdc++.h>
using namespace std;

template <typename T> T Floor(vector<T> a, T k) {
    int n = a.size();
    int low = 0;
    int high = n - 1;
    int ans = -1;
    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (a[mid] <= k) {
            ans = a[mid];
            low = mid + 1;
        } else
            high = mid - 1;
    }
    return ans;
}

template <typename T> T Ceil(vector<T> a, T k) {
    int n = a.size();
    int low = 0;
    int high = n - 1;
    int ans = -1;
    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (a[mid] >= k) {
            ans = a[mid];
            high = mid - 1;
        } else
            low = mid + 1;
    }
    return ans;
}

template <typename T> pair<T, T> FloorCeil(vector<T> a, T k) {
    T f = Floor(a, k);
    T c = Ceil(a, k);
    return make_pair(f, c);
}
