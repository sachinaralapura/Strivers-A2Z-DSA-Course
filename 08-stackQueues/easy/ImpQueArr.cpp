// Implement Queue Using Array
#include <bits/stdc++.h>
using namespace std;

template <class T> class Queue {
  private:
    T *arr;
    int first;
    int last;
    int Size;
    int currSize = 0;

  public:
    Queue() {
        Size = 1000;
        arr = new T[Size];
        first = -1;
        last = -1;
    }
    void push(T data);
    void pop();
    T top();
    void size();
    bool isEmpty();
};

template <typename T> void Queue<T>::push(T data) {
    if (currSize == Size) {
        cout << "Queue is full\nExiting..." << endl;
        exit(1);
    }
    if (last == -1) {
        last = 0;
        first = 0;
    } else
        last = (last + 1) % Size;
    arr[last] = data;
    currSize++;
}

template <typename T> void Queue<T>::pop() {
    if (first == -1) {
        cout << "Queue Empty\nExiting..." << endl;
        exit(1);
    }
    if (currSize == 1) {
        first = -1;
        last = -1;
    } else
        first = (first + 1) % Size;
    currSize--;
}

template <typename T> T Queue<T>::top() {
    if (first == -1) {
        cout << "Queue Empty\nExiting..." << endl;
        exit(1);
    }
    return arr[first];
}
