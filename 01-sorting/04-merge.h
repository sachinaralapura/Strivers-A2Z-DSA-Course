#ifndef SORT_MERGE
#define SORT_MERGE

#include <vector>
using namespace std;
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

template <typename T> void merge_sort(vector<T> &arr, int low, int high) {
    if (low >= high)
        return;
    int mid = (low + high) / 2;
    merge_sort<T>(arr, low, mid);
    merge_sort<T>(arr, mid + 1, high);
    merge<T>(arr, low, mid, high);
}

#endif
