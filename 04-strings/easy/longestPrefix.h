#include <bits/stdc++.h>
using namespace std;

string LongestPrefix(vector<string> &a) {
    sort(a.begin(), a.end());
    string first = a.front();
    string last = a.back();
    int minLength = min(first.size(), last.size());

    int i = 0;

    while (i < minLength && first[i] == last[i])
        i++;

    return first.substr(0, i);
}