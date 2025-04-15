#include <bits/stdc++.h>
using namespace std;
template <typename T> T binarySearch_iter(vector<T> a, T target) {
    int n = a.size();
    int low = 0;
    int high = n - 1;
    while (low <= high) {
        int mid = (low + high) / 2;
        if (a[mid] == target)
            return mid;
        else if (a[mid] > target)
            high = mid - 1;
        else
            low = mid + 1;
    }
    return -1;
}

template <typename T> int __bs__(vector<T> a, int l, int h, T t) {
    if (l > h)
        return -1;
    int m = (l + h) / 2;

    if (a[m] == t)
        return m;
    else if (t > a[m])
        return __bs__(a, m + 1, h, t);

    return __bs__(a, l, m - 1, t);
}

template <typename T> T binarySearch_recursive(vector<T> a, int target) {
    return __bs__(a, 0, a.size() - 1, target);
}

// Binary Search in Rotated array ( No Duplicate)
template <typename T> T binarySearch_Rotated(vector<T> a, int target) {
    int n = a.size();
    int low = 0;
    int high = n - 1;
    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (a[mid] == target)
            return mid;
        // check if left side is sorted
        if (a[low] <= a[mid]) {
            if (a[low] <= target && target <= a[mid])
                high = mid - 1;
            else
                low = mid + 1;
        } else {
            if (a[high] >= target && a[mid] <= target)
                low = mid + 1;
            else
                high = mid - 1;
        }
    }
    return -1;
}

// Binary Search in Rotated array ( Duplicate allowed )
template <typename T> T binarySearch_Rotated2(vector<T> a, int target) {
    int n = a.size();
    int low = 0;
    int high = n - 1;
    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (a[mid] == target)
            return mid;
        // edge case if duplicated allowed
        if (a[low] == a[mid] == a[high]) {
            high--;
            low++;
            continue;
        }
        // check if left side is sorted
        if (a[low] <= a[mid]) {

            if (a[low] <= target && target <= a[mid])
                high = mid - 1;
            else
                low = mid + 1;
        } else {
            if (a[high] >= target && a[mid] <= target)
                low = mid + 1;
            else
                high = mid - 1;
        }
    }
    return -1;
}

// Binary Search in Rotated array ( with distinct ) find minimum
template <typename T> pair<T, int> binarySearch_Rotated_min(vector<T> a) {
    int n = a.size();
    int low = 0;
    int high = n - 1;
    int ans = INT_MAX;
    int minIndex = -1;
    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (a[low] <= a[high]) {
            if (a[low] < ans) {
                ans = min(ans, a[low]);
                minIndex = low;
            }
            break;
        }
        if (a[low] <= a[mid]) {
            if (a[low] < ans) {
                ans = a[low];
                minIndex = low;
            }
            low = mid + 1;
        } else {
            if (a[mid] < ans) {
                ans = a[mid];
                minIndex = mid;
            }
            high = mid - 1;
        }
    }
    return make_pair(ans, minIndex);
}

// Search Single Element in a sorted array
// Problem Statement: Given an array of N integers.
// Every number in the array except one appears twice.Find the single number in the array.
int singleNonDuplicate(vector<int> a) {
    int n = a.size();
    int low = 0;
    int high = n - 1;

    // edge cases
    if (n == 1)
        return a[0];
    if (a[0] != a[1])
        return a[0];
    if (a[n - 1] != a[n - 2])
        return a[n - 1];

    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (a[mid] != a[mid + 1] && a[mid] != a[mid - 1]) {
            return a[mid];
        }

        if ((mid % 2 == 0 && a[mid] == a[mid + 1]) || (mid % 2 == 1 && a[mid] == a[mid - 1])) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }
    return -1;
}

// Find the peak Element
int FindPeak(vector<int> a) {
    int n = a.size();
    int low = 1;
    int high = n - 2;

    // Edge Cases
    if (n == 1)
        return a[0];
    if (a[0] > a[1])
        return a[0];
    if (a[n - 1] > a[n - 2])
        return a[n - 1];
    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (a[mid - 1] < a[mid] && a[mid] > a[mid + 1])
            return mid;
        else if (a[mid] > a[mid - 1])
            low = mid + 1;
        else if (a[mid] > a[mid + 1])
            high = mid - 1;
        else
            high = mid - 1;
    }
    return -1;
}