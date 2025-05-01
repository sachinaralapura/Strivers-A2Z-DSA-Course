#include <bits/stdc++.h>
using namespace std;

string LargestOddNumber(string s) {
    string largest = "";
    int n = s.length();
    for (int i = 0; i < n; i++) {
        for (int j = i; j < n; j++) {
            string sub = s.substr(i, j - i + 1);

            if (sub.length() > 1 && sub[0] == '0') {
                continue;
            }
            if (!sub.empty() && (sub.back() - '0') % 2 != 0) {
                if (largest.empty() || sub.length() > largest.length() ||
                    (sub.length() == largest.length() && sub > largest)) {
                    largest = sub;
                }
            }
        }
    }
    return largest;
}

string LargestOddNumber_Opt(string s) {
    string largest = "";
    int n = s.length();
    for (int i = n - 1; i >= 0; i--) {
        if ((s[i] - '0') % 2 != 0) {
            if (s[0] == '0') {
                return s.substr(1, i + 1);
            }
            return s.substr(0, i + 1);
        }
    }
    return "";
}