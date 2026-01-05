// Problem Statement: Find the intersection of two sorted arrays. OR in other words, Given 2 sorted
// arrays, find all the elements which occur in both the arrays.
#include <bits/stdc++.h>
using namespace std;

vector<int> intersection(vector<int> &num1, vector<int> &num2) {
    // frequency array of num1;
    unordered_map<int, int> freq;
    vector<int> ans;
    for (auto it : num1) {
        freq[it]++;
    }

    for (int i = 0; i < num2.size(); i++) {
        int ele = num2[i];
        if (freq.find(ele) != freq.end() && freq[ele] != 0) {
            ans.push_back(ele);
            freq[ele]--;
        }
    }
    return ans;
}

vector<int> intersection_opt(vector<int> &num1, vector<int> &num2) {
    vector<int> ans;
    sort(num1.begin(), num1.end());
    sort(num1.begin(), num2.end());
    int i = 0, j = 0;
    while (i < num1.size() && j < num2.size()) {
        if (num1[i] == num2[j]) {
            ans.push_back(num1[i]);
            i++;
            j++;
        } else if (num1[i] < num2[j]) {
            i++;
        } else {
            j++;
        }
    }
    return ans;
}
