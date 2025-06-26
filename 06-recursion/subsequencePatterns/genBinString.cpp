#include <bits/stdc++.h>
using namespace std;

vector<vector<int>> vv;

void genAllBinaryStrings(int n, vector<int> &arr, int i) {
    if (i == n) {
        vv.push_back(arr);
        return;
    }

    arr[i] = 0;
    genAllBinaryStrings(n, arr, i + 1);
    arr[i] = 1;
    genAllBinaryStrings(n, arr, i + 1);
}

vector<vector<int>> genBin(int n) {
    vector<int> arr(n);
    genAllBinaryStrings(n, arr, 0);
    return vv;
}
