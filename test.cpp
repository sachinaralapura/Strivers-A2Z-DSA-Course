#include <bits/stdc++.h>
#include <iostream>
#include <string>
#include <unordered_map>
const int MAX_CHAR = 26;
using namespace std;

string getHash(string &s) {
    unordered_map<int, int> mpp;
    string hash;
    vector<int> freq(MAX_CHAR, 0);
    // Count frequency of each character
    for (char ch : s)
        freq[ch - 'a'] += 1;
    // Append the frequency to construct the hash
    for (int i = 0; i < MAX_CHAR; i++) {
        hash.append(to_string(freq[i]));
        hash.append("$");
    }
    return hash;
}

int main(int argc, char const *argv[]) {
    // string str = "sachin";
    // string ans = getHash(str);
    // cout << ans << endl;

    int n = 3;
    int k = 2;
    cout << (n << k) << endl;
    cout << (n * (1 << k)) << endl;
    return 0;
}

// https://leetcode.com/problems/valid-parentheses/description/?envType=problem-list-v2&envId=stack

// https://leetcode.com/problems/longest-valid-parentheses/description/?envType=problem-list-v2&envId=stack

// https://leetcode.com/problems/maximum-subarray/description/

// https://leetcode.com/problems/minimum-cost-for-tickets/

// https://leetcode.com/problems/ones-and-zeroes/
