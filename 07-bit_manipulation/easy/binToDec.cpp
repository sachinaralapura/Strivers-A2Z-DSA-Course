#include <bits/stdc++.h>
#include <cmath>
using namespace std;
#include <iostream>
int main() {
    string bin = "1101";
    int decimal = 0;
    int p2 = 1;
    int n = bin.size();
    for (int i = n - 1; i >= 0; i--) {
        if (bin[i] == '1')
            decimal += p2;
        p2 = p2 * 2;
    }
    cout << decimal << endl;
}
