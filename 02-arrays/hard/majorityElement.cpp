#include <bits/stdc++.h>
using namespace std;
// Find the elements that appears more than N / 3 times in the array
// Problem Statement : Given an array of N integers.Find the elements that appear more than N / 3 times in the array.
// If no such element exists, return an empty vector.
// Extended Boyer Moore’s Voting Algorithm
vector<int> n3majorityElement_morre(vector<int> &arr) {
    int n = arr.size();
    int el1 = INT_MIN;
    int el2 = INT_MIN;
    int cnt1 = 0;
    int cnt2 = 0;
    for (int i = 0; i < n; i++) {
        if (cnt1 == 0 && el2 != arr[i]) {
            cnt1 = 1;
            el1 = arr[i];
        } else if (cnt2 == 0 && el1 != arr[i]) {
            cnt2 = 1;
            el2 = arr[i];
        } else if (arr[i] == el1)
            cnt1++;
        else if (arr[i] == el2)
            cnt2++;
        else {
            cnt1--;
            cnt2--;
        }
    }
    vector<int> ls; // list of answers
    cnt1 = 0, cnt2 = 0;
    for (int i = 0; i < n; i++) {
        if (arr[i] == el1)
            cnt1++;
        if (arr[i] == el2)
            cnt2++;
    }
    int mini = int(n / 3) + 1;
    if (cnt1 >= mini)
        ls.push_back(el1);
    if (cnt2 >= mini)
        ls.push_back(el2);

    return ls;
}
