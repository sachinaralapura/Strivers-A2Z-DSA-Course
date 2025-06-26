#include <bits/stdc++.h>
using namespace std;

bool checkPal(string &str, int low, int high) {
    while (low < high) {
        if (str[low] != str[high])
            return false;

        low++;
        high--;
    }
    return true;
}

string longestPalindrome(string str) {
    int n = str.size();
    // All substrings of length 1 are palindromes
    int maxLen = 1;
    int start = 0;
    for (int i = 0; i < n; i++) {
        for (int j = i; j < n; j++) {
            // check if the current substring is palindrome
            if (checkPal(str, i, j) && maxLen < (j - i + 1)) {
                start = i;
                maxLen = max(maxLen, (j - i + 1));
            }
        }
    }
    return str.substr(start, maxLen);
}