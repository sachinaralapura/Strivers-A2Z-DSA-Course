// Problem Statement: Given an array that contains only 1 and 0 return the count of maximum
// consecutive ones in the array..
#include <bits/stdc++.h>
using namespace std;
int findMaxConsecutiveOnes(vector<int> &arr) {
    int maxi = 0;
    int cnt = 0;
    for (int i = 0; i < arr.size(); i++) {
        if (arr[i] == 1)
            cnt++;
        else
            cnt = 0;
        maxi = max(maxi, cnt);
    }
    return maxi;
}
