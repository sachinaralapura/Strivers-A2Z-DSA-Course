#include "../ll.h"

template <typename T> ST *deleteTailFromNth(ST *head, int n, int length) {
    if (head == nullptr)
        return nullptr;

    int cnt = length - n;
    ST *temp = head;

    if (cnt == 0) {
        ST *newHead = head->next;
        delete (newHead);
        return newHead;
    }
    while (temp != nullptr) {
        cnt--;
        if (cnt == 0)
            break;
        temp = temp->next;
    }
    ST *deleteNode = temp->next;
    temp->next = temp->next->next;
    delete (deleteNode);
    return head;
}