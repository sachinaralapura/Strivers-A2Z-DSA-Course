#ifndef LL_FIND_LOOP
#define LL_FIND_LOOP
#include <bits/stdc++.h>
using namespace std;

template <class T> class SllNode;
template <typename T> bool FindLoop(SllNode<T> *h) {
    SllNode<T> *slow = h;
    SllNode<T> *fast = h;

    while (fast != nullptr && fast->next != nullptr) {
        slow = slow->next;
        fast = fast->next->next;
        if (slow == fast)
            return true;
    }

    return false;
}

template <typename T> SllNode<T> *FindFirstNode(SllNode<T> *h) {
    SllNode<T> *slow = h;
    SllNode<T> *fast = h;
    bool loop = false;
    while (fast != nullptr && fast->next != nullptr) {
        slow = slow->next;
        fast = fast->next->next;
        if (slow == fast)
            loop = true;
    }

    if (loop) {
        slow = h;
        while (slow != fast) {
            slow = slow->next;
            fast = fast->next;
        }
        return slow;
    }
    return nullptr;
}

// length of the loop
template <typename T> int LoopLength(SllNode<T> *h) {
    SllNode<T> *slow = h;
    SllNode<T> *fast = h;
    int count = 0;
    while (fast != nullptr && fast->next != nullptr) {
        slow = slow->next;
        fast = fast->next->next;
        if (slow == fast) {
            do {
                count++;
                fast = fast->next;
            } while (slow != fast);
            return count;
        }
    }

    return 0;
}

#endif
