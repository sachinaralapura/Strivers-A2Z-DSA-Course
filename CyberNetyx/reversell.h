// https://youtu.be/D2vI2DNJGd8?si=ERB-KRjcX3FTnoP8

#include <iostream>
using namespace std;
class Node {
  public:
    int data;
    Node *next;

    Node() { this->next = nullptr; }
    Node(int data) {
        this->data = data;
        next = nullptr;
    }
};

class SLL {
  public:
    Node *head;
    Node *tail;
    SLL() {
        this->head = nullptr;
        this->tail = nullptr;
    }

    void addToTail(int data) {
        if (tail != nullptr) {
            this->tail->next = new Node(data);
            this->tail = tail->next;
        } else {
            head = tail = new Node(data);
        }
    }
    void PrintAll() {
        Node *temp = head;
        while (temp != nullptr) {
            cout << temp->data << endl;
            temp = temp->next;
        }
    }

    void reverse() {
        Node *prev, *cur, *next;
        prev = nullptr;
        cur = this->head;
        next = cur->next;
        while (cur != nullptr) {
            next = cur->next;
            cur->next = prev;
            prev = cur;
            cur = next;
        }
        this->head = prev;
    }

    void recursive_reverse() { rr(this->head); }

  private:
    Node *rr(Node *h) {
        // zero or one node
        if (h == nullptr || h->next == nullptr) {
            this->head = h;
            return h;
        }

        Node *newHead = this->rr(h->next);
        Node *front = h->next;
        front->next = h;
        h->next = nullptr;
        return newHead;
    }
};

