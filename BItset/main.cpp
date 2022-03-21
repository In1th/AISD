#include <iostream>
#include "bitset.hpp"

int main() {
    BitArr<0,16> a{};
    std::cout << sizeof(BitArr<0,32>) << std::endl;
    return 0;
}
