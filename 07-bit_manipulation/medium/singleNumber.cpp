#include <bits/stdc++.h>
using namespace std;
int singleNumber(vector<int> &nums) {
    int xorr = 0;
    for (auto it : nums) {
        xorr ^= it;
    }
    return xorr;
}

int main() {
    vector<int> arr = {2, 2, 1, 3, 3, 1, 4};
    cout << singleNumber(arr);
    return 0;
}
