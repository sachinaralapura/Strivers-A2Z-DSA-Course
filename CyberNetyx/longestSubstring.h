// https://takeuforward.org/data-structure/length-of-longest-substring-without-any-repeating-character/
#include <bits/stdc++.h>
using namespace std;

int usingSet(string str) {
    if (str.size() == 0)
        return 0;
    int maxans = INT_MIN;
    int n = str.length();
    unordered_set<char> set;
    int left = 0;
    for (int right = 0; right < n; right++) {
        if (set.find(str[right]) != set.end()) {
            while (left < right && set.find(str[right]) != set.end()) {
                set.erase(str[left]);
                left++;
            }
        }
        set.insert(str[right]);
        maxans = max(maxans, right - left + 1);
    }
    return maxans;
}

int usingMap(string s) {
    vector<int> mpp(256, -1);

    int left = 0, right = 0;
    int n = s.size();
    int len = 0;
    while (right < n) {
        if (mpp[s[right]] != -1)
            left = max(mpp[s[right]] + 1, left);

        mpp[s[right]] = right;

        len = max(len, right - left + 1);
        right++;
    }
    return len;
}