#include <bits/stdc++.h>
using namespace std;
void solve(int i, int n, string str, string &temp, vector<string> &ans) {
    if (i == n) {
        ans.push_back(temp);
        return;
    }
    // pick the next character
    temp = temp + str[i];
    solve(i + 1, n, str, temp, ans);
    temp.pop_back();
    solve(i + 1, n, str, temp, ans);
}

vector<string> allSubsquence(string str) {
    vector<string> ans;
    string temp = "";
    solve(0, str.length(), str, temp, ans);
    return ans;
}
