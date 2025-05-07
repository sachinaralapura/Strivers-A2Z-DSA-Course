// https://takeuforward.org/data-structure/check-for-balanced-parentheses/
#include <bits/stdc++.h>
using namespace std;

inline bool validParentheses(string str) {
    int balance = 0;
    for (char ch : str) {
        if (ch == '(')
            balance++;
        else if (ch == ')')
            balance--;
    }

    if (balance == 0)
        return true;
    return false;
}

inline bool MultivalidParentheses(string str) {
    stack<char> st;

    for (auto it : str) {
        if (it == '(' || it == '[' || it == '{')
            st.push(it);

        else {
            if (st.size() == 0)
                return false;
            char ch = st.top();
            st.pop();

            if ((it == ')' and ch == '(') or (it == ']' and ch == '[') or
                (it == '}' and ch == '{'))
                continue;
            else
                return false;
        }
    }
    return st.empty();
}

inline int LongestValidParentheses(string str) {
    int n = str.size();
    stack<int> stk;
    int maxi = 0;
    stk.push(-1);
    for (int i = 0; i < n; i++) {
        char ch = str[i];
        if (ch == '(') {
            stk.push(i);
        } else {
            stk.pop();
            if (stk.empty()) {
                stk.push(i);
            } else {
                int len = i - stk.top();
                maxi = max(maxi, len);
            }
        }
    }
    return maxi;
}
