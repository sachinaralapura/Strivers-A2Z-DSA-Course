#include "largestInHistogram.h"
#include "nextGreatSmall.h"
#include <bits/stdc++.h>
#include <stack>
#include <vector>
using namespace std;

int LargestInHistogram(vector<int> arr) {
    vector<int> previousSmaller = PreviousSmaller(arr);
    vector<int> nextSmaller = NextSmaller(arr);
    int n = arr.size();
    int maxArea = 0;
    for (int i = 0; i < n; i++) {
        int left = previousSmaller[i] == -1 ? 0 : previousSmaller[i] + 1;
        int right = nextSmaller[i] == -1 ? (n - 1) : nextSmaller[i] - 1;
        maxArea = max(maxArea, right - left + 1 * arr[i]);
    }
    return maxArea;
}

int LargestInHistogramOpt(vector<int> heights) {
    int n = heights.size();
    vector<int> ans(n, -1);
    stack<int> stk;
    int maxA = 0;
    for (int i = 0; i <= n; i++) {
        while (!stk.empty() && (i == n || heights[stk.top()] >= heights[i])) {
            int height = heights[stk.top()];
            stk.pop();
            int width;
            if (stk.empty())
                width = i;
            else
                width = i - stk.top() - 1;
            maxA = max(maxA, width * height);
        }
        stk.push(i);
    }
    return maxA;
}

// int main() {
//     vector<int> arr = {2, 1, 5, 6, 2, 3, 1};
//     int res = LargestInHistogramOpt(arr);
//     cout << "largest rectangle : " << res << endl;
// }
