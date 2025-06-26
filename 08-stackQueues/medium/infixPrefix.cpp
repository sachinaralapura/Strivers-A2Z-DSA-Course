#include "precedence.h"
#include <algorithm>
#include <bits/stdc++.h>
#include <cctype>
#include <cstdio>
#include <string>
using namespace std;
string InfixToPrefix(string infix) {
    stack<char> stack;
    string result;

    // Reverse infix expression
    string reversed = infix;
    reverse(reversed.begin(), reversed.end());

    // Swap parentheses in reversed string
    for (char &c : reversed) {
        if (c == '(')
            c = ')';
        else if (c == ')')
            c = '(';
    }

    for (char c : reversed) {
        if (isalnum(c)) {
            result += c;
        } else {
            Operator op = getOperator(c);
            if (op == Operator::NONE && c != '(' && c != ')')
                continue;

            if (c == '(') {
                stack.push(c);
            } else if (c == ')') {
                while (!stack.empty() && stack.top() != '(') {
                    result += stack.top();
                    stack.pop();
                }
                if (!stack.empty())
                    stack.pop(); // Remove '('
            } else {
                while (!stack.empty() && stack.top() != '(' && comparePrecedence(stack.top(), c)) {
                    result += stack.top();
                    stack.pop();
                }
                stack.push(c);
            }
        }
    }

    while (!stack.empty()) {
        if (stack.top() != '(')
            result += stack.top();
        stack.pop();
    }

    // Reverse result to get prefix
    reverse(result.begin(), result.end());
    return result;
}
