#include "../ll.h"
#include "findMiddle.h"
template <typename T> ST *mergeSort(ST *head);

template <typename T> ST *sortlinkedList(ST *head) {
    return mergeSort<T>(head);
}

template <typename T> ST *merge(ST *left, ST *right) {
    // Create a dummy node to serve as the head of the merged list
    ST *dummyNode = new ST(-1);
    ST *temp = dummyNode;
    while (left != nullptr && right != nullptr) {
        if (left->info <= right->info) {
            temp->next = left;
            left = left->next;
        } else {
            temp->next = right;
            right = right->next;
        }
        temp = temp->next;
    }
    if (left != nullptr)
        temp->next = left;
    else
        temp->next = right;
    return dummyNode->next;
}

template <typename T> ST *mergeSort(ST *head) {
    // Base case: if the list is empty or has only one node
    // it is already sorted, so return the head
    if (head == nullptr || head->next == nullptr)
        return head;

    ST *middle = findMiddle(head);

    // divide the list in two half
    ST *right = middle->next;
    middle->next = nullptr;
    ST *left = head;

    // Recursively sort the left and right halves
    left = mergeSort<T>(left);
    right = mergeSort<T>(right);

    return merge<T>(left, right);
}
