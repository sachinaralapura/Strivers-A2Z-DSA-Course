#include <bits/stdc++.h>
#include <cmath>
using namespace std;

bool IsEven(int n) {
    if (n & (n - 1)) {
        cout << n << " is not power of two" << endl;
    } else {
        cout << n << " is power of two" << endl;
    }
    return !(n & (n - 1));
}

bool IsPowTwo(int n) {
    if (n & (n - 1)) {
        cout << n << " is not power of two" << endl;
    } else {
        cout << n << " is power of two" << endl;
    }
    return !(n & (n - 1));
}

// check if kth bit is set
void IsbitSet(int n, int k) {
    if (n & (1 << (k - 1))) {
        cout << k << "th bit is set" << endl;
    } else {
        cout << k << "th bit is not set" << endl;
    }
}

// count the number of set bits in a number
// property used subtracting 1 from a binary number flips all the bits from the rightmost set bit
// (1) to the end of the number (0s).
int NumOfSetBit(int n) {
    int count = 0;
    while (n != 0) {
        n &= (n - 1);
        count++;
    }
    return count;
}

// Divide the number by 2 till it's zero
int NumOfSetBitTwo(int n) {
    int count = 0;
    while (n != 0) {
        if (n % 2 == 1)
            count++;
        n = n / 2;
    }
    return count;
}

// return the position of the first set bit
// n & (~n + 1)
// property used two's complement
int getFirstSetBit(int n) {
    if (n == 0)
        return 0;
    // n & ( two's complement of n)
    // or ( n & (-n) ) ( -n and two's complement are same)
    int res = n & (~n + 1);
    // log of res will get the position
    int pos = log2(res) + 1;
    return pos;
}

// return the position of first set bit
// (n & ( n-1 )) ^ num
int getFirstSetBitTwo(int n) {
    if (n == 0)
        return 0;
    int res = (n & (n - 1)) ^ n;
    int pos = log2(res) + 1;
    return pos;
}

// set the rightmost unset bit in the binary representation of n.
int setRightmostUnsetBit(int n) {
    if (n == 0)
        return 1;
    // if all bits of 'n' are set
    if (((n + 1) & n) == 0)
        return n;
    int pos = getFirstSetBit(~n) - 1;

    // set the pos bit to 1;
    return n | (1 << pos);
}

// Check if all the bits is one
bool AllBitOne(int n) {
    return !((n + 1) & n);
}

void swapNumber(int *, int *);
