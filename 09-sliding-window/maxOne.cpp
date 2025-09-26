// Given a binary array nums and an integer k,
// return the maximum number of consecutive 1's
// in the array if you can flip at most k 0's.

#include <algorithm>
#include <climits>
#include <iostream>
#include <vector>
using namespace std;

int maxone_brute(const vector<int> &, int);
int maxone_two_pointer(const vector<int> &, int);
int maxone_two_pointer_opt(const vector<int> &, int);

int maxone_brute(const vector<int> &vec, int k) {
    const int n = vec.size();
    int maxLen = INT_MIN;
    for (int i = 0; i < n; i++) {
        int zeros = 0;
        for (int j = i; j < n; j++) {
            if (vec[j] == 0) zeros++;
            if (zeros <= k)
                maxLen = max(maxLen, j - i + 1);
            else
                break;
        }
    }
    return maxLen;
}

int maxone_two_pointer(const vector<int> &vec, int k) {
    int n = vec.size();
    int l = 0, r = 0;
    int maxLen = INT_MIN;
    int zeros = 0;
    while (r < n) {
        if (vec[r] == 0) zeros++;
        while (zeros > k) {
            if (vec[l] == 0) zeros--;
            l++;
        }
        if (zeros <= k) maxLen = max(maxLen, r - l + 1);
        r++;
    }
    return maxLen;
}

int maxone_two_pointer_opt(const vector<int> &vec, int k) {
    int n = vec.size();
    int l = 0, r = 0;
    int maxLen = INT_MIN;
    int zeros = 0;
    while (r < n) {
        if (vec[r] == 0) zeros++;
        if (zeros > k) {
            if (vec[l] == 0) zeros--;
            l++;
        }
        if (zeros <= k) maxLen = max(maxLen, r - l + 1);
        r++;
    }
    return maxLen;
}

int main() {
    vector<int> arr = {1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 0};
    int k = 2;
    int maxLen = maxone_two_pointer_opt(arr, k);
    cout << maxLen << endl;
}
