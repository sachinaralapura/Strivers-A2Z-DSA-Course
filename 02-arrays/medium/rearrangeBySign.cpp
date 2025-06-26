#include <bits/stdc++.h>
using namespace std;
// Rearrange Array Elements by Sign
// Problem Statement :
// There’s an array ‘A’ of size ‘N’ with an equal number of positive and
// negative elements. Without altering the relative order of positive and negative elements,
// you must return an array of alternately positive and negative values.
inline vector<int> RearrangebySign(vector<int> &arr) {
    vector<int> ans;
    int n = arr.size();
    int posIndex = 0;
    int negIndex = 1;
    for (int i = 0; i < n; i++) {
        if (arr[i] < 0) {
            ans[negIndex] = arr[i];
            negIndex += 2;
        } else {
            ans[posIndex] = arr[i];
            posIndex += 2;
        }
    }
    return ans;
}
