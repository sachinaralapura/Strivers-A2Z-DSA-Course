#include "OnAnswer/kthMissing.h"
#include "OnAnswer/books.h"
#include <iostream>

int main() {

    vector<int> arr = {25, 46, 28, 49, 24};
    int n = 5;
    int m = 4;
    int ans = findMinMaxPages(arr,m);
    cout << "The answer is: " << ans << "\n";
    return 0;
}
