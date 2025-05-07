#include "hard/wordsearch.h"
#include <iostream>
#include <vector>
using namespace std;

int main() {
    vector<vector<string>> ans;
    vector<vector<char>> board{{'A', 'B', 'C', 'E'}, {'S', 'F', 'C', 'S'}, {'A', 'D', 'E', 'E'}};
    string word = "ABCCED";
    Solution *pp = new Solution(word, board);
    bool answer = pp->GetResult();
    cout << answer << endl;
    return 0;
}
