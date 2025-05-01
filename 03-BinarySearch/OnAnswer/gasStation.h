#include <bits/stdc++.h>
using namespace std;

long double minimizedMaxDistance(vector<int> a, int k) {
    int n = a.size();
    vector<int> gapArray(n - 1, 0);
    for (int i = 0; i < k; i++) {
        long double maxSectionDistance = 0;
        int maximumIndex = -1;
        for (int i = 0; i < n - 1; i++) {
            long double initialSectionDistance = a[i + 1] - a[i];
            long double sectionDistance = initialSectionDistance / (long double)(gapArray[i] + 1);
            if (maxSectionDistance < sectionDistance) {
                maxSectionDistance = sectionDistance;
                maximumIndex = i;
            }
        }
        gapArray[maximumIndex]++;
    }

    long double maxAns = -1;
    for (int i = 0; i < n - 1; i++) {
        long double secLength = (a[i + 1] - a[i]) / (long double)(gapArray[i] + 1);
        maxAns = max(maxAns, secLength);
    }
    return maxAns;
}

long double minimizedMaxDistanceHeap(vector<int> a, int k) {
    int n = a.size();
    vector<int> gapArray(n - 1, 0);
    priority_queue<pair<long double, int>> heap;
    for (int i = 0; i < n - 1; i++) {
        int diff = a[i + 1] - a[i];
        heap.push({diff, i});
    }
    for (int i = 0; i < n - 1; i++) {
        auto top = heap.top();
        heap.pop();
        int sectionIndex = top.second;
        gapArray[sectionIndex]++;
        long double initialSectionLength = a[sectionIndex + 1] - a[sectionIndex];
        long double newSectionLenght =
            initialSectionLength / (long double)(gapArray[sectionIndex] + 1);
        heap.push({newSectionLenght, sectionIndex});
    }
    return heap.top().first;
}