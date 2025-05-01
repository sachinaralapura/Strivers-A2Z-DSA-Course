#include <bits/stdc++.h>
using namespace std;

bool canRotateTo(string s, string goal) {
    int n = s.size();
    if (n != goal.size())
        return false;
    if (s == goal)
        return true;

    return (s + s).find(goal) != string::npos;
}