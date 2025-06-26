#include <bits/stdc++.h>
#include <iostream>
#include <stack>
#include <vector>

using namespace std;

vector<int> NextGreater(vector<int> arr) {
    int n = arr.size();
    vector<int> ans;
    for (int i = 0; i < n; i++) {
        int j = i + 1;
        while (j % n != i) {
            if (arr[j % n] > arr[i]) {
                ans.push_back(arr[j % n]);
                break;
            } else
                j++;
        }
        if (j % n == i)
            ans.push_back(-1);
    }
    return ans;
}

vector<int> NextGreaterOpt(vector<int> arr) {
    int n = arr.size();
    vector<int> ans(n, -1);
    stack<int> st;
    for (int i = 2 * n - 1; i >= 0; i--) {
        while (!st.empty() && st.top() <= arr[i % n])
            st.pop();
        if (i < n)
            if (!st.empty())
                ans[i] = st.top();
        st.push(arr[i % n]);
    }
    return ans;
}

vector<int> NextSmallerOpt(vector<int> arr) {
    int n = arr.size();
    vector<int> ans(n, -1);
    stack<int> st;
    for (int i = 2 * n - 1; i >= 0; i--) {
        while (!st.empty() && st.top() >= arr[i % n])
            st.pop();
        if (i < n)
            if (!st.empty())
                ans[i] = st.top();
        st.push(arr[i % n]);
    }
    return ans;
}

int main() {
    vector<int> arr = {
        2, 3, 1, 6, 7, 9, 1, 2, 10, 2, 4, 3, 7, 6, 1, 10,
    };
    vector<int> ans = NextSmallerOpt(arr);
    for (auto it : ans) {
        cout << it << endl;
    }
}
