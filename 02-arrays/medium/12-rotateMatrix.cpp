#include <bits/stdc++.h>
using namespace std;
// Rotate Image by 90 degree
// Problem Statement : Given a matrix, your task is to rotate the matrix 90
// degrees clockwise.
inline vector<vector<int>> rotateMatrix(vector<vector<int>> &matrix) {
    int n = matrix.size();
    int m = matrix[0].size();
    // transpose the matrix
    for (int i = 0; i < n; i++)
        for (int j = 0; j < i; j++)
            swap(matrix[i][j], matrix[j][i]);

    for (int i = 0; i < n; i++)
        reverse(matrix[i].begin(), matrix[i].end());
    return matrix;
}

// Spiral Traversal of Matrix
inline vector<int> SpiralTraversal(vector<vector<int>> &matrix) {
    int n = matrix.size();
    int m = matrix[0].size();
    vector<int> ans;
    int left = 0;       // left 0 to m;
    int right = m - 1;  // right m to 0;
    int top = 0;        // top 0 to n;
    int bottom = n - 1; // botton n to 0;

    while (top <= bottom && left <= right) {
        // For moving left to right
        for (int i = left; i <= right; i++)
            ans.push_back(matrix[top][i]);

        top++;

        // For moving top to bottom
        for (int i = top; i <= bottom; i++)
            ans.push_back(matrix[i][right]);

        right--;

        // For moving right to left
        if (top <= bottom) {
            for (int i = right; i >= left; i--)
                ans.push_back(matrix[bottom][i]);

            bottom--;
        }

        if (left <= right) {
            for (int i = bottom; i >= top; i--)
                ans.push_back(matrix[i][left]);

            left++;
        }
    }
    return ans;
}
