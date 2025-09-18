#include <iostream>
#include <string>
#include <unordered_map>
using namespace std;

template <typename T> struct SNode {
    int key;
    T value;
};

template <typename T> class LruCache;
template <typename T> class Node;
template <typename T> ostream &operator<<(ostream &, const Node<T> &);

template <typename T> class Node {
  public:
    int key;
    T value;
    Node<T> *next;
    Node<T> *prev;
    Node(int k, T v) : key(k), value(v), next(nullptr), prev(nullptr) {}
    Node() : key(-1), next(nullptr), prev(nullptr) {}
    friend ostream &operator<< <T>(ostream &os, const Node<T> &p);
};

template <typename T> class LruCache {
  public:
    Node<T> *head = new Node<T>();
    Node<T> *tail = new Node<T>();
    int capacity;
    unordered_map<int, Node<T> *> mpp;

    LruCache(int cap);
    ~LruCache();

    void add(Node<T> *n);
    void deleteNode(Node<T> *n);
    T get(int key);
    void put(int _key, T value);
};

template <typename T> ostream &operator<<(ostream &os, const Node<T> &p) {
    if (p.key == -1) {
        os << "nullptr";
        return os;
    }
    os << "key: " << p.key << ", value: " << p.value;
    return os;
}
