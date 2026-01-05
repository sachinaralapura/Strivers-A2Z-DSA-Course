// Problem Statement: A monkey is given ‘n’ piles of bananas,
// whereas the 'ith' pile has ‘a[i]’ bananas. An integer ‘h’ is also given,
// which denotes the time (in hours) for all the bananas to be eaten.

// Each hour, the monkey chooses a non-empty pile of bananas and eats ‘k’ bananas.
// If the pile contains less than ‘k’ bananas, then the monkey consumes all the bananas
// and won’t eat any more bananas in that hour.

// Find the minimum number of bananas ‘k’ to eat per hour so that the monkey can eat
// all the bananas within ‘h’ hours.
#include <bits/stdc++.h>
using namespace std;

int findMax(vector<int> &v) {
    int maxi = INT_MIN;
    int n = v.size();
    // find the maximum:
    for (int i = 0; i < n; i++) {
        maxi = max(maxi, v[i]);
    }
    return maxi;
}

int totalHours(vector<int> &a, int k) {
    int hours = 0;
    for (int i = 0; i < a.size(); i++) {
        hours += ceil((double)a[i] / (double)k);
    }
    return hours;
}

int koto_brute(vector<int> a, int hour) {
    int high = findMax(a);
    for (int i = 1; i <= high; i++) {
        int reqHours = totalHours(a, i);
        if (reqHours <= hour) {
            return i;
        }
    }
    return high;
}

int koto_bs(vector<int> a, int hour) {
    int low = 1;
    int high = findMax(a);
    while (low <= high) {
        int mid = low + (high - low) / 2;
        int midk = totalHours(a, mid);
        if (midk <= hour) {
            high = mid - 1;
        } else if (midk > hour) {
            low = mid + 1;
        }
    }
    return low;
}
