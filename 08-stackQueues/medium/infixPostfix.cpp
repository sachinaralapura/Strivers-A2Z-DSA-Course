#include "precedence.h"
#include <bits/stdc++.h>
#include <cctype>
#include <stack>
#include <string>
using namespace std;

string InfixPostfix(string infix) {
    stack<char> stk;
    string postfix;

    for (char c : infix) {
        if (c == ' ')
            continue;
        if (std::isalnum(c)) {
            postfix += c;
        }
        if (c == '(') {
            stk.push(c);
        } else if (c == ')') {
            while (!stk.empty() && stk.top() != '(') {
                postfix += stk.top();
                stk.pop();
            }
            if (!stk.empty())
                stk.pop(); // Remove '('
        } else {
            Operator op = getOperator(c);
            if (op == Operator::NONE)
                continue;
            else {
                while (!stk.empty() && comparePrecedence(stk.top(), c)) {
                    postfix += stk.top();
                    stk.pop();
                }
                stk.push(c);
            }
        }
    }

    while (!stk.empty()) {
        if (stk.top() != '(')
            postfix += stk.top();
        stk.pop();
    }
    return postfix;
}
