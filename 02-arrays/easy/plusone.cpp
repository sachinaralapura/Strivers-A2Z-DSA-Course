#include <bits/stdc++.h>
using namespace std;
vector<int> plusone(vector<int> &digits) {
    int n = digits.size();
    int i = n - 1;
    while (i >= 0) {
        if (digits[i] < 9) {
            digits[i]++;
            return digits;
        } else {
            digits[i--] = 0;
        }
    }
    digits.insert(digits.begin(), 1);
    return digits;
}
