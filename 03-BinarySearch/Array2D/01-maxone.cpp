#include <bits/stdc++.h>
using namespace std;

int maxOne_brute(vector<vector<int>> mat) {
    int rows = mat.size();
    int cols = mat[0].size();
    // cout << rows << "  " << cols << endl;
    int maxi = 0;
    int index = -1;
    for (int i = 0; i < rows; i++) {
        int maxone = 0;
        for (int j = 0; j < cols; j++) {
            if (mat[i][j] == 1) {
                maxone = cols - j;
                break;
            }
        }
        if (maxi < maxone) {
            maxi = maxone;
            index = i;
        }
    }
    return index;
}

int lowerBound(vector<int> a) {
    int n = a.size();
    int low = 0;
    int high = n - 1;
    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (a[mid] >= 1)
            high = mid - 1;
        else
            low = mid + 1;
    }
    return low;
}

int maxOne_bs(vector<vector<int>> mat) {
    int rows = mat.size();
    int cols = mat[0].size();
    int index = -1;
    int count_max = 0;
    for (int i = 0; i < rows; i++) {
        int count = cols - lowerBound(mat[i]);
        if (count > count_max) {
            count_max = count;
            index = i;
        }
    }
    return index;
}
