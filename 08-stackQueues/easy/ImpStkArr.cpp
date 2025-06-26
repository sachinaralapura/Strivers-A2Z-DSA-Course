#include <bits/stdc++.h>
#include <iostream>
using namespace std;
template <class T> class Stack {
  private:
    T *arr;
    int Size;
    T Top;

  public:
    Stack() {
        Top = -1;
        Size = 1000;
        arr = new T[Size];
    }
    void push(T data);
    void pop();
    T top();
    int size();
};

template <typename T> void Stack<T>::push(T data) {
    Top++;
    arr[Top] = data;
}

template <typename T> void Stack<T>::pop() { Top--; }

template <typename T> T Stack<T>::top() { return arr[Top]; }

template <typename T> int Stack<T>::size() { return Top + 1; }

int main() {
    Stack<int> stk;
    for (int i = 0; i < 1000; i++) {
        stk.push(i + 1);
    }
    while (stk.size() != 0) {
        cout << stk.top() << endl;
        stk.pop();
    }
}
