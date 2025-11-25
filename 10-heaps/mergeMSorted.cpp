// Problem Statement : Given heads of k sorted linked lists as an array called heads, merge them
// into one single sorted linked list and return the head of that list.;
struct ListNode {
    int data;
    ListNode *next;
    ListNode(int x) : data(x), next(nullptr) {}
};

#include "heap.h"
#include <functional>
#include <iostream>
#include <vector>
using namespace std;

auto compare = [](ListNode *a, ListNode *b) { return a->data > b->data; };
using ListNodeMinHeap = BinaryHeap<ListNode *, function<bool(ListNode *, ListNode *)>>;

ListNode *MergeMSortedLists(vector<ListNode *> &lists) {
    ListNodeMinHeap minHeap(compare);
    for (ListNode *head : lists)
        if (head != nullptr)
            minHeap.insertNode(head);
    ListNode *dummy = new ListNode(-1);
    ListNode *temp = dummy;
    while (!minHeap.isEmpty()) {
        ListNode *smallest = minHeap.removeRootNode();
        temp->next = smallest;
        temp = temp->next;
        if (smallest->next != nullptr)
            minHeap.insertNode(smallest->next);
    }
    return dummy->next;
}

int main(int argc, char const *argv[]) {
    vector<vector<int>> input = {{1, 4, 5}, {1, 3, 4}, {2, 6}, {0, 9, 10, 11}, {7, 8}};
    vector<ListNode *> lists;
    for (const auto &vec : input) {
        ListNode *dummy = new ListNode(-1);
        ListNode *temp = dummy;
        for (int val : vec) {
            temp->next = new ListNode(val);
            temp = temp->next;
        }
        lists.push_back(dummy->next);
    }
    ListNode *sorted = MergeMSortedLists(lists);
    ListNode *temp = sorted;
    while (temp != nullptr) {
        cout << temp->data << endl;
        temp = temp->next;
    }
    // delete allocated memory
    temp = sorted;
    while (temp != nullptr) {
        ListNode *nextNode = temp->next;
        delete temp;
        temp = nextNode;
    }
    return 0;
}
