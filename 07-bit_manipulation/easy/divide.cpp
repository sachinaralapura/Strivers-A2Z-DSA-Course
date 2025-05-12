#include <climits>
#include <iostream>
using namespace std;

int divide(int dividend, int divisor) {
    if (dividend == divisor)
        return 1;
    bool positive = true;
    positive = ((dividend < 0) ^ (divisor < 0)) ? false : true;
    int n = abs(dividend);
    int d = abs(divisor);
    int quotient = 0;
    while (n >= d) {
        int count = 0;
        while (n >= (d << (count + 1))) {
            count++;
        }
        quotient += (1 << count);
        n = n - (d << (count));
    }
    if (quotient == (1 << 31) && positive) {
        return INT_MAX;
    }
    if (quotient == (1 << 31) && !positive)
        return INT_MIN;
    return positive ? quotient : -quotient;
}

int main() {
    int quotient = divide(22, -3);
    cout << quotient << endl;
    return 0;
}
