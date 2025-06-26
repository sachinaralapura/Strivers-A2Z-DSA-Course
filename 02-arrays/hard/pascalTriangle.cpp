#include <bits/stdc++.h>
using namespace std;

int nCr(int n, int r) {
    long long res = 1;
    for (int i = 0; i < r; i++) {
        res = res * (n - i);
        res = res / (i + 1);
    }
    return (int)(res);
}
// Program to generate Pascal's Triangle
// Variation 1 : Given row number r and column number c.Print the element at position(r, c)
// in Pascal’s triangle
int pascalTriangle(int r, int c) {
    int element = nCr(r - 1, c - 1);
    return element;
}

// Variation 2:  Print the n - th row of Pascal’s triangle.
void pascalTriangleRow(int n) {
    for (int i = 1; i <= n; i++) {
        cout << nCr(n - 1, i - 1) << " ";
    }
}

// Variation 3 : Given the number of rows n.Print the first n rows of Pascal’s
// triangle.
vector<vector<int>> pascalTriangle(int n) {
    vector<vector<int>> ans;
    // Store the entire pascal's triangle:
    for (int row = 1; row <= n; row++) {
        vector<int> tempLst; // temporary list
        for (int col = 1; col <= row; col++)
            tempLst.push_back(nCr(row - 1, col - 1));

        ans.push_back(tempLst);
    }
    return ans;
}
