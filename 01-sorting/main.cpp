#include "./check.h"
#include <iostream>
using namespace std;
int main(int argc, char const *argv[])
{
    vector<double> arr = {13.34, 46.33, 24.2234, 52.444, 20.234, 9};
    int n = sizeof(arr) / sizeof(arr[0]);
    cout << "Before selection sort: " << "\n";
    for (auto i : arr)
        cout << i << ",";
    cout << "\n";

    cout << isSorted(arr) << endl;
    return 0;
}
