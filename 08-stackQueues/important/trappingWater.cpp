#include <bits/stdc++.h>
#include <iostream>

#include <vector>
using namespace std;
int TrappingWater_suboptimal(vector<int>);
int TrappingWater_opt(vector<int>);
int main() {
    vector<int> a = {0, 1, 0, 2, 1, 0, 1, 3, 2, 1, 2, 1};
    int ans = TrappingWater_opt(a);
    cout << ans << endl;
    return 0;
}

int TrappingWater_suboptimal(vector<int> a) {
    int n = a.size();
    vector<int> prefixMax(n, 0);
    vector<int> suffixMax(n, 0);
    prefixMax[0] = a[0];
    suffixMax[n - 1] = a[n - 1];
    int pmax = 0;
    int smax = 0;
    for (int i = 1, j = n - 2; i < n && j >= 0; i++, j--) {
        prefixMax[i] = max(prefixMax[i - 1], a[i]);
        suffixMax[j] = max(suffixMax[j + 1], a[j]);
    }
    int ans = 0;
    for (int i = 0; i < n; i++)
        ans += min(prefixMax[i], suffixMax[i]) - a[i];
    return ans;
}

int TrappingWater_opt(vector<int> a) {
    int n = a.size();
    int left = 0;
    int right = n - 1;
    int res = 0;
    int maxLeft = 0, maxRight = 0;
    while (left <= right) {
        if (a[left] <= a[right]) {
            if (a[left] >= maxLeft)
                maxLeft = a[left];
            else
                res += maxLeft - a[left];
            left++;
        } else {
            if (a[right] >= maxRight)
                maxRight = a[right];
            else
                res += maxRight - a[right];
            right--;
        }
    }
    return res;
}
