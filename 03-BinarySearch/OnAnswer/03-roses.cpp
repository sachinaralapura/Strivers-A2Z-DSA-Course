// Problem Statement: You are given 'N’ roses and
//  you are also given an array ' arr '  where ' arr[i] '  denotes that the ' ith '
// rose will bloom on the ' arr[i] th' day. You can only pick
// already bloomed roses that are adjacent to make a bouquet
//.You are also told that you require exactly 'k' adjacent bloomed roses to make a
// single bouquet.Findeast ‘m ' bouquets each  the minimum number of days required to make at
// lcontaining ' k' roses. Return -1 if it is not possible.

#include <bits/stdc++.h>
using namespace std;

int numberOfBouquet(vector<int> &a, int nthDay, int flowersNeeded) {
    int cnt = 0;
    int nOfBouquet = 0;
    for (int i = 0; i < a.size(); i++) {
        if (a[i] <= nthDay)
            cnt++;
        else {
            nOfBouquet += floor(cnt / flowersNeeded);
            cnt = 0;
        }
    }
    nOfBouquet += floor(cnt / flowersNeeded);
    return nOfBouquet;
}

bool possible(vector<int> &a, int nthDay, int flowersNeeded, int bouquestsNeeded) {
    return numberOfBouquet(a, nthDay, flowersNeeded) >= bouquestsNeeded;
}

int RosesGarden_brute(vector<int> a, int rosesperbouquet, int bouquets) {
    long long minimumFlowerNeed = rosesperbouquet * 1ll * bouquets * 1ll;
    int n = a.size();
    if (minimumFlowerNeed > n)
        return -1;

    int mini = INT_MAX;
    int maxi = INT_MIN;
    // find min and max element of a;
    for (int i = 0; i < n; i++) {
        mini = min(mini, a[i]);
        maxi = max(maxi, a[i]);
    }

    // run loop from mini to maxi
    for (int i = mini; i <= maxi; i++) {
        if (possible(a, i, rosesperbouquet, bouquets)) {
            return i;
        }
    }
    return -1;
}

int RosesGarden_bs(vector<int> a, int rosesperbouquet, int bouquets) {
    long long minimumFlowerNeed = rosesperbouquet * 1ll * bouquets * 1ll;
    int n = a.size();
    if (minimumFlowerNeed > n)
        return -1;

    int low = INT_MAX;
    int high = INT_MIN;
    // find min and max element of a;
    for (int i = 0; i < n; i++) {
        low = min(low, a[i]);
        high = max(high, a[i]);
    }

    while (low <= high) {
        int mid = low + (high - low) / 2;
        int numberOfBouquetsOnMid = numberOfBouquet(a, mid, rosesperbouquet);
        if (numberOfBouquetsOnMid >= bouquets) {
            high = mid - 1;
        } else {
            low = mid + 1;
        }
    }
    return low;
}
