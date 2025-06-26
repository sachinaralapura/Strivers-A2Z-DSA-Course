#ifndef LL_DELETE_MIDDLE
#define LL_DELETE_MIDDLE

#include "../ll.h"
#include "findMiddle.h"
template <typename T> ST *deleteMiddleNode(ST *head) {
    if (head == nullptr || head->next == nullptr)
        return nullptr;

    ST *slow = head;
    ST *fast = head;
    fast = head->next->next;

    while (fast != nullptr && fast->next != nullptr) {
        slow = slow->next;
        fast = fast->next->next;
    }

    ST *deleteNode = slow->next;
    slow->next = slow->next->next;
    delete deleteNode;
    return head;
}

#endif
