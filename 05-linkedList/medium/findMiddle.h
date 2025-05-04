#ifndef FINDMIDDLE_H
#define FINDMIDDLE_H

#include "../ll.h"
#include <bits/stdc++.h>
using namespace std;

template <typename T> ST *findMiddle(ST *head) {
    if (head == nullptr || head->next == nullptr)
        return head;

    ST *slow = head;
    // a node previous to middle 
    ST *fast = head->next;

    while (fast != nullptr && fast->next != nullptr) {
        slow = slow->next;
        fast = fast->next->next;
    }
    return slow;
}

#endif