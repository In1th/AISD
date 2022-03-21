#include <iostream>
#include <cassert>

#include "hash.hpp"

#define TAB_SIZE 10



template <typename T>
int func(T x, int k){
    return (( (int) (x)  % TAB_SIZE) + k) % TAB_SIZE;
}

using std::cout, std::endl;

int main() {
    std::cout << "Hello, World!" << std::endl;

    HashTable<int, TAB_SIZE> tab = HashTable<int, TAB_SIZE>(func<int>);
    tab.insert(10);
    tab.insert(5);
    tab.insert(2);
    tab.insert(20);
    tab.insert(30);
    assert(tab.search(30));
    assert(!tab.search(4));
    tab.deleteValue(20);
    assert(!tab.search(20));

    return 0;
}
