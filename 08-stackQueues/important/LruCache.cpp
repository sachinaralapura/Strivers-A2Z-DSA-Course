#include "LruCache.h"

template <typename T> LruCache<T>::LruCache(int cap) {
    capacity = cap;
    head->next = tail;
    tail->prev = head;
}

template <typename T> void LruCache<T>::add(Node<T> *n) {
    Node<T> *temp = this->head->next;
    n->next = temp;
    n->prev = head;
    this->head->next = n;
    temp->prev = n;
}

template <typename T> void LruCache<T>::deleteNode(Node<T> *n) {
    Node<T> *delprev = n->prev;
    Node<T> *delNext = n->next;
    delprev->next = delNext;
    delNext->prev = delprev;
}

template <typename T> T LruCache<T>::get(int _key) {
    if (this->mpp.find(_key) != this->mpp.end()) {
        Node<T> *temp = this->mpp[_key];
        T res = temp->value;
        this->mpp.erase(_key);
        this->deleteNode(temp);
        this->add(temp);
        this->mpp[_key] = this->head->next;
        return res;
    }
    return T();
}

template <typename T> LruCache<T>::~LruCache() {
    Node<T> *current = head;
    Node<T> *nextNode;
    while (current != nullptr) {
        nextNode = current->next;
        delete current;
        current = nextNode;
    }
}

template <typename T> void LruCache<T>::put(int _key, T value) {
    if (mpp.find(_key) != mpp.end()) {
        Node<T> *existingNode = mpp[_key];
        mpp.erase(_key);
        deleteNode(existingNode);
    }
    if (mpp.size() == capacity) {
        mpp.erase(tail->prev->key);
        deleteNode(tail->prev);
    }
    add(new Node<T>(_key, value));
    mpp[_key] = head->next;
}

int main(int argc, char const *argv[]) {
    LruCache<string> *pp = new LruCache<string>(5);
    pp->put(1, "one");
    pp->put(2, "two");
    pp->put(3, "three");
    pp->put(4, "four");
    pp->put(5, "five");
    cout << pp->get(1) << endl;
    pp->put(6, "six");
    cout << pp->get(2) << endl;
    cout << pp->get(3) << endl;
    cout << pp->get(4) << endl;
    cout << pp->get(5) << endl;
    cout << pp->get(6) << endl;
    delete pp;
    return 0;
}
