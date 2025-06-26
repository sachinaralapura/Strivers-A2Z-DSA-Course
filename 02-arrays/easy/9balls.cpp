#include <bits/stdc++.h>
using namespace std;
int heavierBall(vector<int> arr) {
    int n = arr.size();
    if (n != 9) {
        return -1;
    }
    int start = 0;
    int end = 0;
    int i = 0;
    while (true) {
        int sum = arr[i] + arr[i + 1] + arr[i + 2];
        i += 3;
        int nextGroupSum = arr[i] + arr[i + 1] + arr[i + 2];
        if (sum > nextGroupSum) {
            start = 0;
            end = 3;
            break;
        } else if (nextGroupSum > sum) {
            start = 3;
            end = 6;
        } else {
            start = 6;
            end = 9;
        }
    }
    if (arr[start] > arr[start + 1]) {
        return arr[start];
    } else if (arr[start + 1] < arr[start]) {
        return arr[start + 1];
    } else {
        return arr[end - 1];
    }
    return -1;
}
