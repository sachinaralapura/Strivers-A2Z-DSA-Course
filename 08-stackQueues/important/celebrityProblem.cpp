#include "celebrityProblem.h"
#include <vector>
using namespace std;

int celebrity(Matrix matrix) {
    int n = matrix.size();
    int m = matrix[0].size();
    if (n != m) {
        throw MyError("expected n x n matrix");
    }
    vector<int> knowMe(n, 0);
    vector<int> IKnow(n, 0);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (matrix[i][j] == 1) {
                IKnow[i]++;
                knowMe[j]++;
            }
        }
    }
    for (int i = 0; i < n; i++) {
        if (knowMe[i] == n - 1 && IKnow[i] == 0) {
            return i;
        }
    }
    return -1;
}

int celebrityOpt(Matrix matrix) {
    int n = matrix.size();
    int m = matrix[0].size();
    if (n != m) {
        throw MyError("expected n x n matrix");
    }
    int top = 0;
    int down = n - 1;
    while (top < down) {
        if (matrix[top][down] == 1)
            top++;
        else if (matrix[down][top] == 1)
            down--;
        else {
            top++;
            down--;
        }
    }
    if (top == down) {
        for (int i = 0; i < n; i++) {
            if (i == top)
                continue;
            if (matrix[top][i] != 0 || matrix[i][top] != 1)
                return -1;
        }
        return top;
    }
    return -1;
}

// int main() { Matrix mat = {{0, 1, 1, 0}, {0, 0, 0, 0}, {0, 1, 0, 0}, {1, 1, 0, 0}};
//     int res = celebrityOpt(mat);
//     cout << "Celebrity : " << res << endl;
// }
