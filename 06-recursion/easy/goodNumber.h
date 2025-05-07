inline long long R(int n) {
    if (n == 1) {
        return 4.0;
    }
    if (n % 2 == 0) {
        return (long long)5 * R(n - 1);
    } else {
        return (long long)4 * R(n - 1);
    }
}
