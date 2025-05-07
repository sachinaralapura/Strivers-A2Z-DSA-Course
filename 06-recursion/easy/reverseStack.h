#include <bits/stdc++.h>
using namespace std;
inline void insert_bottom(stack<int> &stk, int x) {
    if (stk.empty()) {
        stk.push(x);
        return;
    }
    int temp = stk.top();
    stk.pop();
    insert_bottom(stk, x);
    stk.push(temp);
}

inline void reverseStack(stack<int> &stk) {
    if (stk.empty())
        return;
    int temp = stk.top();
    stk.pop();
    reverseStack(stk);
    insert_bottom(stk, temp);
}
