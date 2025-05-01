// https://takeuforward.org/data-structure/3-sum-find-triplets-that-add-up-to-a-zero/
#include <bits/stdc++.h>
using namespace std;

vector<vector<int>> threeSum_Opt(vector<int> &arr) {
    int n = arr.size();
    sort(arr.begin(), arr.end());
    vector<vector<int>> ans;

    for (int i = 0; i < n; i++) {
        if (i != 0 && arr[i - 1] == arr[i])
            continue;
        int j = i + 1;
        int k = n - 1;
        while (j < k) {
            int sum = arr[i] + arr[j] + arr[k];
            if (sum > 0)
                k--;
            else if (sum < 0)
                j++;
            else {
                vector<int> temp = {arr[i], arr[j], arr[k]};
                ans.push_back(temp);
                j++;
                k--;
                while (j < k && arr[j - 1] == arr[j])
                    j++;
                while (j < k && arr[k + 1] == arr[k])
                    k--;
            }
        }
    }
    return ans;
}