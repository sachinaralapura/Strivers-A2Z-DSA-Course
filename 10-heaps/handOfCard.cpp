#include "heap.h"
#include <iostream>
#include <map>
#include <vector>
using namespace std;

bool handOfCard(vector<int> hand, int groupSize) {
    if (hand.size() % groupSize != 0)
        return false;
    map<int, int> freq;
    for (int card : hand) {
        freq[card]++;
    }
    auto it = freq.begin();
    while (it != freq.end()) {
        if (it->second == 0) {
            it++;
            continue;
        }
        int start = it->first;
        int count = it->second;
        for (int i = 0; i < groupSize; i++) {
            if (freq[start + i] < count) {
                return false;
            }
            freq[start + i] -= count;
        }
        it++;
    }
    return true;
}

int main(int argc, char const *argv[]) {
    vector<int> hand = {1, 2, 3, 6, 2, 3, 4, 7, 8};
    int groupSize = 3;
    bool result = handOfCard(hand, groupSize);
    for (int card : hand)
        cout << card << " ";
    cout << endl;
    cout << (result ? "True" : "False") << endl;
    return 0;
}
