// Given two strings s and t of lengths m and n respectively, return the minimum window of s such that every character
// in t (including duplicates) is included in the window. If there is no such substring, return the empty string ""
#include <climits>
#include <iostream>
#include <string>
#include <unordered_map>
#include <utility>
using namespace std;

pair<int, int> brute(string str, string t) {
    int minCount = INT_MAX;
    int count = 0;
    int startIndex = 0;
    const int n = str.length();
    const int m = t.length();
    unordered_map<char, int> mpp;
    for (int i = 0; i < n; i++) {
        mpp.clear();
        count = 0;
        for (int k = 0; k < m; k++)
            mpp[t[k]]++;
        for (int j = i; j < n; j++) {
            if (mpp[str[j]] > 0) count++;
            mpp[str[j]]--;
            if (count == m) {
                if ((j - i + 1) < minCount) {
                    minCount = j - i + 1;
                    startIndex = i;
                }
                break;
            }
        }
    }
    return {startIndex, minCount};
}

pair<int, int> TwoPointer(string str, string t) {
    int minCount = INT_MAX;
    int count = 0;
    int startIndex = 0;
    const int n = str.length();
    const int m = t.length();

    unordered_map<char, int> mpp;
    int left = 0, right = 0;

    for (int k = 0; k < m; k++)
        mpp[t[k]]++;

    while (right < n) {
        if (mpp[str[right]] > 0) count += 1;
        mpp[str[right]]--;
        while (count == m) {
            if ((right - left + 1) < minCount) {
                minCount = right - left + 1;
                startIndex = left;
            }
            mpp[str[left]]++;
            if (mpp[str[left]] > 0) count -= 1;
            left += 1;
        }
        right += 1;
    }
    return {startIndex, minCount};
}

int main() {
    string str = "ddaaabbca";
    string t = "abc";
    pair<int, int> ans = TwoPointer(str, t);
    cout << str.substr(ans.first, ans.second) << endl;
    return 0;
}
