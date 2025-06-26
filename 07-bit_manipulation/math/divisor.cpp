#include <bits/stdc++.h>
#include <cmath>
#include <vector>
using namespace std;

vector<int> divisors(int n) {
    vector<int> divisor;
    for (int i = 1; i * i <= n; i++) {
        if (n % i == 0) {
            divisor.push_back(i);
            if (n / i != i) {
                divisor.push_back(n / i);
            }
        }
    }
    return divisor;
}
