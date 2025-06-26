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
