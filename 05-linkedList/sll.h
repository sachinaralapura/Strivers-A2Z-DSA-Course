#include "ll.h"
#include "medium/deleteTail.h"
#include "medium/findMiddle.h"
#include "medium/isPalindrome.h"
#include "medium/oddEven.h"
#include "medium/reverse.h"
#include "medium/deleteMiddle.h"

template <class T> Sll<T>::Sll() : head(nullptr), tail(nullptr) {}

template <class T> Sll<T>::Sll(vector<T> list) {
    for (auto it : list) {
        addToTail(it);
    }
}

template <class T> Sll<T>::~Sll() {
    for (ST *p; !isEmpty();) {
        p = head->next;
        delete head;
        head = p;
    }
}

template <class T> void Sll<T>::addToHead(T el) {
    head = new ST(el, head);
    if (tail == nullptr)
        tail = head;
}

template <class T> void Sll<T>::addToTail(T el) {
    if (tail != nullptr) {
        tail->next = new ST(el);
        tail = tail->next;
    } else
        head = tail = new ST(el);
}

template <class T> int Sll<T>::deleteHead() {
    int el = head->info;
    ST *temp = head;
    if (head == tail)
        head = tail = nullptr;
    else
        head = head->next;
    delete temp;
    return el;
}

template <class T> int Sll<T>::deleteTail() {
    int el = tail->info;
    if (head == tail) {
        delete tail;
        head = tail = nullptr;
    } else {
        ST *temp;
        for (temp = head; temp->next != tail; temp = temp->next)
            ;
        delete tail;
        tail = temp;
        tail->next = nullptr;
    }
    return el;
}

template <class T> void Sll<T>::deleteNode(T el) {
    if (head == tail && el == head->info) {
        delete head;
        head = tail = nullptr;
    } else if (el == head->info) {
        ST *temp = head;
        head = head->next;
        delete temp;
    } else {
        ST *pred, *tmp;
        for (pred = head, tmp = head->next; tmp != nullptr && !(tmp->info == el);
             pred = pred->next, tmp = tmp->next)
            if (tmp != nullptr) {
                pred->next = tmp->next;
                if (tmp == tail)
                    tail = pred;
                delete tmp;
            }
    }
}

template <class T> bool Sll<T>::search(T el) const {
    ST *temp;
    for (temp = head; temp != nullptr && !(temp->info == el); temp = temp->next)
        ;
    return temp != nullptr;
}

template <class T> void Sll<T>::reverse() { head = reverse_iter(head); }

template <class T> ST *Sll<T>::getMiddle() { return findMiddle(head); }

template <class T> bool Sll<T>::isPalindrome() { return IsPalindrome(head); }

template <class T> void Sll<T>::SegregatetoOddEVen() { this->head = OddEven<T>(head); }

template <class T> void Sll<T>::deleteNthTail(int n) {
    int lenght = this->length();
    this->head = deleteTailFromNth(this->head, n, lenght);
}

template <class T> void Sll<T>::deleteMiddle(){
	this->head = deleteMiddleNode(this->head);
}

template <class T> void Sll<T>::printAll() const {
    ST *tmp;
    for (tmp = head; tmp != nullptr; tmp = tmp->next)
        std::cout << tmp->info << endl;
}
