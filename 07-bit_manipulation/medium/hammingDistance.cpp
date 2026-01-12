// using built-in function
int NumOfSetBit(int n) {
    return __builtin_popcount(n);
}

int NumberOfSetBitOne(int n) {
    int count = 0;
    while (n != 0) {
        n = n & (n - 1);
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
// number of bit to flip  to get a number from anther number
int Distance(int start, int goal) {
    int res = start ^ goal;
    return NumOfSetBit(res);
}
