#include "../ll.h"
#include <type_traits>

template <typename T> SllNode<T> *OddEven(SllNode<T> *head) {

    static_assert(std::is_same_v<T, int> || std::is_same_v<T, long>,
                  "Template parameter T must be either int or long.");

    SllNode<T> *oddHead = new SllNode(-1), *oddTail = oddHead;
    SllNode<T> *evenHead = new SllNode(-1), *evenTail = evenHead;
    SllNode<T> *current = head, *temp;
    while (current != nullptr) {
        temp = current;
        current = current->next;
        temp->next = nullptr;

        if (temp->info & 1) {
            oddTail->next = temp;
            oddTail = temp;
        } else {
            evenTail->next = temp;
            evenTail = temp;
        }
        evenTail->next = oddHead->next;
    }
    return evenHead->next;
}