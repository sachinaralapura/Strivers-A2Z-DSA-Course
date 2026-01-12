#ifndef LL_H // Unique identifier for this header (usually uppercase and
             // includes the filename)
#define LL_H
#define ST SllNode<T>
#define DT DllNode<T>
#include <bits/stdc++.h>
#include <iostream>
using namespace std;

// ==================== SLL ====================

template <class T> class SllNode {
  public:
    T info;
    SllNode *next;
    SllNode() {
        next = nullptr;
    }
    SllNode(T i, ST *in = 0) {
        info = i;
        next = in;
    }
};

template <class T> class Sll {
  private:
    ST *head;
    ST *tail;

  public:
    Sll();
    Sll(vector<T> list);
    ~Sll();
    ST *getHead() const {
        return head;
    }
    void setHead(ST *h) {
        this->head = h;
    }

    bool isEmpty() {
        return head == nullptr;
    }
    int length() {
        int length = 0;
        ST *temp = head;
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
    ST *getMiddle();
    bool isPalindrome();
    void SegregatetoOddEVen();
    void deleteNthTail(int n);
    void sort();
    void sortZeroOneTwo();
    ST *intersectionPoint(ST *, ST *);
    void addOne();
    void reverseGroup(int k);
    void rotate(int k);
};

// ==================== DLL ====================
template <class T> class DllNode {
  public:
    T info;
    DT *next, *prev;
    DT() {
        next = prev = nullptr;
    }
    DT(const T &info, DT *n = nullptr, DT *p = nullptr) {
        this->info = info;
        this->next = n;
        this->prev = p;
    }
};

template <class T> class DoublyLinkedList {
  private:
    DT *head, *tail;

  public:
    DoublyLinkedList<T>() {
        head = tail = nullptr;
    }
    DoublyLinkedList<T>(vector<T> &);
    ~DoublyLinkedList<T>();
    bool isEmpty() {
        return head == nullptr;
    }
    int length();
    void addToTail(const T &el);
    T deleteTail();
    void display();
    void deleteEl(const T el);
};

// ==================== RANDOM LIST ====================

template <class T> class RNode {
  public:
    T data;
    RNode<T> *next;
    RNode<T> *random;
    RNode<T>(T data) {
        this->data = data;
        next = nullptr;
        random = nullptr;
    }
};

#endif
