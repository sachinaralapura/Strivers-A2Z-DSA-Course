// Problem Statement: Given two sorted arrays, arr1, and arr2 of size n and m. Find the union of two
// sorted arrays.

// The union of two arrays can be defined as the common and distinct elements in the two arrays.

// NOTE: Elements in the union should be in ascending order.
#include <bits/stdc++.h>
using namespace std;
template <typename T> vector<T> Union_brute(vector<T> &arr1, vector<T> &arr2) {
    vector<T> temp = arr1;
    for (auto i : arr2) {
        if (!Linear_search(temp, i)) {
            temp.push_back(i);
        }
    }
    return temp;
}
template <typename T> vector<T> Union_map(vector<T> &arr1, vector<T> &arr2) {
    map<T, int> freq;
    vector<T> Union;
    for (int i = 0; i < arr1.size(); i++)
        freq[arr1[i]]++;
    for (int i = 0; i < arr2.size(); i++)
        freq[arr2[i]]++;
    for (auto i : freq)
        Union.push_back(i.first);
    return Union;
}
template <typename T> vector<int> Union_set(vector<T> &arr1, vector<T> &arr2) {
    set<T> s;
    vector<T> Union;
    for (int i = 0; i < arr1.size(); i++)
        s.insert(arr1[i]);
    for (int i = 0; i < arr2.size(); i++)
        s.insert(arr2[i]);
    for (auto &i : s)
        Union.push_back(i);
    return Union;
}
