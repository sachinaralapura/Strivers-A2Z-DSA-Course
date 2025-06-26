#include <bits/stdc++.h>
using namespace std;
// Problem Statement: Given a non-empty array of integers arr,
// every element appears twice except for one. Find that single one
int getSingleElement(vector<int> &arr) {
    for (int i = 0; i < arr.size(); i++) {
        int num = arr[i]; // selected element
        int cnt = 0;
        // find the occurrence using linear search:
        for (int j = 0; j < arr.size(); j++) {
            if (arr[j] == num)
                cnt++;
        }
        // if the occurrence is 1 return ans:
        if (cnt == 1)
            return num;
    }
    return -1;
}
int getSingleElement_hash(vector<int> &arr) {
    int N = arr.size();
    // Find the maximum element:
    int maxi = arr[0];
    for (int i = 0; i < N; i++) {
        maxi = max(maxi, arr[i]);
    }
    vector<int> hash(maxi + 1, 0);
    for (int i = 0; i < N; i++) {
        hash[arr[i]]++;
    }
    for (int i = 0; i < N; i++) {
        if (hash[arr[i]] == 1)
            return arr[i];
    }

    // This line will never execute
    // if the array contains a single element.
    return -1;
}

int getSingleElement_hashMap(vector<int> &arr) {
    // size of the array:
    int n = arr.size();

    // Declare the hashmap.
    // And hash the given array:
    unordered_map<int, int> mpp;
    for (int i = 0; i < n; i++) {
        mpp[arr[i]]++;
    }
    // Find the single element and return the answer:
    for (auto it : mpp) {
        if (it.second == 1)
            return it.first;
    }
    return -1;
}

int getSingleElement_XOR(vector<int> &arr) {
    // size of the array:
    int n = arr.size();
    int xorr = 0;
    for (int i = 0; i < n; i++) {
        xorr = xorr ^ arr[i];
    }
    return xorr;
}
