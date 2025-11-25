#include <algorithm>
#include <type_traits>
#include <vector>
using namespace std;

template <class T, class Compare = less<T>> class BinaryHeap {
  private:
    vector<T> _arr;
    Compare _compare;

    int leftChildIndex(int);
    int rightChildIndex(int);
    int parentNodeIndex(int);
    void heapifyUp(int);
    void heapifyDown(int);
    inline bool compare(const T &a, const T &b) {
        return _compare(a, b);
    }

  public:
    BinaryHeap(const Compare &comp = Compare());
    BinaryHeap(const vector<T> &arr);
    template <typename Iterator>
    BinaryHeap(Iterator begin, Iterator end, const Compare &comp = Compare());
    T getNode(int) const;
    void buildHeapify(vector<T>);
    void heapify();
    T leftChild(int);
    T rightChild(int);
    T parentNode(int);
    void insertNode(T);
    T removeRootNode();
    T &top() const;
    T &last() const;
    int size() const {
        return _arr.size();
    }
    void swap(int, int);
    bool isEmpty() {
        return _arr.empty();
    }
    bool isMinHeap();
    bool isMaxHeap();
    T kthSmallestElement(int);
    T kthLargestElement(int);
};

template <class T, class Compare>
BinaryHeap<T, Compare>::BinaryHeap(const Compare &comp) : _compare(comp) {}

template <class T, class Compare> BinaryHeap<T, Compare>::BinaryHeap(const vector<T> &arr) {
    this->buildHeapify(arr);
}

template <class T, class Compare>
template <typename Iterator>
BinaryHeap<T, Compare>::BinaryHeap(Iterator begin, Iterator end, const Compare &comp)
    : _compare(comp) {
    vector<T> arr(begin, end);
    this->buildHeapify(arr);
}

template <class T, class Compare> void BinaryHeap<T, Compare>::swap(int _x, int _y) {
    int n = _arr.size();
    if (_x >= n || _y >= n)
        return;
    T temp = _arr[_x];
    _arr[_x] = _arr[_y];
    _arr[_y] = temp;
}

template <class T, class Compare> int BinaryHeap<T, Compare>::leftChildIndex(int _index) {
    int n = _arr.size();
    int left_index = 2 * _index + 1;
    if (left_index < n)
        return left_index;
    return -1;
}

template <class T, class Compare> int BinaryHeap<T, Compare>::rightChildIndex(int _index) {
    int n = _arr.size();
    if (_index > n)
        return -1;
    int right_index = 2 * _index + 2;
    if (right_index < n)
        return right_index;
    return -1;
}

template <class T, class Compare> int BinaryHeap<T, Compare>::parentNodeIndex(int _index) {
    if (_index == 0)
        return -1;
    return (_index - 1) / 2;
}

template <class T, class Compare> T BinaryHeap<T, Compare>::getNode(int _index) const {
    return _arr[_index];
}

template <class T, class Compare> T BinaryHeap<T, Compare>::leftChild(int _index) {
    int index = this->leftChildIndex(_index);
    if (index == -1)
        throw "No left child";
    return _arr[index];
}

template <class T, class Compare> T BinaryHeap<T, Compare>::rightChild(int _index) {
    int index = this->rightChildIndex(_index);
    if (index == -1)
        throw "No right child";
    return _arr[index];
}

template <class T, class Compare> T BinaryHeap<T, Compare>::parentNode(int _index) {
    int index = this->parentNodeIndex(_index);
    if (index == -1)
        throw "No parent node";
    return _arr[index];
}

template <class T, class Compare> void BinaryHeap<T, Compare>::insertNode(T _data) {
    _arr.push_back(_data);
    heapifyUp(_arr.size() - 1);
}

template <class T, class Compare> void BinaryHeap<T, Compare>::heapifyUp(int _index) {
    int curr = _index;
    while (curr != 0 && compare(parentNode(curr), _arr[curr])) {
        swap(parentNodeIndex(curr), curr);
        curr = parentNodeIndex(curr);
    }
}

template <class T, class Compare> T BinaryHeap<T, Compare>::removeRootNode() {
    if (_arr.empty())
        throw "Empty Heap";
    T root = _arr[0];
    _arr[0] = _arr[_arr.size() - 1];
    _arr.pop_back();
    heapifyDown(0);
    return root;
}

template <class T, class Compare> T &BinaryHeap<T, Compare>::top() const {
    if (_arr.empty())
        throw "Empty Heap";
    return const_cast<T &>(_arr[0]);
}

template <class T, class Compare> T &BinaryHeap<T, Compare>::last() const {
    if (_arr.empty())
        throw "Empty Heap";
    return const_cast<T &>(_arr[_arr.size() - 1]);
}

template <class T, class Compare> void BinaryHeap<T, Compare>::heapifyDown(int _index) {
    int n = _arr.size();
    int curr = _index;

    while (true) {
        int left = leftChildIndex(curr);
        int right = rightChildIndex(curr);
        int highest_priority = curr; // Assume current node is highest priority

        // Compare with Left Child
        // Check if left child exists AND left child has higher priority than current 'highest'
        if (left != -1 && compare(_arr[highest_priority], _arr[left])) {
            highest_priority = left;
        }

        // Compare with Right Child
        // Check if right child exists AND right child has higher priority than current 'highest'
        if (right != -1 && compare(_arr[highest_priority], _arr[right])) {
            highest_priority = right;
        }

        // If a child had higher priority, swap and continue down
        if (highest_priority != curr) {
            std::swap(_arr[curr], _arr[highest_priority]);
            curr = highest_priority; // Continue down from the swapped child's position
        } else {
            // Heap property satisfied at this node
            break;
        }
    }
}

template <class T, class Compare> void BinaryHeap<T, Compare>::buildHeapify(vector<T> arr) {
    int n = arr.size();
    _arr = arr;
    for (int i = ((n / 2) - 1); i >= 0; i--)
        heapifyDown(i);
}

template <class T, class Compare> void BinaryHeap<T, Compare>::heapify() {
    this->buildHeapify(_arr);
}

template <class T, class Compare> bool BinaryHeap<T, Compare>::isMinHeap() {
    if (!is_arithmetic_v<T>)
        throw "No a arithmetic type";
    for (int i = 0; i < (_arr.size() / 2); i++) {
        int left = leftChildIndex(i);
        if (left != -1 && _arr[left] < _arr[i])
            return false;
        int right = rightChildIndex(i);
        if (right != -1 && _arr[right] < _arr[i])
            return false;
    }
    return true;
}

template <class T, class Compare> bool BinaryHeap<T, Compare>::isMaxHeap() {
    if (!is_arithmetic_v<T>)
        throw "No a arithmetic type";
    for (int i = 0; i < (_arr.size() / 2); i++) {
        int left = leftChildIndex(i);
        if (left != -1 && _arr[left] > _arr[i])
            return false;
        int right = rightChildIndex(i);
        if (right != -1 && _arr[right] > _arr[i])
            return false;
    }
    return true;
}

template <class T, class Compare> T BinaryHeap<T, Compare>::kthSmallestElement(int k) {
    if (!is_arithmetic_v<T>)
        throw "No a arithmetic type";
    if (k <= 0 || k > _arr.size())
        throw "k is out of bounds";
    BinaryHeap<T, greater<T>> minHeap; // Min-heap to store the elements
    for (const T &element : _arr) {
        minHeap.insertNode(element);
    }
    T kthSmallest;
    for (int i = 0; i < k; i++) {
        kthSmallest = minHeap.removeRootNode();
    }
    return kthSmallest;
}

template <class T, class Compare> T BinaryHeap<T, Compare>::kthLargestElement(int k) {
    if (!is_arithmetic_v<T>)
        throw "No a arithmetic type";
    if (k <= 0 || k > _arr.size())
        throw "k is out of bounds";
    BinaryHeap<T, less<T>> maxHeap; // Max-heap to store the elements
    for (const T &element : _arr) {
        maxHeap.insertNode(element);
    }
    T kthLargest;
    for (int i = 0; i < k; i++) {
        kthLargest = maxHeap.removeRootNode();
    }
    return kthLargest;
}

using BinaryHeapMinHeap = BinaryHeap<int, greater<int>>; // min heap
using BinaryHeapMaxHeap = BinaryHeap<int, less<int>>;    // max heap
