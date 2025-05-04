#ifndef DLL_H
#define DLL_H
#include "ll.h"

template <class T> DoublyLinkedList<T>::DoublyLinkedList(vector<T> &v) {
    this->head = this->tail = nullptr;
    for (auto it : v) {
        this->addToTail(it);
    }
}

template <class T> DoublyLinkedList<T>::~DoublyLinkedList<T>() {
    while (head != nullptr) {
        if (head == tail) { // Special case: only one node left
            delete head;
            head = tail = nullptr;
            break;
        } else {
            DT *headNext = head->next;
            DT *tailPrev = tail->prev;
            delete head;
            delete tail;
            head = headNext;
            tail = tailPrev;
            if (head)
                head->prev = nullptr;
            if (tail)
                head->next = nullptr;
        }
    }
}

template <class T> void DoublyLinkedList<T>::addToTail(const T &el) {
    if (tail != nullptr) {
        tail = new DT(el, nullptr, tail);
        tail->prev->next = tail;
    } else
        head = tail = new DT(el);
}

template <class T> T DoublyLinkedList<T>::deleteTail() {
    T info = tail->info;
    if (tail == head) {
        delete tail;
        head = tail = nullptr;
    } else {
        tail = tail->prev;
        delete tail->next;
        tail->next = nullptr;
    }
    return info;
}

template <class T> int DoublyLinkedList<T>::length() {
    if (head == nullptr)
        return 0;
    DT *temp = head;
    int len = 0;
    while (temp != tail) {
        len++;
        temp = temp->next;
    }
    return len;
}

template <class T> void DoublyLinkedList<T>::deleteEl(const T el) {
    DT *h = this->head;
    while (h != nullptr) {
        if (h->info == el) {
            h->prev != nullptr ? h->prev->next = h->next : this->head = h->next;
            h->next != nullptr ? h->next->prev = h->prev : this->tail = h->prev;
            DT *t = h;
            h = h->next;
            delete t;
            continue;
        }
        h = h->next;
    }
}

template <class T> void DoublyLinkedList<T>::display() {
    DT *tmp;
    for (tmp = head; tmp != nullptr; tmp = tmp->next) {
        std::cout << tmp->info << std::endl;
    }
}

#endif
