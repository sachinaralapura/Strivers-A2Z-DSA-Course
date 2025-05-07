#include <bits/stdc++.h>
using namespace std;

inline void GenAllParentheses(int n, int open, vector<string> &ans,
                              string current) {
    if (current.length() == 2 * n) {
        ans.push_back(current);
        return;
    }
    if (open < n)
        GenAllParentheses(n, open + 1, ans, current + '(');
    if (current.length() - open < open)
        GenAllParentheses(n, open, ans, current + ')');
}

inline vector<string> genParentheses(int n) {
    vector<string> ans;
    GenAllParentheses(n, 0, ans, "");
    return ans;
}
