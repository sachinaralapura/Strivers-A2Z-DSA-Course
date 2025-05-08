#include <bits/stdc++.h>
using namespace std;

vector<bool> bulbs(int round) {
    vector<bool> bulb(100, false);
    for (int i = 1; i <= round; i++) {
        for (int j = i - 1; i < 100; j += i) {
            bulb[j] = !bulb[j];
        }
    }
    return bulb;
}
