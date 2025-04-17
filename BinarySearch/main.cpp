#include "OnAnswer/kthMissing.h"
#include "OnAnswer/painter.h"
#include <iostream>

int main() {

    vector<int> a = {10, 20, 30, 40};
    int k = 2;
    int ans = painterPartition(a, k);
    cout << "The answer is: " << ans << "\n";
    return 0;
}
