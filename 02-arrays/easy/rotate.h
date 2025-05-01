#include <vector>
#include <iostream>
using namespace std;
template <typename T>
void rotate_left(vector<T> &arr)
{
    T temp = arr[0];
    for (int i = 1; i < arr.size(); i++)
    {
        arr[i - 1] = arr[i];
    }
    arr[arr.size() - 1] = temp;
    for (auto i : arr)
    {
        cout << i << ",";
    }
}

// rotate k elements
template <typename T>
void rotateRight(vector<T> &arr, int k)
{
    int n = arr.size();
    if (n == 0)
        return;
    k = k % n;
    if (k > n)
        return;
    T temp[k];
    for (int i = n - k; i < n; i++)
    {
        temp[i - n + k] = arr[i];
    }
    for (int i = n - k - 1; i >= 0; i--)
    {
        arr[i + k] = arr[i];
    }
    for (int i = 0; i < k; i++)
    {
        arr[i] = temp[i];
    }
}

// Reversal Algorithm
template <typename T>
void reverse(vector<T> &arr, int start, int end)
{
    while (start <= end)
    {
        T t = arr[start];
        arr[start] = arr[end];
        arr[end] = t;
        start++;
        end--;
    }
}

template <typename T>
void ReverseRotate(vector<T> &arr, int k)
{
    int n = arr.size() - 1;
    reverse(arr, 0, n - k);
    reverse(arr, n - k + 1, n);
    reverse(arr, 0, n);
}
