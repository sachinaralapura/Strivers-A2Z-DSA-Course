#include <vector>
using namespace std;
template <typename T> bool isSorted(vector<T> &arr) {
    for (int i = 0; i < arr.size(); i++)
        for (int j = i + 1; j < arr.size(); j++)
            if (arr[i] > arr[j])
                return false;

    return true;
}

template <typename T> bool isSortedOpt(vector<T> &arr) {
    for (int i = 1; i < arr.size(); i++)
        if (arr[i - 1] > arr[i])
            return false;
    return true;
}
