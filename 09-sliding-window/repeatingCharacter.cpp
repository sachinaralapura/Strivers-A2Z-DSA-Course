#include <algorithm>
#include <climits>
#include <iostream>
#include <string>
#include <unordered_map>
using namespace std;
using CharMap = unordered_map<char, int>;

int repeatingCharacter(string str, int k) {
    const int n = str.length();
    int max_len = 0;
    for (int i = 0; i < n; i++) {
        CharMap mpp(26);
        int max_freq = 0;
        for (int j = i; j < n; j++) {
            mpp[str[j]]++;
            max_freq = max(max_freq, mpp[str[j]]);
            int changes = (j - i + 1) - max_freq;
            if (changes <= k)
                max_len = max(max_len, j - i + 1);
            else
                break;
        }
    }
    return max_len;
}

int repeatingCharacterTwoPointer(string str, int k) {
    const int n = str.length();
    int max_len = 0;
    int right = 0;
    int left = 0;
    CharMap mpp(26);
    int max_freq = 0;
    for (char c : str) {
        mpp[str[right]]++;
        max_freq = max(max_freq, mpp[str[right]]);
        int changes = (right - left + 1) - max_freq;
        if (changes > k) {
            mpp[str[left]]--;
            // max_freq = 0;
            // for (auto it : mpp)
            //     max_freq = max(max_freq, it.second);
            // if (mpp[str[left]] == 0) mpp.erase(mpp.find(str[left]));
            changes = (right - left + 1) - max_freq;
            left++;
        }
        if (changes <= k)
            max_len = max(max_len, right - left + 1);
        right++;
    }
    return max_len;
}

int main() {
    string str = "AAAAABACBAABBCCD";
    int max_len = repeatingCharacterTwoPointer(str, 2);
    cout << max_len << endl;
}
