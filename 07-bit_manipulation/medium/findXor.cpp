#include <iostream>
using namespace std;
// return xor from 1 to n
int findXor(int n) {
    int reminder = n % 4;
    if (reminder == 0)
        return n;
    if (reminder == 1)
        return 1;
    else if (reminder == 2)
        return n + 1;
    else if (reminder == 3)
        return 0;
    return -1;
}

int findXorRange(int l, int r) { return findXor(l - 1) ^ findXor(r); }

int main() {
    int xorr = findXorRange(4, 8);
    cout << xorr << endl;
    return 0;
}
