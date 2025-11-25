#include "heap.h"
#include <functional>
#include <iostream>

class MedianStream {
  private:
    BinaryHeap<int, greater<int>> minHeap;
    BinaryHeap<int, less<int>> maxHeap;

  public:
    MedianStream() {}

    void addNum(int val) {
        maxHeap.insertNode(val);
        minHeap.insertNode(maxHeap.removeRootNode());
        if (minHeap.size() > maxHeap.size()) {
            maxHeap.insertNode(minHeap.removeRootNode());
        }
    }

    double findMedian() {
        if (maxHeap.size() == minHeap.size()) {
            return (maxHeap.top() + minHeap.top()) / 2.0;
        }
        return maxHeap.top();
    }
};

int main() {
    MedianStream mf;
    mf.addNum(1);
    mf.addNum(2);
    cout << mf.findMedian() << endl; // Output: 1.5
    mf.addNum(3);
    cout << mf.findMedian() << endl; // Output: 2
    return 0;
}
