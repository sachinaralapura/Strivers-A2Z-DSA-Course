#ifndef LL_GROUP_REVERSE
#define LL_GROUP_REVERSE
#include "../ll.h"
#include "../medium/reverse.h"

template <typename T> ST *groupReverse(ST *head, int k, int n) {
    if (k > n)
        return head;
    ST *temp = head;
    ST *prevNode = temp;
    while (temp != nullptr) {
        int count = 1;
        ST *kthNode = temp;
        while (count != k && kthNode != nullptr) {
            count++;
            kthNode = kthNode->next;
        }
        if (count < k)
            break;
        ST *nextNode = kthNode->next;
        kthNode->next = nullptr;
        temp == head ? head = reverse_iter(temp) : prevNode->next = reverse_iter(temp);

        prevNode = temp;
        temp = nextNode;
    }
    return head;
}
#endif
