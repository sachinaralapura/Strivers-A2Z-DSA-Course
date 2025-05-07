#include <bits/stdc++.h>
#include <vector>
using namespace std;
class Solution {
  public:
    string word;
    vector<vector<char>> matrix;
    int n;
    int m;
    Solution(string w, vector<vector<char>> m) {
        this->word = w;
        this->matrix = m;
        this->n = matrix.size();
        this->m = matrix[0].size();
    }
    bool searchNext(int row, int col, int index);
    bool GetResult();
};

bool Solution::GetResult() {
    int index = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++)

            if (matrix[i][j] == word[index])
                if (searchNext(i, j, index))
                    return true;
    }

    return false;
}

bool Solution::searchNext(int row, int col, int index) {

    if (index == word.length())
        return true;

    if (row < 0 || col < 0 || row >= n || col >= m || matrix[row][col] == '#' or
        word[index] != matrix[row][col])
        return false;

    char ch = matrix[row][col];
    matrix[row][col] = '#';

    bool top = searchNext(row - 1, col, index + 1);
    bool left = searchNext(row, col - 1, index + 1);
    bool right = searchNext(row, col + 1, index + 1);
    bool bottom = searchNext(row + 1, col, index + 1);

    matrix[row][col] = ch;

    return top || left || right || bottom;
}
