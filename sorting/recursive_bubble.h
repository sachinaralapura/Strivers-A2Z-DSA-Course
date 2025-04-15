#include <vector>
using namespace std;
template <typename T>
void bubble_sort_recursive(vector<T> &arr, int n)
{
    if (n == 1)
        return;

    bool didswap = false;
    for (int i = 0; i < n - 1; i++)
    {
        if (arr[i] > arr[i + 1])
        {
            T t = arr[i];
            arr[i] = arr[i + 1];
            arr[i + 1] = t;
            didswap = true;
        }
    }
    if (didswap)
        return;
    bubble_sort_recursive(arr, n - 1);
}