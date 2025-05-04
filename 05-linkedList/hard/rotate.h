#include "../ll.h"

template <typename T> ST *rotateLL(ST *head, int k) {
    if (head == nullptr && head->next == nullptr)
        return head;
    int len = 1;
    ST *temp = head;
    while (temp->next != nullptr && ++len)
        temp = temp->next;
    temp->next = head;
    k = k % len;
    k = len - k;
    while (k--)
        temp = temp->next;
    head = temp->next;
    temp->next = nullptr;
    return head;
}
