#include <bits/stdc++.h>
using namespace std;

string removeOuterParentheses(string str) {
    int balance = 0;
    string ans = "";
    for (int i = 0; i < str.length(); i++) {
        if (str[i] == ')')
            balance--;

        if (balance != 0)
            ans.push_back(str[i]);

        if (str[i] == '(')
            balance++;
    }
    return ans;
}