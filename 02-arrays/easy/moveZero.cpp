#include <bits/stdc++.h>
using namespace std;
void zeroToLeft(vector<int> &arr) {
    int n = arr.size();
    int j = -1;
    int i = 0;
    for (int k = 0; k < n; k++) {
        if (arr[k] == 0) {
            j = k;
            break;
        }
    }
    if (j == -1)
        return;
    for (int i = j + 1; i < n; i++) {
        if (arr[i] != 0) {
            int t = arr[i];
            arr[i] = arr[j];
            arr[j] = t;
            j++;
        }
    }
}
