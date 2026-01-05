// You are the owner of a Shipment company. You use conveyor belts to ship packages from one port to
// another. The packages must be shipped within 'd' days. The weights of the packages are given in
// an array 'of weights'. The packages are loaded on the conveyor belts every day in the same order
// as they appear in the array. The loaded weights must not exceed the maximum weight capacity of
// the ship. Find out the least-weight capacity so that you can ship all the packages within 'd'
// days .
#include <bits/stdc++.h>
using namespace std;

int findDays(vector<int> &a, int capacity) {
    int days = 1;
    int load = 0;
    for (int i = 0; i < a.size(); i++) {
        if ((load + a[i]) > capacity) {
            days++;
            load = a[i];
        } else
            load += a[i];
    }
    return days;
}

int Shipment(vector<int> a, int days) {
    int low = *max_element(a.begin(), a.end());
    int high = accumulate(a.begin(), a.end(), 0);

    while (low <= high) {
        int mid = low + (high - low) / 2;
        int daysRequired = findDays(a, mid);
        if (daysRequired > days) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }
    return low;
}
