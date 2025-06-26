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
