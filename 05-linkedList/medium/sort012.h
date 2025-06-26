#ifndef LL_SORT_012
#define LL_SORT_012
#include "../ll.h"

template <typename T> void swapNode(ST *node1, ST *node2) {
  T temp = node1->info;
  node1->info = node2->info;
  node2->info = temp;
}
template <typename T> ST *highPrev(ST *mid, ST *high) {
  ST *temp = mid;
  while (temp->next != high) {
    temp = temp->next;
  }
  return temp;
}
template <typename T> ST *sort123(ST *head, ST *tail, int n) {
  ST *low = head;
  ST *mid = head;
  ST *high = tail;
  while (mid != high) {
    if (mid->info == 0) {
      swapNode(mid, low);
      mid = mid->next;
      low = low->next;
    } else if (mid->info == 1) {
      mid = mid->next;
    } else {
      swapNode(mid, high);
      high = highPrev(mid, high);
    }
  }
  if (mid->info == 0) {
       swapNode(mid, low);
       mid = mid->next;
       low = low->next;
     } else if (mid->info == 1) {
       mid = mid->next;
     } else {
       swapNode(mid, high);
       high = highPrev(mid, high);
     }
  return head;
}
#endif
