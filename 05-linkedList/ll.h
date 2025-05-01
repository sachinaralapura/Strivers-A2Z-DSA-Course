#ifndef LL_H // Unique identifier for this header (usually uppercase and includes the filename)
#define LL_H
#define ST SllNode<T>
#include <bits/stdc++.h>
#include <iostream>
using namespace std;

template <class T> class SllNode {
  public:
    T info;
    SllNode *next;
    SllNode() { next = nullptr; }
    SllNode(T i, SllNode<T> *in = 0) {
        info = i;
        next = in;
    }
};

template <class T> class Sll {
  private:
    SllNode<T> *head;
    SllNode<T> *tail;

  public:
    Sll();
    Sll(vector<T> list);
    ~Sll();
    SllNode<T> *getHead() const { return head; }
    void setHead(SllNode<T> *h) { this->head = h; }

    bool isEmpty() { return head == nullptr; }
    int length() {
        int length = 0;
        SllNode<T> *temp = head;
        while (temp != nullptr) {
            length++;
            temp = temp->next;
        }
        delete temp;
        return length;
    }
    void addToHead(T);
    void addToTail(T);
    int deleteHead();
    int deleteTail();
    void deleteNode(T);
    void deleteMiddle();
    bool search(T) const;
    void printAll() const;
    void reverse();
    SllNode<T> *getMiddle();
    bool isPalindrome();
    void SegregatetoOddEVen();
    void deleteNthTail(int n);
};

#endif
