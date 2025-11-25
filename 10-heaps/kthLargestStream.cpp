#include "heap.h"
#include <iostream>
#include <queue>
using namespace std;

class KthLargest {
  private:
    BinaryHeapMinHeap minHeap;
    int size;
    priority_queue<int, vector<int>, greater<int>> pq;

  public:
    KthLargest(int k, const vector<int> nums) {
        this->size = k;
        for (int it : nums) {
            this->minHeap.insertNode(it);
            if (minHeap.size() > k)
                minHeap.removeRootNode();
        }
    }

    int add(int val) {
        minHeap.insertNode(val);
        if (minHeap.size() > this->size)
            minHeap.removeRootNode();
        return minHeap.top();
    }
};

int main() {
    int k = 3;
    vector<int> num = {4, 5, 8, 2};
    KthLargest kthlargest(k, num);
    cout << kthlargest.add(3) << endl;  // Output: 4
    cout << kthlargest.add(5) << endl;  // Output: 5
    cout << kthlargest.add(10) << endl; // Output: 5
    cout << kthlargest.add(9) << endl;  // Output: 8
    cout << kthlargest.add(4) << endl;  // Output: 8
    return 0;
}
