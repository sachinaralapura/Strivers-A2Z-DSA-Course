#include <bits/stdc++.h>
using namespace std;

int kthMissing(vector<int> a, int k) {
    int n = a.size();
    int low = 0;
    int high = n - 1;
    while (low <= high) {
        int mid = low + (high - low) / 2;
        int missingNumber = a[mid] - (mid + 1);
        if (missingNumber < k) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }
    return high + 1 + k;
}