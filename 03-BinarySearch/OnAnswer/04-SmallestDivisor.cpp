// You are given an array of integers 'arr' and an integer i.e. a threshold value 'limit'. Your task
// is to find the smallest positive integer divisor, such that upon dividing all the elements of the
// given array by it, the sum of the division's result is less than or equal to the given threshold
// value.
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
int sumOfDivisor(vector<int> a, int divisor) {

    int sum = 0;
    for (int i = 0; i < a.size(); i++) {
        sum += ceil((double)(a[i]) / (double)(divisor));
    }
    return sum;
}

bool possible(vector<int> a, int divisor, int limit) {
    return sumOfDivisor(a, divisor) <= limit;
}

int SmallestDivisor(vector<int> a, int limit) {
    int low = 1;
    int high = findMax(a);
    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (possible(a, mid, limit)) {
            high = mid - 1;
        } else {
            low = mid + 1;
        }
    }
    return low;
}
