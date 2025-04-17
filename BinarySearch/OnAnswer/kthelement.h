#include <bits/stdc++.h>
using namespace std;

int kthElement(vector<int> &a, vector<int> &b, int k) {
    int ele = -1;
    int n = a.size();
    int m = b.size();
    int cnt = 0; // counter
    int i = 0, j = 0;
    while (i < m && j < n) {
        if (a[i] < b[j]) {
            if (cnt == k - 1) {
                ele = a[i];
                break;
            }
            cnt++;
            i++;
        } else {
            if (cnt == k - 1) {
                ele = b[j];
                break;
            }
            cnt++;
            j++;
        }
    }

    // copy the left-out elements:
    while (i < m) {
        if (cnt == k - 1)
            ele = a[i];
        cnt++;
        i++;
    }
    while (j < n) {
        if (cnt == k - 1)
            ele = b[j];
        cnt++;
        j++;
    }
    return ele;
}
