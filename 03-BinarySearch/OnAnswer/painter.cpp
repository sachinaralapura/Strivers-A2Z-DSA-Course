#include <bits/stdc++.h>
using namespace std;

int countPartitions(vector<int> &a, int maximum) {
    int partition = 1;
    long long sum = 0;
    for (int i = 0; i < a.size(); i++) {
        if (sum + a[i] <= maximum) {
            sum += a[i];
        } else {
            partition++;
            sum = a[i];
        }
    }
    return partition;
}

int painterPartition(vector<int> a, int painters) {
    int n = a.size();
    if (painters > n)
        return -1;
    int low = *max_element(a.begin(), a.end());
    int high = accumulate(a.begin(), a.end(), 0);
    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (countPartitions(a, mid) <= painters) {
            high = mid - 1;
        } else {
            low = mid + 1;
        }
    }
    return low;
}