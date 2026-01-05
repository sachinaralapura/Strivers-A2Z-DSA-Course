// Given an array/list of length ‘N’, where the array/list represents the boards and each element of
// the given array/list represents the length of each board. Some ‘K’ numbers of painters are
// available to paint these boards. Consider that each unit of a board takes 1 unit of time to
// paint. You are supposed to return the area of the minimum time to get this job done of painting
// all the ‘N’ boards under the constraint that any painter will only paint the continuous sections
// of boards.
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
