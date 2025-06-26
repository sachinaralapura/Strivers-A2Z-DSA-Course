#include <bits/stdc++.h>
using namespace std;
// Problem Statement: Given an integer N and an array of size N-1 containing N-1 numbers between 1 to N.
// Find the number(between 1 to N), that is not present in the given array.
int Missing_brute(vector<int> &arr) {
    for (int i = 1; i <= arr.size(); i++) {
        int flag = 0;
        for (int j = 0; j < arr.size(); j++) {
            if (arr[j] == i) {
                flag = 1;
                break;
            }
        }
        if (flag == 0) {
            return i;
        }
    }
    return -1;
}

int Missing_Opt(vector<int> &arr) {
    int N = arr.size();
    int sum = (N * (N + 1)) / 2;
    int sum2 = 0;
    for (int i = 0; i < N - 1; i++)
        sum2 += arr[i];
    int missingNum = sum - sum2;
    return missingNum;
}

int Missing_XOR(vector<int> &arr) {
    int N = arr.size();
    int xor1 = 0, xor2 = 0;
    for (int i = 0; i < N; i++) {
        xor1 = xor1 ^ (i + 1);
        xor2 = xor2 ^ arr[i];
    }
    xor1 = xor1 ^ N + 1;
    return (xor1 ^ xor2);
}
