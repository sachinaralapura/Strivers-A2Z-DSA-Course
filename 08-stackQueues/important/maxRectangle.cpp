#include "maxRectangle.h"
#include "largestInHistogram.h"
#include <algorithm>
using namespace std;

Matrix computePrefixSum(const Matrix &matrix) {
    int n = matrix.size();
    int m = matrix[0].size();
    Matrix prefixSumMatrix(n, vector<int>(m, 0));
    for (int j = 0; j < m; j++) {
        int sum = 0;
        for (int i = 0; i < n; i++) {
            sum += matrix[i][j];
            if (matrix[i][j] == 0)
                sum = 0;
            prefixSumMatrix[i][j] = sum;
        }
    }
    return prefixSumMatrix;
}

int maxRectangle(const Matrix matrix) {
    int n = matrix.size();
    int maxS = 0;
    if (n == 0)
        return -1;
    int m = matrix[0].size();
    Matrix prefixSumMatrix = computePrefixSum(matrix);
    for (auto it : prefixSumMatrix) {
        maxS = max(maxS, LargestInHistogramOpt(it));
    }
    return maxS;
}

int main() {
    Matrix matrix;
    matrix.push_back({1, 0, 1, 0, 1});
    matrix.push_back({1, 0, 1, 1, 1});
    matrix.push_back({1, 1, 1, 1, 1});
    matrix.push_back({1, 0, 0, 1, 0});
    cout << "Largest recantangle is : " << maxRectangle(matrix) << endl;
    return 0;
}
