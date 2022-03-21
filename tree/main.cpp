

#include <iostream>
#include <cassert>
#include "Tree.hpp"


int main() {
    std::cout << "Hello, World!" << std::endl;
    BSTTree<int> tree = BSTTree<int>();
    tree.insert(10);
    tree.insert(2);
    tree.insert(16);
    tree.insert(14);
    tree.insert(39);
    assert(tree.remove(10));
    std::cout << "Minimal Test for BST passed!" << std::endl;

    AVLTree<int> avl = AVLTree<int>();
    avl.insert(10);
    avl.insert(5);
    avl.insert(2);
    assert(avl.remove(5));
    std::cout << "Minimal Test for AVL passed!" << std::endl;

    return 0;
}

