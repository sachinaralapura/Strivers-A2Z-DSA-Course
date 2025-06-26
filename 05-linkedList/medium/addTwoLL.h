#ifndef LL_ADD_TWO
#define LL_ADD_TWO
#include "../ll.h"

template <typename T> ST *AddTwoLL(ST *l1, ST *l2) {
    ST *newll = new ST();
    ST *temp = newll;
    int carry = 0;
    while (l1 != nullptr || l2 != nullptr || carry) {
        int sum = 0;
        if (l1 != nullptr) {
            sum += l1->info;
            l1 = l1->next;
        }
        if (l2 != nullptr) {
            sum += l2->info;
            l2 = l2->next;
        }
        sum += carry;
        carry = sum / 10;
        ST *newNode = new ST(sum % 10);
        temp->next = newNode;
        temp = temp->next;
    }
    return newll->next;
}
#endif
