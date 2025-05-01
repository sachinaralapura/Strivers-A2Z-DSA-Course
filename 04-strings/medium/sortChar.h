#include <bits/stdc++.h>
#include <iostream>
using namespace std;
#define ppi pair<int, char>
int countFrequency(string &s, char c) {
    int count = 0;
    for (int i = 0; i < s.length(); i++)
        if (s[i] == c)
            count++;

    return count;
}

vector<pair<int, char>> frequenySort(string s) {
    int n = s.length();
    vector<pair<int, char>> vp;
    for (int i = 0; i < n; i++)
        vp.push_back(make_pair(countFrequency(s, s[i]), s[i]));
    return vp;
}

class Compare {
  public:
    bool operator()(pair<int, char> below, pair<int, char> above) {
        if (below.first == above.first)
            return below.second > above.second;
        return below.first > above.first;
    }
};

string frequenySort_opt(string s) {
    unordered_map<char, int> mpp;
    priority_queue<ppi, vector<ppi>, Compare> minH;

    for (char ch : s)
        mpp[ch]++;

    string ans = "";

    for (auto m : mpp)
        minH.push({m.second, m.first});
    while (minH.size() > 0) {
        int freq = minH.top().first;
        char ch = minH.top().second;
        for (int i = 0; i < freq; i++) {
            ans += ch;
        }
        minH.pop();
    }
    return ans;
}