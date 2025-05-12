// Given an unsorted array that contains even number of occurrences for all numbers except two numbers. The task is to
// find the two numbers which have odd occurrences
#include <bits/stdc++.h>
using namespace std;
vector<int> SingleNumber(vector<int> arr) {
    int n = arr.size();
    int xorVal = 0;
    for (int i : arr)
        xorVal ^= i;

    // Get its last set bit
    int mask = xorVal & (-xorVal);
    vector<int> ans(2, 0);
    for (int i = 0; i < n; i++) {
        int num = arr[i];
        if (num & mask)
            ans[0] ^= num;
        else
            ans[1] ^= num;
    }
    return ans;
}

int main() {
    vector<int> arr = {1, 2, 1, 3, 3, 2, 10, 12};
    auto ans = SingleNumber(arr);
    cout << ans[0] << " " << ans[1];
}
