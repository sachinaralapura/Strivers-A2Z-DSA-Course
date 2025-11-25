// #include "include/linkedList/ll.h"
// #include "include/linkedList/sll.h"
#include <iostream>
#include <ostream>
#include <vector>
int main() {
    // Sll<int> *sll = new Sll<int>();
    // for (int i = 0; i < 10; i++) {
    //     sll->addToHead(i + 1);
    // }
    // sll->reverse();
    // sll->printAll();
    // return 0;
    std::vector<int> my_vec;
    my_vec.push_back(34);
    int *arr = new int[10];
    std::cout << my_vec.max_size() << std::endl;
    std::cout << sizeof(my_vec) << std::endl;
    std::cout << sizeof(arr) << std::endl;
}
