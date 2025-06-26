#ifndef LL_ISPALINDROME_H
#define LL_ISPALINDROME_H
#include "../ll.h"

template <typename T> bool IsPalindrome(SllNode<T> *head) {
    stack<T> stk;
    SllNode<T> *temp;
    for (temp = head; temp != nullptr; temp = temp->next) {
        stk.push(temp->info);
    }
    temp = head;
    for (temp = head; temp != nullptr; temp = temp->next) {
        T ele = stk.top();
        if (ele != temp->info) {
            return false;
        }
        stk.pop();
    }
    return true;
}


#endif
