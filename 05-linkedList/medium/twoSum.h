// given a sorted dll , find pairs that adds up to given number
#include "../ll.h"
#include <utility>

template <typename T> vector<pair<T, T>> twoSum(DT *head, DT *tail, int k) {
    static_assert(std::is_same_v<T, int> || std::is_same_v<T, long>,
                  "Template parameter T must be either int or long.");
    DT *left = head;
    DT *right = tail;
    vector<pair<T, T>> ans;
    while (left->info < right->info) {
        int sum = left->info + right->info;
        if (sum == k) {
            ans.push_back({left->info, right->info});
            left = left->next;
            right = right->prev;
            continue;
        } else if (sum < k) {
            left = left->next;
        } else {
            right = right->next;
        }
    }
    return ans;
}
