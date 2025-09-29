#include <iostream>
#include <map>
using namespace std;
using FreqMap = map<char, int>;

int func(string str, int k) {
    int max_len = 0;
    int n = str.size();
    int left = 0, right = 0;
    FreqMap mpp;
    while (right < n) {
        mpp[str[right]]++;
        while (mpp.size() > k) {
            mpp[str[left]]--;
            if (mpp[str[left]] == 0) mpp.erase(str[left]);
            left += 1;
        }
        if (mpp.size() <= k) max_len = max(max_len, (right - left + 1));
        right += 1;
    }
    return max_len;
}

int main() {
    string str = "aababbcaacc";
    int k = 2;
    int max_len = func("abcddefg", 3);
    cout << max_len << endl;
    return 0;
}
