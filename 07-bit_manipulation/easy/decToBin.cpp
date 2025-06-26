#include <bits/stdc++.h>
using namespace std;
string decToBin(int dec) {
    string binary = "";
    while (dec != 0) {
        if (dec % 2 == 1)
            binary += '1';
        else
            binary += '0';
        dec = dec / 2;
    }

    reverse(binary.begin(), binary.end());
    return binary;
}
