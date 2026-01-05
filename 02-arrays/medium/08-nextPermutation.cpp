#include <bits/stdc++.h>
#include <iostream>
using namespace std;
// next_permutation : find next lexicographically greater permutation
// Problem Statement : Given an array Arr[] of integers, rearrange the
// numbers of the given array into the
//  lexicographically next greater permutation of numbers.If such an
// arrangement is not possible,
// it must rearrange to the lowest possible order(i.e., sorted in ascending
// order).
// Input format :
//  Arr[] = {1, 3, 2}
// Output:
//  Arr[] = {2, 1, 3}

// Explanation : All permutations of{1, 2, 3} are{{1, 2, 3}, {1, 3, 2}, {2,
// 13}, {2, 3, 1}, {3, 1, 2}, {3, 2, 1}}.So,
// the next permutation just after{1, 3, 2} is{2, 1, 3}.
bool Next_permutation(vector<int> &arr);
template <typename T> void printVector(vector<T> &arr) {
    cout << "{ ";
    for (int i = 0; i < arr.size(); i++)
        cout << arr[i] << ",";
    cout << " }" << endl;
}

template <typename T> void AllPermutations(vector<T> &arr) {
    do {
        printVector(arr);
    } while (Next_permutation(arr));
}

bool Next_permutation(vector<int> &arr) {
    int n = arr.size();
    int breakIndex = -1;
    // find the break point
    for (int i = n - 2; i >= 0; i--) {
        if (arr[i] < arr[i + 1]) {
            breakIndex = i;
            break;
        }
    }
    if (breakIndex == -1) {
        reverse(arr.begin(), arr.end());
        return false;
    }

    // swap breakIndex element with least great element to the right of the breakIndex
    for (int i = n - 1; i > breakIndex; i--) {
        if (arr[i] > arr[breakIndex]) {
            swap(arr[i], arr[breakIndex]);
            break;
        }
    }
    reverse(arr.begin() + breakIndex + 1, arr.end());
    return true;
}
