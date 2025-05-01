// https://takeuforward.org/data-structure/merge-overlapping-sub-intervals/
#include <bits/stdc++.h>
using namespace std;

vector<vector<int>> mergeOverlapping(vector<vector<int>> arr) {
    vector<vector<int>> ans;
    sort(arr.begin(), arr.end());
    for (auto current : arr) {
        if (ans.empty() || ans.back()[1] < current[0])
            ans.push_back(current);
        else
            ans.back()[1] = max(ans.back()[1], current[1]);
    }
    return ans;
}