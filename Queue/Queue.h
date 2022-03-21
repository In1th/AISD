//
// Created by kruk on 13/12/2021.
//

#ifndef QUEUE_QUEUE_H
#define QUEUE_QUEUE_H
#include <vector>
#include "PointerList.h"

#define QUEUE_MAX 20

template <class T> class Queue {
protected:
    int size{0};
public:
    virtual void put(T val) = 0;
    virtual T poll() = 0;
    virtual bool isFull() = 0;
    virtual bool isEmpty() = 0;
    virtual void print() = 0;
    virtual ~Queue() = 0;
};



template <class T> class ArrayQueue :public Queue<T>{
    std::vector<T> array;
    int start{0}, end{0};

public:
    ArrayQueue(){
        for(int i = 0; i < QUEUE_MAX; i++){
            array.add(0);
        }
    }
    void put(T val) {
        if (!isFull()){
            array[end] = val;
            end = (end+1)%QUEUE_MAX;
            this->size++;
        }
    }
    T poll() {
        if (!isEmpty()){
            this->size--;
            T tmp = array[start];
            start = (start+1)%QUEUE_MAX;
            return tmp;
        }
    }
    bool isFull() {
        return this->size == QUEUE_MAX;
    }
    bool isEmpty() {
        return this->size == 0;
    }
    void print(){
        for (int i = start; i != end; start = (start+1)%QUEUE_MAX){
            std::cout << array.at(i) << " ";
        }
        std::cout << std::endl;
    }

};

template <class T> class PointerQueue : public Queue<T>{
    TwoWayPointerList<T> list;
public:
    void put(T val) {
        list.add(val);
    }
    T poll() {
        return list.removeLast();
    }
    bool isFull() {
        return this->size == QUEUE_MAX;
    }
    bool isEmpty() {
        return this->size == 0;
    }
    void print(){
        list.print();
    }

    ~PointerQueue(){
        for (const auto &ptr = list.head; ptr != LIST_END; ){
            auto backup = ptr;
            ptr = ptr->getNext();
            delete backup;
        }
    }
};

#endif //QUEUE_QUEUE_H
