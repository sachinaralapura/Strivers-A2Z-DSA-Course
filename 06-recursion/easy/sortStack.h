#include <bits/stdc++.h>
using namespace std;

void sortStack(stack<int> &stk, int x) {
    if (stk.empty() || x > stk.top()) {
        stk.push(x);
        return;
    }
    int temp = stk.top();
    stk.pop();
    sortStack(stk, x);
    stk.push(temp);
}

inline void sort(stack<int> &stk) {
    if (!stk.empty()) {
        int x = stk.top();
        stk.pop();
        sort(stk);
        sortStack(stk, x);
    }
}
