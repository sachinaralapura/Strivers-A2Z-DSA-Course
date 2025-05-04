// Delete all duplicates in sorted DLL
#include "../ll.h"
#include <cstdlib>

template <typename T> DT *DDuplicates(DT *head) {
    DT *temp = head;
    while (temp != nullptr && temp->next != nullptr) {
        DT *nextNode = temp->next;
        while (nextNode != nullptr && nextNode->info == temp->info) {
            DT *duplicate = nextNode;
            nextNode = nextNode->next;
            free(duplicate);
        }
        temp->next = nextNode;
        if (nextNode != nullptr) {
            nextNode->prev = temp;
        }
        temp = temp->next;
    }
    return head;
}
