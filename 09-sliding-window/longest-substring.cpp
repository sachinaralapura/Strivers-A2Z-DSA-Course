// Given a String, find the length of longest substring without any repeating character.

#include <algorithm>
#include <climits>
#include <iostream>
#include <string>
#include <unordered_map>
#include <unordered_set>
using namespace std;

int longest_substring(string);
int longest_substring_opt(string);

int longest_substring(string str) {
    int len = str.length();
    if (len == 0)
        return 0;
    int l = 0;
    unordered_set<int> set;
    int maxLex = INT_MIN;

    for (int r = 0; r < len; r++) {
        if (set.contains(str[r])) {
            while (l < r && set.contains(str[r])) {
                set.erase(str[l]);
                l++;
            }
        }
        set.insert(str[r]);
        maxLex = max(maxLex, r - l + 1);
    }
    return maxLex;
}

int longest_substring_opt(string str) {
    int maxLen = INT_MIN;
    int len = str.length();
    int l = 0, r = 0;
    unordered_map<int, int> mpp;
    while (r < len) {
        if (mpp.contains(str[r]))
            l = mpp[str[r]] + 1;
        mpp[str[r]] = r;
        maxLen = max(maxLen, r - l + 1);
        r++;
    }
    return maxLen;
}

int main() {
    string str = "abcaabcdba";
    int maxlen = longest_substring(str);
    cout << maxlen << endl;
}
