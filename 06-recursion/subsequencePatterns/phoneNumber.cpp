// Letter Combinations of a Phone Number
// Given a string consisting of digits from 2 to 9 (inclusive). Return all possible letter
// combinations that the number can represent.
// Mapping of digits to letters is given in first example.
// Examples:
// Input : digits = "34"
// Output : [ "dg", "dh", "di", "eg", "eh", "ei", "fg", "fh", "fi" ]
// Explanation : The 3 is mapped with "def" and 4 is mapped with "ghi".
#include <bits/stdc++.h>
using namespace std;
vector<string> char_map = {
    "0",    // 0
    "1",    // 1
    "abc",  // 2
    "def",  // 3
    "ghi",  // 4
    "jkl",  // 5
    "mno",  // 6
    "pqrs", // 7
    "tuv",  // 8
    "wxyz"  // 9}
};

vector<string> result;

void backTrack(int index, int n, string str, string currStr) {
    if (index == n) {
        result.push_back(currStr);
        return;
    }
    string numberString = char_map[str[index] - '0'];
    for (char ch : numberString) {
        backTrack(index + 1, n, str, currStr + ch);
    }
}
vector<string> phoneNumber(string str) {
    if (!str.empty()) {
        string currStr = "";
        backTrack(0, str.length(), str, currStr);
        return result;
    }
    return result;
}
