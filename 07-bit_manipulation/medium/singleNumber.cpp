#include <bits/stdc++.h>
using namespace std;
int singleNumber(vector<int> &nums) {
    int xorr = 0;
    for (auto it : nums) {
        xorr ^= it;
    }
    return xorr;
}
