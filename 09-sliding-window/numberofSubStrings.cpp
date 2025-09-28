#include <algorithm>
#include <iostream>
#include <map>
#include <unordered_map>
#include <vector>

int numberOfSubStrings(std::vector<char> arr) {
    int n = arr.size();
    int count = 0;
    for (int i = 0; i < n; i++) {
        std::map<char, int> mpp;
        for (int j = i; j < n; j++) {
            mpp[arr[j]] = 1;
            if (mpp['a'] + mpp['b'] + mpp['c'] == 3) {
                count = count + (n - j);
                break;
            }
        }
    }
    return count;
}

int numberOfSubStringsOpt(std::vector<char> arr) {
    int n = arr.size();
    int count = 0;
    std::unordered_map<char, int> mpp(3);
    mpp['a'] = -1;
    mpp['b'] = -1;
    mpp['c'] = -1;
    for (int i = 0; i < n; i++) {
        mpp[arr[i]] = i;
        if (mpp['a'] != -1 && mpp['b'] != -1 && mpp['c'] != -1) { // can omit this if case
            int min = std::min(mpp['a'], std::min(mpp['b'], mpp['c']));
            count = count + (min + 1);
        }
    }
    return count;
}

int main() {
    std::vector<char> arr = {'a', 'b', 'c', 'a', 'b', 'c'};
    const int count = numberOfSubStringsOpt(arr);
    std::cout << count << std::endl;
    return 0;
}
