#include <bits/stdc++.h>
using namespace std;
template <typename T> bool Linear_search(vector<T> &arr, int num) {
    int i;
    int n = arr.size();
    for (i = 0; i < n; i++) {
        if (arr[i] == num)
            return true;
    }
    return false;
}
