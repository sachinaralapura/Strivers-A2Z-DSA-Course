
double Rpow(double x, int n) {
    if (n == 0) {
        return 1.0;
    }
    return x * Rpow(x, n - 1);
}
