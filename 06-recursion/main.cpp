#include "hard/ratpath.h"
#include <iostream>
#include <vector>
using namespace std;

int main() {
    vector<string> ans;
    vector<vector<int>> m = {{1, 0, 0, 0}, {1, 1, 1, 1}, {1, 1, 0, 1}, {0, 1, 1, 1}};
    Solution *pp = new Solution(m);
    ans = pp->GetResult();
    for (auto it : ans) {
        cout << it << endl;
    }
    return 0;
}
