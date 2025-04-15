// Finding Sqrt of a number using Binary Search
// Problem Statement : You are given a positive integer n.Your task is to find and return its square
// root.If ‘n’ is not a perfect square, then return the floor value of 'sqrt(n)'.
#include <bits/stdc++.h>
using namespace std;
int sqrt_brute(int n) {
    int ans = 0;
    for (long long i = 1; i < n; i++) {
        long long val = i * i;
        if (val <= n)
            ans = i;
        else
            break;
    }
    return ans;
}

int sqrt_bs(int n) {
    int low = 1;
    int high = n;
    int ans = 0;
    while (low <= high) {
        long long mid = low + (high - low) / 2;
        long long val = mid * mid;
        if (val <= (long long)n)
            low = mid + 1;
        else
            high = mid - 1;
    }
    return high;
}

int func(int mid, int n, int m) {
    long long ans = 1;
    for (int i = 1; i <= n; i++) {
        ans = ans * mid;
        if (ans > m)
            return 2;
    }
    if (ans == m)
        return 1;
    return 0;
}

int nthRoot(int n, int m) {
    int low = 1;
    int high = m;

    while (low <= high) {
        int mid = low + (high - low) / 2;
        int midN = func(mid, n, m);

        if (midN == 1)
            return mid;
        else if (midN == 2)
            high = mid - 1;
        else
            low = mid + 1;
    }

    return -1;
}