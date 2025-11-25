#include "heap.h"
#include <algorithm>
#include <iostream>
#include <set>
#include <vector>
using namespace std;

struct Tuple {
    int sum;
    int i;
    int j;
    Tuple(int s, int a, int b) : sum(s), i(a), j(b) {}
    bool operator<(const Tuple &other) const {
        return sum < other.sum;
    }
};

vector<int> maxCombination(vector<int> &a, vector<int> &b, int k) {
    // sort both arrays
    sort(a.begin(), a.end(), greater<int>());
    sort(b.begin(), b.end(), greater<int>());

    BinaryHeap<Tuple, less<Tuple>> maxHeap;
    vector<int> result;

    set<pair<int, int>> visited;
    maxHeap.insertNode(Tuple(a[0] + b[0], 0, 0));
    visited.insert({0, 0});

    while (k-- && !maxHeap.isEmpty()) {
        // current max sum
        Tuple current = maxHeap.removeRootNode();
        result.push_back(current.sum);

        if (current.i + 1 < a.size() && !visited.count({current.i + 1, current.j})) {
            maxHeap.insertNode(Tuple(a[current.i + 1] + b[current.j], current.i + 1, current.j));
            visited.insert({current.i + 1, current.j});
        }

        if (current.j + 1 < b.size() && !visited.count({current.i, current.j + 1})) {
            maxHeap.insertNode(Tuple(a[current.i] + b[current.j + 1], current.i, current.j + 1));
            visited.insert({current.i, current.j + 1});
        }
    }
    return result;
}

int main() {
    vector<int> nums1 = {3, 4, 5};
    vector<int> nums2 = {2, 6, 3};
    int k = 2;
    vector<int> result = maxCombination(nums1, nums2, k);
    cout << "Top " << k << " maximum combinations are: ";
    for (int sum : result) {
        cout << sum << " ";
    }
    cout << endl;
    return 0;
}
