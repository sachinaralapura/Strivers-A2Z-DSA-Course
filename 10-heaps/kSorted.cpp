// Sort K sorted array

// Problem Statement: Given an array arr[] and a number k . The array is sorted in a way that
// every element is at max k distance away from it sorted position. It means if we completely
// sort the array, then the index of the element can go from i - k to i + k where i is index in
// the given array. Our task is to completely sort the array.

#include "heap.h"
#include <iostream>
#include <vector>

vector<int> KSortedArray(vector<int> &arr, int k) {
    vector<int> result;
    BinaryHeapMinHeap minHeap(arr.begin(), arr.begin() + k + 1);
    int index = 0;
    if (arr.size() <= k) {
        while (!minHeap.isEmpty()) {
            result.push_back(minHeap.removeRootNode());
        }
        return result;
    }
    for (int i = k + 1; i < arr.size(); i++) {
        result.push_back(minHeap.removeRootNode());
        minHeap.insertNode(arr[i]);
    }
    while (!minHeap.isEmpty()) {
        result.push_back(minHeap.removeRootNode());
    }
    return result;
}

struct kSortedInput {
    vector<int> arr;
    int k;
};

int main(int argc, char const *argv[]) {
    kSortedInput input0 = {{1, 4, 5, 2, 3, 6, 7, 8, 9, 10}, 2};
    kSortedInput input1 = {{6, 5, 3, 2, 8, 10, 9}, 3};
    vector<int> sorted = KSortedArray(input0.arr, input0.k);
    for (int num : sorted) {
        cout << num << " ";
    }
    cout << endl;
    return 0;
}
