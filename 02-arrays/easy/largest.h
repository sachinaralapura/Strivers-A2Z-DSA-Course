#include <bits/stdc++.h>
using namespace std;
template <typename T>
T largest_brute(vector<T> &arr)
{
    sort(arr.begin(), arr.end());
    return arr[arr.size() - 1];
}

template <typename T>
T largest_iter(vector<T> &arr)
{
    T max = arr[0];
    for (int i = 0; i < arr.size(); i++)
    {
        if (arr[i] > max)
        {
            max = arr[i];
        }
    }
    return max;
}

template <typename T>
T second_largest(vector<T> &arr)
{
    if (arr.size() < 2)
        return -1;
    T max = arr[0];
    T second_max = arr[0];
    for (int i = 0; i < arr.size(); i++)
    {
        if (arr[i] > max)
        {
            second_max = max;
            max = arr[i];
        }
        else if (arr[i] > second_max && arr[i] != max)
        {
            second_max = arr[i];
        }
    }
    return second_max;
}
