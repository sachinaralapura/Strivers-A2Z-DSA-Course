#include <bits/stdc++.h>
using namespace std;
template <typename T> int countPairs(vector<T> &arr, int low, int mid, int high) {
    int count = 0;
    int right = mid + 1;
    for (int i = low; i <= mid; i++) {
        while (right <= high && arr[i] > 2 * arr[right]) {
            right++;
        }
        count += (right - (mid + 1));
    }
    return count;
}

template <typename T> void merge(vector<T> &arr, int low, int mid, int high) {
    vector<T> temp;
    int left = low;
    int right = mid + 1;

    while (left <= mid && right <= high) {
        if (arr[left] <= arr[right])
            temp.push_back(arr[left++]);

        else
            temp.push_back(arr[right++]);
    }

    while (left <= mid)
        temp.push_back(arr[left++]);
    while (right <= high)
        temp.push_back(arr[right++]);

    for (int i = low; i <= high; i++)
        arr[i] = temp[i - low];
}

template <typename T> int merge_sort(vector<T> &arr, int low, int high) {
    int count = 0;
    if (low >= high)
        return count;
    int mid = (low + high) / 2;
    count += merge_sort<T>(arr, low, mid);
    count += merge_sort<T>(arr, mid + 1, high);
    // a function to count Reverse Pair
    count += countPairs<T>(arr, low, mid, high);
    merge<T>(arr, low, mid, high);
    return count;
}

// -------------------------------------------------------

int CountReversePairs_Opt(vector<int> &a) { return merge_sort(a, 0, a.size() - 1); }

int CountReversePairs_brute(vector<int> &arr) {
    int n = arr.size();
    int cnt = 0;
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (arr[i] > 2 * arr[j]) {
                cnt += 1;
            }
        }
    }
    return cnt;
}
