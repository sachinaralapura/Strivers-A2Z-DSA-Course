#include "heap.h"
#include <functional>
#include <iostream>
#include <random>
#include <vector>
using BinaryHeapMinHeap = BinaryHeap<int, greater<int>>; // min heap
using BinaryHeapMaxHeap = BinaryHeap<int, less<int>>;    // max heap

// 1. Create a random number engine (the generator)
// std::mt19937 is a widely used Mersenne Twister engine.
std::random_device rd; // Used to seed the generator from a non-deterministic source
std::mt19937 generator(rd());
// 2. Create a uniform integer distribution
// This ensures every integer from 1 to 1000 (inclusive) has an equal chance.
std::uniform_int_distribution<> distrib(1, 1000);

int main() {
    vector<int> arr;
    for (int i = 0; i < 10; i++) {
        int random_number = distrib(generator);
        arr.push_back(random_number);
    }
    BinaryHeapMinHeap heap(arr);
    int k = 3;
    std::cout << "The " << k << "th smallest element is: " << heap.kthSmallestElement(k)
              << std::endl;
    std::cout << "The " << k << "th largest element is: " << heap.kthLargestElement(k) << std::endl;
    while (!heap.isEmpty()) {
        auto a = heap.removeRootNode();
        std::cout << a << std::endl;
    }
    return 0;
}
