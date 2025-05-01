// https://takeuforward.org/data-structure/check-for-balanced-parentheses/
#include <bits/stdc++.h>
using namespace std;

bool validParentheses(string str) {
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

bool MultivalidParentheses(string str) {
    stack<char> st;

    for (auto it : str) {
        if (it == '(' || it == '[' || it == '{')
            st.push(it);

        else {
            if (st.size() == 0)
                return false;
            char ch = st.top();
            st.pop();

            if ((it == ')' and ch == '(') or (it == ']' and ch == '[') or (it == '}' and ch == '{'))
                continue;
            else
                return false;
        }
    }
    return st.empty();
}