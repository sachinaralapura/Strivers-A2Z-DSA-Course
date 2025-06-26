#include <vector>
using namespace std;

template <typename T> int merge(vector<T> &arr, int low, int mid, int high) {
    vector<T> temp;
    int left = low;
    int right = mid + 1;

    int count = 0;
    while (left <= mid && right <= high) {
        if (arr[left] <= arr[right])
            temp.push_back(arr[left++]);

        else {
            temp.push_back(arr[right++]);
            count += (mid - left + 1); // increment count (mid - low + 1) times
        }
    }

    while (left <= mid)
        temp.push_back(arr[left++]);
    while (right <= high)
        temp.push_back(arr[right++]);

    for (int i = low; i <= high; i++)
        arr[i] = temp[i - low];

    return count;
}

template <typename T> int merge_sort(vector<T> &arr, int low, int high) {
    int count = 0;
    if (low >= high)
        return count;
    int mid = (low + high) / 2;
    count += merge_sort<T>(arr, low, mid);
    count += merge_sort<T>(arr, mid + 1, high);
    count += merge<T>(arr, low, mid, high);
    return count;
}

// -------------------------------------------------------

int numberOfInversions_brute(vector<int> arr) {
    int n = arr.size();
    int count = 0;
    for (int i = 0; i < n; i++)
        for (int j = i + 1; j < n; j++)
            if (arr[i] > arr[j])
                count++;
    return count;
}

int numberOfInversions_opt(vector<int> &arr) { return merge_sort<int>(arr, 0, arr.size() - 1); }

// Count inversions in an array
// Problem Statement: Given an array of N integers, count the inversion of the array (using merge-sort).
// What is an inversion of an array? Definition: for all i & j < size of array, if i < j then you have to find pair
// (A[i],A[j]) such that A[j] < A[i].
