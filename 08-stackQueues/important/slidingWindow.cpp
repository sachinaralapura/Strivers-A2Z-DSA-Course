#include "slidingWindow.h"
#include <algorithm>
#include <climits>
#include <deque>
#include <iostream>

using namespace std;

void GetMax(const vector<int> arr, int l, int r, vector<int> &ans) {
    int i, maxi = INT_MIN;
    for (i = l; i <= r; i++)
        maxi = max(arr[i], maxi);
    ans.push_back(maxi);
}

vector<int> SlidingWindow(vector<int> arr, int k) {
    int n = arr.size();
    if (k > n) {
        throw MyError("window size is bigger than the array size");
    }
    int l = 0;
    int r = l + k - 1;
    vector<int> ans;
    while (r < n) {
        GetMax(arr, l, r, ans);
        l++;
        r++;
    }
    return ans;
}

vector<int> SlidingWindowDequeue(vector<int> arr, int k) {
    int n = arr.size();
    if (k > n)
        throw MyError("window size is bigger than the array size");
    deque<int> dq;
    vector<int> ans;
    for (int i = 0; i < n; i++) {
        int currEle = arr[i];
        if (!dq.empty() && dq.front() == i - k)
            dq.pop_front();
        while (!dq.empty() && arr[dq.back()] < currEle)
            dq.pop_back();

        dq.push_back(i);
        if (i >= k - 1)
            ans.push_back(arr[dq.front()]);
    }
    return ans;
}

int main() {
    vector<int> arr{4, 0, -1, 3, 5, 3, 6, 8};
    int k = 3;
    try {
        vector<int> ans = SlidingWindowDequeue(arr, k);
        for (auto it : ans)
            cout << it << endl;
    } catch (const MyError &e) {
        cout << e.what() << endl;
    }
}
