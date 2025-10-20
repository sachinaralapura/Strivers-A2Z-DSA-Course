
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
    inline bool isLess(const T &a, const T &b) { return _compare(a, b); }

  public:
    BinaryHeap(const Compare &comp = Compare());

    const T getNode(int) const;
    void buildHeapify(vector<T>);
    T leftChild(int);
    T rightChild(int);
    T parentNode(int);
    void insertNode(T);
    T removeRootNode();
    void swap(int, int);
};

template <class T, class Compare> BinaryHeap<T, Compare>::BinaryHeap(const Compare &comp) : _compare(comp) {}

template <class T, class Compare> void BinaryHeap<T, Compare>::swap(int _x, int _y) {
    int n = _arr.size();
    if (_x >= n || _y >= n) return;
    T temp = _arr[_x];
    _arr[_x] = _arr[_y];
    _arr[_y] = temp;
}
template <class T, class Compare> int BinaryHeap<T, Compare>::leftChildIndex(int _index) {
    int n = _arr.size();
    int left_index = 2 * _index + 1;
    if (left_index < n) return left_index;
    return -1;
}

template <class T, class Compare> int BinaryHeap<T, Compare>::rightChildIndex(int _index) {
    int n = _arr.size();
    if (_index > n) return -1;
    int right_index = 2 * _index + 2;
    if (right_index < n) return right_index;
    return -1;
}

template <class T, class Compare> int BinaryHeap<T, Compare>::parentNodeIndex(int _index) {
    if (_index == 0) return -1;
    return (_index - 1) / 2;
}

template <class T, class Compare> const T BinaryHeap<T, Compare>::getNode(int _index) const { return _arr[_index]; }

template <class T, class Compare> T BinaryHeap<T, Compare>::leftChild(int _index) {
    int index = this->leftChildIndex(_index);
    return _arr[index];
}

template <class T, class Compare> T BinaryHeap<T, Compare>::rightChild(int _index) {
    int index = this->rightChildIndex(_index);
    return _arr[index];
}

template <class T, class Compare> T BinaryHeap<T, Compare>::parentNode(int _index) {
    int index = this->parentNodeIndex(_index);
    return _arr[index];
}

template <class T, class Compare> void BinaryHeap<T, Compare>::insertNode(T _data) {
    _arr.push_back(_data);
    heapifyUp(_arr.size() - 1);
}

template <class T, class Compare> void BinaryHeap<T, Compare>::heapifyUp(int _index) {
    int curr = _index;
    while (curr != 0 && isLess(parentNode(curr), _arr[curr])) {
        swap(parentNode(curr), getNode(curr));
        curr = parentNodeIndex(curr);
    }
}

template <class T, class Compare> T BinaryHeap<T, Compare>::removeRootNode() {
    if (_arr.empty()) throw "Error";
    T root = _arr[0];
    _arr[0] = _arr[_arr.size() - 1];
    _arr.pop_back();
    heapifyDown(0);
    return root;
}

template <class T, class Compare> void BinaryHeap<T, Compare>::heapifyDown(int _index) {
    int n = _arr.size();
    int largest = _index;
    while (true) {
        int left = leftChildIndex(_index);
        int right = rightChildIndex(_index);

        if (left < n && isLess(leftChild(_index), getNode(largest))) largest = left;
        if (right < n && isLess(rightChild(_index), getNode(largest))) largest = right;
        if (largest != _index) {
            swap(getNode(largest), getNode(_index));
            _index = largest;
        } else
            break;
    }
}

template <class T, class Compare> void BinaryHeap<T, Compare>::buildHeapify(vector<T> arr) {
    int n = arr.size();
    _arr = arr;
    for (int i = ((n / 2) - 1); i >= 0; i--)
        heapifyDown(i);
}
