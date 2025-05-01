#include <bits/stdc++.h>
#include <iostream>

using namespace std;
struct TNode {
    TNode *links[26];
    bool flag = false;

    TNode() {
        for (int i = 0; i < 26; i++) {
            links[i] = nullptr;
        }
    }

    bool containsKey(char ch) { return links[ch - 'a'] != nullptr; }
    void setKey(char ch, TNode *node) { links[ch - 'a'] = node; }
    TNode *referenceNode(char ch) { return links[ch - 'a']; }
    void setFlag(bool f) { flag = f; }
};

class Trie {
  private:
    TNode *root = nullptr;
    void DeleteNode(TNode *node);
    void Print(TNode *, string);

  public:
    Trie() { root = new TNode(); }
    ~Trie() { DeleteNode(root); }
    void Insert(string str);
    bool Search(string str);
    bool StartWith(string str);
    void PrintTrie();
};

// O(len(str))
void Trie::Insert(string str) {
    TNode *node = root;
    for (int i = 0; i < str.length(); i++) {
        char ch = str[i];
        if (!node->containsKey(ch)) {
            node->setKey(ch, new TNode());
        }
        node = node->referenceNode(ch);
    }
    node->setFlag(true);
}

// O(len(str))
bool Trie::Search(string str) {
    TNode *node = root;
    for (int i = 0; i < str.length(); i++) {
        char ch = str[i];
        if (!node->containsKey(ch)) {
            return false;
        }
        node = node->referenceNode(ch);
    }
    return node->flag;
}

// O(len(str))
bool Trie::StartWith(string str) {
    TNode *node = root;
    for (int i = 0; i < str.length(); i++) {
        char ch = str[i];
        if (!node->containsKey(ch)) {
            return false;
        }
        node = node->referenceNode(ch);
    }
    return true;
}

void Trie::PrintTrie() { Print(this->root, ""); }

void DeleteNode(TNode *node) {
    if (node == nullptr)
        return;
    for (int i = 0; i < 26; i++) {
        if (node->links[i] != nullptr)
            DeleteNode(node->links[i]);
    }
    delete node;
}

void Trie::Print(TNode *node, string word) {
    if (node == nullptr)
        return;

    if (node->flag == true) {
        cout << word << endl; // print the word
    }

    for (int i = 0; i < 26; i++) {
        if (node->links[i] != nullptr) {
            char ch = 'a' + i;
            Print(node->links[i], word + ch); // go deeper, add the char
        }
    }
}
