// find rectangle with maximum largest area in n * m matrix.
#ifndef MAX_RECTANGLE
#define MAX_RECTANGLE
#include "../../00-common/common.h"
#include <iostream>
#include <vector>
using namespace common;

inline void PrintMatrix(const Matrix matrix) {
    for (auto it : matrix) {
        for (int i : it)
            std::cout << i << " ";
        std::cout << std::endl;
    }
}
Matrix computePrefixSum(const Matrix &);
int maxRectangle(Matrix);
#endif
