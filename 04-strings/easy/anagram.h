#include <bits/stdc++.h>
using namespace std;

bool anagram(string &s, string &goal) {
    while (next_permutation(s.begin(), s.end())) {
        if (s == goal) {
            return true;
        }
    }
    return false;
}

bool anagram_opt(string &s, string &goal) {
    sort(s.begin(), s.end());
    sort(goal.begin(), goal.end());
    if (s == goal)
        return true;
    return false;
}