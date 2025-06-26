#include "precedence.h"
#include <bits/stdc++.h>
#include <cctype>
#include <stack>
#include <string>
using namespace std;

string PostfixToInfix(string postfix) {
    string infix;
    stack<string> st;

    for (char c : postfix) {
        if (isalnum(c))
            st.push(string(1, c));
        else {
            Operator op = getOperator(c);
            if (op == Operator::NONE)
                continue;
            if (st.size() < 2)
                return "Invalid Expression";

            string operand2 = st.top();
            st.pop();
            string operand1 = st.top();
            st.pop();

            string expression = "(" + operand1 + c + operand2 + ")";
            st.push(expression);
        }
    }
    return st.empty() ? "Empty expression" : st.top();
}
