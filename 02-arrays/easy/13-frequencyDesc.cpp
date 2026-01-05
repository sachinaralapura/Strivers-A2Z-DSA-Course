// Problem Statement: Given an array, we have found the number of occurrences of each element in the
// array.
#include <bits/stdc++.h>
using namespace std;

vector<int> frequency(vector<int> a) {
    map<int, int> freq;
    vector<int> ans;
    for (auto i : a)
        freq[i]++;

    for (auto it : freq) {
        ans.push_back(it.first);
    }
    return ans;
}
