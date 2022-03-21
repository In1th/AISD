//
// Created by kruk on 16/01/2022.
//

#ifndef HASH_H
#define HASH_H

#include "PointerList.h"
#include <iostream>
#include <vector>
#include <functional>

using std::vector, std::function;

template <typename T>
struct Position{
    T value{};
    bool empty{true};
};

template <typename T, int N>
class HashTable {

    vector< Position<T> > table{};
    function<int(T,int)> hash;



public:
    explicit HashTable(function<int(T,int)> function) noexcept;

    void insert(T value) noexcept;
    bool search(T value) noexcept;
    void deleteValue(T value) noexcept;

};




#include "hash.tpp"

#endif