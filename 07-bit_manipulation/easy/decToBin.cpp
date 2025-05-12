#include <bits/stdc++.h>
using namespace std;
#include <iostream>
int main() {
    int dec = 13;

    string binary = "";
    while (dec != 0) {
        if (dec % 2 == 1)
            binary += '1';
        else
            binary += '0';
        dec = dec / 2;
    }

    reverse(binary.begin(), binary.end());
    cout << binary << endl;
}
