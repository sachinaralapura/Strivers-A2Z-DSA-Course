#include <bits/stdc++.h>
#include <iostream>
using namespace std;

bool searchMatrix(vector<vector<int>> mat, int target) {
    int rows = mat.size();
    int cols = mat[0].size();
    int n = rows * cols;
    int low = 0;
    int high = n - 1;
    while (low <= high) {
        int mid = low + (high - low) / 2;
        int row = mid / cols;
        int col = mid % cols;
        int midEle = mat[row][col];
        if (midEle == target)
            return true;
        else if (midEle < target)
            low = mid + 1;
        else
            high = mid - 1;
    }
    return false;
}

bool searchMatrix2(vector<vector<int>> mat, int target) {
    int rows = mat.size();
    int cols = mat[0].size();
    for (int i = 0; i < rows; i++) {
        bool exists = binary_search(mat[i].begin(), mat[i].end(), target);
        if (exists) {
            return true;
        }
    }
    return false;
}

bool searchMatrix2_opt(vector<vector<int>> mat, int target) {
    int rows = mat.size();
    int cols = mat[0].size();
    int low = 0;
    int high = cols - 1;
    while (low < rows && high >= 0) {
        if (mat[low][high] == target)
            return true;
        else if (mat[low][high] < target)
            low++;
        else
            high--;
    }
    return false;
}