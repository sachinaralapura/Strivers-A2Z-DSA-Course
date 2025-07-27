#include "nextGreatSmall.h"
#include <bits/stdc++.h>
#include <stack>
#include <utility>
#include <vector>
using namespace std;

vector<int> NextGreaterBrute(vector<int> arr) {
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

vector<int> NextGreaterCircluar(vector<int> arr) {
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

vector<int> PreviousGreatorCircular(vector<int> arr) {
    int n = arr.size();
    vector<int> ans(n, -1);
    stack<int> st;
    for (int i = 0; i <= 2 * n - 1; i++) {
        while (!st.empty() && st.top() <= arr[i % n])
            st.pop();
        if (i >= n) {
            if (!st.empty())
                ans[i % n] = st.top();
        }
        st.push(arr[i % n]);
    }
    return ans;
}

vector<int> NextSmallerCircular(vector<int> arr) {
    int n = arr.size();
    vector<int> ans(n, -1);
    stack<int> st;
    stack<pair<int, int>> stk;
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

vector<int> PreviousSmallerCircular(vector<int> arr) {
    int n = arr.size();
    if (n == 0)
        return arr;
    vector<int> ans(n, -1);
    stack<int> st;
    for (int i = 0; i <= 2 * n - 1; i++) {
        while (!st.empty() && st.top() >= arr[i % n])
            st.pop();
        if (i >= n)
            if (!st.empty())
                ans[i % n] = st.top();
        st.push(arr[i % n]);
    }
    return ans;
}

vector<int> PreviousSmaller(vector<int> arr) {
    int n = arr.size();
    if (n == 0)
        return arr;
    vector<int> ans(n, -1);
    stack<pair<int, int>> stk;
    for (int i = 0; i < n; i++) {
        while (!stk.empty() && stk.top().second >= arr[i])
            stk.pop();
        if (!stk.empty())
            ans[i] = stk.top().first;
        stk.push({i, arr[i]});
    }
    return ans;
}

vector<int> NextSmaller(vector<int> arr) {
    int n = arr.size();
    if (n == 0)
        return arr;
    vector<int> ans(n, -1);
    stack<pair<int, int>> stk;
    for (int i = n - 1; i >= 0; i--) {
        while (!stk.empty() && stk.top().second >= arr[i])
            stk.pop();
        if (!stk.empty())
            ans[i] = stk.top().first;
        stk.push({i, arr[i]});
    }
    return ans;
}

// int main() {
// vector<int> arr = {10, 2, 3, 1, 6, 7, 9, 1, 2};
// vector<int> arr = {9, 1, 6, 7, 3, 4, 2, 9, 2, 1, 9, 7, 6, 1, 3, 2};
// vector<int> ans = NextSmaller(arr);
// for (int i = 0; i < ans.size(); i++) {
//     string buf = "";
//     if (ans[i] < 0)
//         buf = " ";
//     cout << buf << i << " ";
// }
// cout << endl;
//     for (auto it : ans)
//         cout << it << " ";
// }
