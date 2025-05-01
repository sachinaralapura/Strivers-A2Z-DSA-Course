#include "Array2D/maxone.h"
#include "Array2D/search.h"

int main() {
    vector<vector<int>> matrix = {{1, 4, 7, 11, 15},
                                  {2, 5, 8, 12, 19},
                                  {3, 6, 9, 16, 22},
                                  {10, 13, 14, 17, 24},
                                  {18, 21, 23, 26, 30}};
    searchMatrix2_opt(matrix, 9) == true ? cout << "true\n" : cout << "false\n";
}
