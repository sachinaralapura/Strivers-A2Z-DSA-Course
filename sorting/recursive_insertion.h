#include <vector>
using namespace std;

template <typename T>
void recursive_insertion_sort(vector<T> &arr, int i, int n)
{
    if (i == n)
        return;

    int j = i;
    while (j > 0 && arr[j - 1] > arr[j])
    {
        T temp = arr[j - 1];
        arr[j - 1] = arr[j];
        arr[j] = temp;
        j--;
    }

    recursive_insertion_sort(arr, i + 1, n);
}