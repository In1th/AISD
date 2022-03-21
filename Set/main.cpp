#include <iostream>

#include "set.hpp"

int main() {
    std::cout << "Hello, World!" << std::endl;
    Set<int> s1{}, s2{};
    s1.insert(5);
    s1.insert(10);
    s1.insert(1);
    s1.insert(6);
    s2.insert(6);
    s2.insert(2);
    s1.difference(s2);
    return 0;
}
