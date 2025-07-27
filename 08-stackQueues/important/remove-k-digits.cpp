#ifndef REMOVE_K_DIGITS
#define REMOVE_K_DIGITS
#include <algorithm>
#include <bits/stdc++.h>
#include <iostream>
#include <stack>
#include <string>
using namespace std;

string removeKDigits(string arr, int k) {
    stack<int> stk;
    for (auto it : arr) {
        while (!stk.empty() && k > 0 && (stk.top()) > (it - '0')) {
            stk.pop();
            k--;
        }
        stk.push(it - '0');
    }
    while (!stk.empty() && k > 0) {
        stk.pop();
        k--;
    }
    if (stk.empty())
        return "0";

    string res = "";
    while (!stk.empty()) {
        res.append(to_string(stk.top()));
        stk.pop();
    }
    reverse(res.begin(), res.end());
    return res;
}

int main() {
    string str = "141234";
    string res = removeKDigits(str, 3);
    cout << res << endl;
}
#endif
