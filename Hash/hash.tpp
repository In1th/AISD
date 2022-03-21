//
// Created by kruk on 16/01/2022.
//

#include "hash.hpp"

template<typename T, int N>
HashTable<T, N>::HashTable(function<int(T, int)> function) noexcept {
    hash = function;
    Position<T> temp;
    for (int i = 0; i < N; i++){
        table.push_back(temp);
    }
}

template<typename T, int N>
void HashTable<T, N>::insert(T value) noexcept {
    int k = 0;
    while (k < N){
        auto index = hash(value, k);
        auto &[val, isEmpty] = table.at(index);
        if (isEmpty){
            val = value;
            isEmpty = false;
            return;
        }
        k++;
    }
}

template<typename T, int N>
bool HashTable<T, N>::search(T value) noexcept {
    int k = 0;
    while (k < N){
        auto index = hash(value, k);
        auto &[val, isEmpty] = table.at(index);
        if (!isEmpty && val == value) return true;
        k++;
    }
    return false;
}

template<typename T, int N>
void HashTable<T, N>::deleteValue(T value) noexcept {
    int k = 0;
    while (k < N){
        auto index = hash(value, k);
        auto &[val, isEmpty] = table.at(index);
        if (!isEmpty && value == val){
            isEmpty = true;
            return;
        }
        k++;
    }
}

