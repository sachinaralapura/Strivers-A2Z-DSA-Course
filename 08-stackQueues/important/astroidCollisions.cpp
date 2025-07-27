#include <bits/stdc++.h>
#include <cstdlib>
#include <iostream>
#include <stack>
#include <vector>
using namespace std;

stack<int> astroidCollisions(vector<int> arr) {
    // const n = arr.size();
    stack<int> stk;
    for (int a : arr) {
        if (a > 0)
            stk.push(a);
        else {
            while (!stk.empty() && stk.top() > 0 && stk.top() < abs(a))
                stk.pop();
            if (!stk.empty() && stk.top() == abs(a))
                stk.pop();
            else if (stk.empty())
                stk.push(a);
        }
    }
    return stk;
}

int main() {
    vector<int> arr = {4, 7, 1, 1, 2, -3, -7, 17, 15, -16};
    stack<int> stk = astroidCollisions(arr);

    while (!stk.empty()) {
        cout << stk.top() << endl;
        stk.pop();
    }
    return 0;
}
