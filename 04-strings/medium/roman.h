#include <bits/stdc++.h>
using namespace std;

unordered_map<char, int> rmap = {{'I', 1},   {'V', 5},   {'X', 10},  {'L', 50},
                                 {'C', 100}, {'D', 500}, {'M', 1000}};

int RomanToInt(string s) {
    int n = s.size();
    int ans = 0;
    for (int i = 0; i < n; i++) {
        char ch = s[i];
        if (i + 1 < n && rmap[ch] < rmap[s[i + 1]]) {
            ans += rmap[s[i + 1]] - rmap[ch];
            i++;
        } else
            ans += rmap[ch];
    }
    return ans;
}

string IntToRoman(int num) {
    vector<std::pair<int, string>> romanMap = {
        {1000, "M"}, {900, "CM"}, {500, "D"}, {400, "CD"}, {100, "C"}, {90, "XC"}, {50, "L"},
        {40, "XL"},  {10, "X"},   {9, "IX"},  {5, "V"},    {4, "IV"},  {1, "I"}};

    string result = "";
    for (const auto &pair : romanMap) {
        while (num >= pair.first) {
            result += pair.second;
            num -= pair.first;
        }
    }
    return result;
}