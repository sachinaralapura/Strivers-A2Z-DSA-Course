#include <bits/stdc++.h>
using namespace std;

bool isomorphic(string s, string t) {
    int n = s.size();
    if (n != t.size())
        return false;

    unordered_map<char, char> s_to_t;
    unordered_map<char, char> t_to_s;

    for (int i = 0; i < n; i++) {
        char char_s = s[i];
        char char_t = t[i];
        // check the mapping from s to t
        if (s_to_t.find(char_s) == s_to_t.end())
            s_to_t[char_s] = char_t;
        else if (s_to_t[char_s] != char_t)
            return false;

        // Check mapping from t to s (for reverse consistency)
        if (t_to_s.find(char_t) == t_to_s.end())
            t_to_s[char_t] = char_s;
        else if (t_to_s[char_t] != char_s)
            return false;
    }

    return true;
}