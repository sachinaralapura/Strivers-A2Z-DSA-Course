#ifndef LL_ADD_ONE
#define LL_ADD_ONE
#include "../ll.h"
#include "reverse.h"
template <typename T> ST *addOneLinkList(ST *head) {
    static_assert(std::is_same_v<T, int> || std::is_same_v<T, long>,
                  "Template parameter T must be either int or long.");
    T carry = 1;
    head = reverse_iter(head);

    ST *temp = head;
    while (temp != nullptr) {
        temp->info = temp->info + carry;
        if (temp->info < 10) {
            carry = 0;
            break;
        } else {
            temp->info = 0;
            carry = 1;
        }
        temp = temp->next;
    }

    if (carry == 1) {
        ST *newNode = new ST(1);
        newNode->next = head;
        return newNode;
    }

    head = reverse_iter(head);
    return head;
}

template <typename T> int recursive(ST *temp) {
    if (temp == nullptr) {
        return 1;
    }
    int carry = recursive(temp->next);
    temp->info = temp->info + 1;
    if (temp->info < 10) {
        return 0;
    }

    temp->info = 0;
    return 1;
}

template <typename T> ST *addOne_recursive(ST *head) {
    static_assert(std::is_same_v<T, int> || std::is_same_v<T, long>,
                  "Template parameter T must be either int or long.");
    int carry = recursive(head);
    if (carry == 1) {
        ST *newHead = new ST(1);
        newHead->next = head;
        return newHead;
    }
    return head;
}
#endif
