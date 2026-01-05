#include <bits/stdc++.h>
using namespace std;
// Set Matrix Zero
// Problem Statement : Given a matrix if an element in the matrix is 0
// then you will have to set its entire column and row to 0 and then return the matrix.
inline vector<vector<int>> zeroMatrix(vector<vector<int>> &matrix) {
    int rowSize = matrix.size();
    int colSize = matrix[0].size();

    vector<int> rows(rowSize, 0);
    vector<int> cols(colSize, 0);

    for (int i = 0; i < rowSize; i++) {
        for (int j = 0; j < colSize; j++) {
            if (matrix[i][j] == 0) {
                rows[i] = 1;
                cols[j] = 1;
            }
        }
    }

    for (int i = 0; i < rowSize; i++) {
        for (int j = 0; j < colSize; j++) {
            if (rows[i] || cols[j])
                matrix[i][j] = 0;
        }
    }
    return matrix;
}

inline vector<vector<int>> zeroMatrixOpt(vector<vector<int>> &matrix) {
    int rowSize = matrix.size();
    int colSize = matrix[0].size();

    // vector<int> rows(rowSize, 0); -> matrix[...][0]
    // vector<int> cols(colSize, 0); -> matrix[0][...]
    int cols0 = 1;
    for (int i = 0; i < rowSize; i++) {
        for (int j = 0; j < colSize; j++) {
            if (matrix[i][j] == 0) {
                matrix[i][0] = 0;
                if (j != 0)
                    matrix[0][j] = 0;
                else
                    cols0 = 0;
            }
        }
    }

    for (int i = 1; i < rowSize; i++) {
        for (int j = 1; j < colSize; j++) {
            if (matrix[i][j] != 0)
                if (matrix[i][0] == 0 || matrix[0][j] == 0)
                    matrix[i][j] = 0;
        }
    }

    if (matrix[0][0] == 0)
        for (int j = 1; j < colSize; j++)
            matrix[0][j] = 0;

    if (cols0 == 0)
        for (int i = 0; i < rowSize; i++)
            matrix[i][0] = 0;

    return matrix;
}
