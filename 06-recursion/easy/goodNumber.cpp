long long goodNumber(int n) {
    if (n == 1) {
        return 4.0;
    }
    if (n % 2 == 0) {
        return (long long)5 * goodNumber(n - 1);
    } else {
        return (long long)4 * goodNumber(n - 1);
    }
}
