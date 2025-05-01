// https://takeuforward.org/arrays/find-the-highest-lowest-frequency-element/
#include <bits/stdc++.h>
using namespace std;

static bool compare(pair<int, int> &p1, pair<int, int> &p2) {
    if (p1.second == p2.second)
        return p1.first > p2.first;
    return p1.second > p2.second;
}

vector<int> TopKFreq(vector<int> arr, int k) {
    int n = arr.size();
    // <element , index>
    unordered_map<int, int> mpp;
    for (int i = 0; i < n; i++)
        mpp[arr[i]]++;

    vector<pair<int, int>> freq(mpp.begin(), mpp.end());

    // Sort the vector 'freq' on the basis of the
    // 'compare' function
    sort(freq.begin(), freq.end(), compare);

    vector<int> ans;
    for (int i = 0; i < k; i++)
        ans.push_back(freq[i].first);

    return ans;
}

// Function to find  k numbers with most occurrences
vector<int> topKFrequent(vector<int> &arr, int k) {

    // unordered_map 'mp' implemented as frequency hash
    // table
    unordered_map<int, int> mp;
    for (int val : arr)
        mp[val]++;

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

    for (pair<int, int> entry : mp) {
        pq.push({entry.second, entry.first});
        if (pq.size() > k)
            pq.pop();
    }

    // store the result
    vector<int> res(k);

    for (int i = k - 1; i >= 0; i--) {
        res[i] = pq.top().second;
        pq.pop();
    }

    return res;
}
