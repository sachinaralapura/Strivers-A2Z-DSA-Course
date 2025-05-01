#include <bits/stdc++.h>
using namespace std;

int maxElement(vector<vector<int>> &mat, int rows, int col) {
    int max = INT_MIN;
    int maxrow = -1;
    for (int i = 0; i < rows; i++) {
        if (mat[i][col] > max) {
            max = mat[i][col];
            maxrow = i;
        }
    }
    return maxrow;
}

pair<int, int> findPeak(vector<vector<int>> mat) {
    int n = mat.size();
    int m = mat[0].size();

    int low = 0;
    int high = m - 1;
    while (low <= high) {
        int mid = low + (high - low) / 2;
        int maxrow = maxElement(mat, n, mid);
        int left = mid - 1 >= 0 ? mat[maxrow][mid - 1] : -1;
        int right = mid + 1 < m ? mat[maxrow][mid + 1] : -1;
        if (mat[maxrow][mid] > left && mat[maxrow][mid] > right)
            return {maxrow, mid};
        else if (mat[maxrow][mid] < left)
            high = mid - 1;
        else
            low = mid + 1;
    }

    return {-1, -1};
}