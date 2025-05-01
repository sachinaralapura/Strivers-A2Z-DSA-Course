#ifndef FINDMIDDLE_H
#define FINDMIDDLE_H

#include "../ll.h"
#include <bits/stdc++.h>
using namespace std;

template <typename T> ST *findMiddle(ST *head) {
    ST *fast = head;
    ST *slow = head;

    while (fast != nullptr && fast->next != nullptr) {
        slow = slow->next;
        fast = fast->next->next;
    }
    return slow;
}

#endif 