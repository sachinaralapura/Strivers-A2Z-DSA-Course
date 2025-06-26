#ifndef LL_INTER_POINT
#define LL_INTER_POINT
#include "../ll.h"

template <typename T> ST *IPoint(ST *head1, ST *head2) {
    if (head1 == nullptr || head2 == nullptr)
        return nullptr;

    ST *temp1 = head1;
    ST *temp2 = head2;
    while (temp1 != temp2) {
        temp1 = temp1 == nullptr ? head2 : temp1->next;
        temp2 = temp2 = nullptr ? head1 : temp2->next;
    }
    return temp1;
}

#endif
