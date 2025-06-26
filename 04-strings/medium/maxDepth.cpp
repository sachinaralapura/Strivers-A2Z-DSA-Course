#include <bits/stdc++.h>
using namespace std;

int maxDepth(string s) {
    int maxi = 0;
    int balance = 0;
    for (char ch : s) {
        if (ch == '(') {
            balance++;
            maxi = max(maxi, balance);
        }
        if (ch == ')')
            balance--;
        if (balance == 0) {
        }
    }
    return maxi;
}
