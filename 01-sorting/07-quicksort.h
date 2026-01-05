#ifndef SORT_QUICK
#define SORT_QUICK

#include <vector>
using namespace std;

template <typename T> int partition(vector<T> &arr, int low, int high);

template <typename T> void Quick_sort(vector<T> &arr, int low, int high) {
    if (low < high) {
        int pivot = partition(arr, low, high);
        Quick_sort(arr, low, pivot - 1);
        Quick_sort(arr, pivot + 1, high);
    }
}

template <typename T> int partition(vector<T> &arr, int low, int high) {
    T pivot = arr[low];
    int i = low;
    int j = high;
    while (i < j) {
        while (arr[i] <= pivot && i <= high - 1)
            i++;
        while (arr[j] >= pivot && j >= low + 1)
            j--;
        if (i < j)
            swap(arr[i], arr[j]);
    }
    swap(arr[low], arr[j]);
    return j;
}

#endif
