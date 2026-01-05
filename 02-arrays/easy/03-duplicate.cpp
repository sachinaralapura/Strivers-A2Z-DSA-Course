// iven an integer array sorted in non-decreasing order, remove the duplicates in place such that
// each unique element appears only once. The relative order of the elements should be kept the
// same.

// If there are k elements after removing the duplicates, then the first k elements of the array
// should hold the final result. It does not matter what you leave beyond the first k elements.
#include <vector>
using namespace std;
int removeDuplicatesFromSorted(vector<int> &arr) {
    int ptr = 0;
    for (int i = 0; i < arr.size(); i++) {
        if (arr[ptr] != arr[i]) {
            ptr++;
            arr[ptr] = arr[i];
        }
    }
    return ptr + 1;
}
