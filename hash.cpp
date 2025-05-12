#include <bits/stdc++.h>
using namespace std;
const int TABLE_SIZE = 10;
int hashfunction(int key) { return key % TABLE_SIZE; }
int main() {
    vector<vector<int>> hashtable(TABLE_SIZE);
    vector<int> items;
    for (int i = 1; i <= 100; i++) {
        items.push_back(i);
    }
    for (int it : items) {
        int key = hashfunction(it);
        hashtable[key].push_back(it);
    }
    for (auto it : hashtable) {
        int len = it.size();
        for (auto i : it) {
            if (len > 1)
                cout << i << "->";
            else
                cout << i;
        }
        cout << endl;
    }
    return 0;
}
