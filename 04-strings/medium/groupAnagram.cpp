#include <bits/stdc++.h>
#include <string>
#include <unordered_map>
#include <vector>
using namespace std;

const int MAX_CHAR = 26;

string inline getHash(string &str) {
    string hash;
    vector<int> freq(MAX_CHAR, 0);
    // count the frequenices
    for (auto it : str) {
        freq[it - 'a'] += 1;
    }
    for (auto it : freq) {
        hash.append(to_string(it));
        hash.append("$");
    }
    return hash;
}

vector<vector<string>> inline groupAnagram(vector<string> &arr) {
    vector<vector<string>> ans;
    unordered_map<string, int> mpp;
    for (string it : arr) {
        string key = getHash(it);

        if (mpp.find(key) == mpp.end()) {
            mpp[key] = ans.size();
            ans.push_back({});
        }
        ans[mpp[key]].push_back(it);
    }
    return ans;
}
