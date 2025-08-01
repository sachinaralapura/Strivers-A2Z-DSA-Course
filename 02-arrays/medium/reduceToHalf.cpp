// You are given an integer array arr. You can choose a set of integers and
// remove all the occurrences of these integers in the array.

// Return the minimum size of the set so that at least half of the integers of
// the array are removed.
#include <algorithm>
#include <bits/stdc++.h>
#include <functional>
#include <ranges>
#include <unordered_map>
#include <utility>
#include <vector>
using namespace std;

inline int reduceHalf(vector<int> &arr) {
    const int n = arr.size();
    int sum = 0;
    unordered_map<int, int> count;
    vector<pair<int, int>> numAndFreqs;
    vector<int> ans;

    for (const int a : arr) {
        ++count[a];
    }

    for (const auto &[a, freq] : count) {
        numAndFreqs.emplace_back(a, freq);
    }
    ranges::sort(numAndFreqs, greater{}, [](const pair<int, int> &numAndFreq) { return numAndFreq.second; });
    for (int i = 0; i < numAndFreqs.size(); ++i) {
        sum += numAndFreqs[i].second;
        if (sum >= n / 2)
            return i + 1;
    }
    return 0;
}
