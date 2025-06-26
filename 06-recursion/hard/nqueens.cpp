#include <bits/stdc++.h>
using namespace std;
class Solution {
  public:
    int n;
    vector<string> board;
    vector<vector<string>> ans;
    Solution(int n) {
        this->n = n;
        string s(n, '#');
        this->board = vector<string>(n, s);
    }
    bool isSafe(int row, int col, int n, vector<string> &board);
    void Solve(int col, int n, vector<string> &board);
    vector<vector<string>> GetResult() {
        Solve(0, n, board);
        return ans;
    }
};

inline void Solution::Solve(int col, int n, vector<string> &board) {
    if (col == n) {
        ans.push_back(board);
        return;
    }

    for (int row = 0; row < n; row++) {
        if (isSafe(row, col, n, board)) {
            board[row][col] = 'Q';
            Solve(col + 1, n, board);
            board[row][col] = '#';
        }
    }
}

inline bool Solution::isSafe(int row, int col, int n, vector<string> &board) {
    if (col == 0)
        return true;
    for (int i = col; i >= 0; i--) {
        if (board[row][i] == 'Q') {
            return false;
        }
    }
    for (int i = row, j = col; i < n && j >= 0; i++, j--) {
        if (board[i][j] == 'Q') {
            return false;
        }
    }
    for (int i = row, j = col; i >= 0 && j >= 0; i--, j--) {
        if (board[i][j] == 'Q') {
            return false;
        }
    }
    return true;
}
