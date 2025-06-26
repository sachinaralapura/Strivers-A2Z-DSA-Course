#include <bits/stdc++.h>
#include <string>
#include <vector>
using namespace std;
class PalindromePartition {
  private:
    string str;

  public:
    vector<vector<string>> result;
    vector<string> ds;
    void func(int index, string s, vector<string> &ds);
    bool isPalindrome(string s, int start, int end);
    PalindromePartition() : str("") {}
    PalindromePartition(string s) : str(s) { func(0, this->str, this->ds); }
    vector<vector<string>> GetResult() { return result; }
};

inline void PalindromePartition::func(int index, string s, vector<string> &ds) {
    if (index == s.size()) {
        result.push_back(ds);
        return;
    }
    for (int i = index; i < s.size(); i++) {
        if (isPalindrome(s, index, i)) {
            ds.push_back(s.substr(index, i - index + 1));
            func(i + 1, s, ds);
            ds.pop_back();
        }
    }
}

inline bool PalindromePartition::isPalindrome(string s, int start, int end) {
    while (start <= end) {
        if (s[start++] != s[end--])
            return false;
    }
    return true;
}
