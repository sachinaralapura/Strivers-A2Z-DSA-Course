#ifndef LL_REVERSE_H
#define LL_REVERSE_H

#include "../ll.h"
#include <bits/stdc++.h>
using namespace std;

template <typename T> SllNode<T> *reverse_iter(SllNode<T> *head) {
    SllNode<T> *prev = nullptr;
    SllNode<T> *cur = head;
    SllNode<T> *next = head;

    while (cur != nullptr) {
        next = cur->next;
        cur->next = prev;
        prev = cur;
        cur = next;
    }

    return prev;
}

template <typename T> SllNode<T> *reverse_recursive(SllNode<T> *head) {
    if (head == nullptr || head->next == nullptr)
        return head;
    SllNode<T> *newHead = reverse_recursive(head->next);
    SllNode<T> *front = head->next;
    front->next = head;
    head->next = nullptr;
    return newHead;
}

#endif
