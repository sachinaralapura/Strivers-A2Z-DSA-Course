#include "Array2D/maxone.h"
#include <iostream>

int main() {
    vector<vector<int>> matrix = {{0, 0, 1}, {0, 0, 1}, {0, 0, 0}, {0, 1, 1}};
    cout << "The row with maximum no. of 1's is: " << maxOne_bs(matrix) << '\n';

    return 0;
}
