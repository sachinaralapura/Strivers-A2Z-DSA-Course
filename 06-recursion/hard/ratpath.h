#include <bits/stdc++.h>
#include <vector>
using namespace std;
class Solution {
  public:
    string dlru = "DLRU";
    vector<string> ans;
    vector<vector<int>> grid;
    Solution(vector<vector<int>> grid) { this->grid = grid; }
    vector<string> GetResult() {
        string str = "";
        nextPath(0, 0, grid.size(), str);
        return ans;
    }

    void nextPath(int row, int col, int n, string path) {
        if (row == n - 1 && col == n - 1) {
            ans.push_back(path);
            return;
        }
        for (char direction : dlru) {

            grid[row][col] = -1;
            switch (direction) {
            case 'D':
                if (isPath(row + 1, col, n)) {
                    path.push_back(direction);
                    nextPath(row + 1, col, n, path);
                    path.pop_back();
                }
                break;
            case 'L':
                if (isPath(row, col - 1, n)) {
                    path.push_back(direction);
                    nextPath(row, col - 1, n, path);
                    path.pop_back();
                }
                break;
            case 'R':
                if (isPath(row, col + 1, n)) {
                    path.push_back(direction);
                    nextPath(row, col + 1, n, path);
                    path.pop_back();
                }
                break;
            case 'U':
                if (isPath(row - 1, col, n)) {
                    path.push_back(direction);
                    nextPath(row - 1, col, n, path);
                    path.pop_back();
                }
                break;
            }
            grid[row][col] = 1;
        }
    }
    bool isPath(int row, int col, int n) {
        if (row < 0 || col < 0 || row >= n || col >= n || this->grid[row][col] == 0 ||
            this->grid[row][col] == -1) {
            return false;
        }
        return true;
    }
};
