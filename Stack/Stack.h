//
// Created by kruk on 22/11/2021.
//

#ifndef STACK_STACK_H
#define STACK_STACK_H

#include <iostream>
#include <vector>

#include "PointerList.h"

#define NMAX 20

template <class T> class Stack {

public:

    virtual void put(T val) = 0;
    virtual T poll() = 0;
    virtual bool isEmpty() = 0;
    virtual bool isFull() = 0;

};

template <class T> class ArrayStack : public Stack<T>{

    std::vector<T> array;
    int top{0};

public:

    ArrayStack(){
        for (int i = 0; i < NMAX; i++)
            array.push_back((T)(0));

    }

    void put(T val) {
        if (!isFull()){
            array.at(top++) = val;
        }
    }
    T poll() {
        if (!isEmpty()){
            return array.at(top--);
        }
    }
    bool isEmpty() {
        return top == 0;
    }
    bool isFull() {
        return top == NMAX;
    }

};

template <class T> class PointerStack :public Stack<T>{
    PointerList<T> *list;
    int top{0};
public:

    PointerStack(){
        list = new OneWayPointerList<T>();
    }

    void put(T val) {
        if (!isFull()){
            list->add(val);
            top++;
        }
    }
    T poll() {
        if (!isEmpty()){
           top++;
           T out = list->head->getVal();
           list->remove_i(0);
           return out;
        }
    }
    bool isEmpty() {
        return top == 0;
    }
    bool isFull() {
        return top == NMAX;
    }

};

#endif STACK_STACK_H
