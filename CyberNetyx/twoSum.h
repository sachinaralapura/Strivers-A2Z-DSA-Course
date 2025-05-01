// https://takeuforward.org/data-structure/two-sum-check-if-a-pair-with-given-sum-exists-in-array/
#include <bits/stdc++.h>
using namespace std;

bool twosum_hash(vector<int> a, int target) {
    int n = a.size();
    // stored elements , index
    unordered_map<int, int> mpp;
    for (int i = 0; i < n; i++) {
        int current = a[i];
        int needed = target - current;
        if (mpp.find(needed) != mpp.end())
            return true;

        mpp[current] = i;
    }
    return false;
}

bool twosum_pointer(vector<int> a, int target) {
    int n = a.size();
    int left = 0;
    int right = n - 1;

    sort(a.begin(), a.end());

    while (left < right) {
        int sum = a[left] + a[right];
        if (sum == target)
            return true;

        if (sum > target)
            right--;
        else
            left++;
    }
    return false;
}