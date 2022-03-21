/**
 * ArrayList implementation
 *
 * @author Mateusz Kruk
 * @version 1.0
 */

#ifndef POINTERLIST_H
#define POINTERLIST_H

#include <iostream>
#include <array>
#include <vector>

constexpr auto LIST_END = nullptr;


template <class T> class Node {
protected:
    T val;
public:
    virtual Node<T>* getPrev() = 0;
    virtual T getVal() = 0;
    virtual Node<T>* getNext() = 0;

    virtual void setPrev(Node<T>* p) = 0;
    virtual void setVal(T v) = 0;
    virtual void setNext(Node<T>* n) = 0;


};

template <class T> class OneWayNode : public Node<T> {
protected:
    Node<T>* next{};
public:
    OneWayNode(T v, Node<T>* next){
        this-> val = v;
        this-> next = next;
    }

    T getVal() {
        return this->val;
    }
    Node<T>* getNext() {
        return this->next;
    }

    Node<T>* getPrev(){
        return LIST_END;
    }

    void setVal(T v){
        this->val = v;
    }
    void setNext(Node<T>* n){
        this->next = n;
    }

    void setPrev(Node<T>* p){
           }

};

template <class T> class TwoWayNode : public Node<T>{
protected:
    Node<T>* next{};
    Node<T>* previous{};
public:
     TwoWayNode(T v,Node<T>* prev, Node<T>* next){
        this-> val = v;
        this-> next = next;
        this->previous =prev;
    }


    T getVal() {
        return this->val;
    }
    Node<T>* getNext() {
        return this->next;
    }

    Node<T>* getPrev(){
        return this->previous;
    }

    void setVal(T v){
        this->val = v;
    }
    void setNext(Node<T>* n){
        this->next = n;
    }

    void setPrev(Node<T>* p){
         this->previous = p;
    }

};

template <class T>
class PointerList{
protected:
    const static int removesNeeded{2};

    int elems{0};
public:
    Node<T>* head{LIST_END};

    /**
     * Adds an element to the beginning of the ArrayList
     *
     * @param e - element to add
     */
    virtual void add(T e) = 0;

    /**
     * Adds an element to the specified location on the ArrayList
     *
     * @param e - element to be added
     * @param i - position to add a new element
     */
    virtual void add(T e,int i) = 0;

    /**
     * Remove element from the ArrayList, if it's on a list
     *
     * @param e - element to remove
     */
    virtual void remove_e(T e) = 0;

    /**
     * Remove element on a specified location on the ArrayList, if it's on the list
     *
     * @param i - position of the element to remove
     */
    virtual void remove_i(int i) = 0;

    /**
     * Checks if ArrayList contains element e
     *
     * @param e - element that method is searching for
     * @return true if e element if found, otherwise false
     */
    virtual bool find(T e) = 0;

    /**
     * Sorts an ArrayList ascending
     */
    virtual void sort() = 0;

    virtual void print() = 0;

};


template <class T>
class OneWayPointerList : public PointerList<T>{

public:

    void add(T e){
           Node<T> *newNode = new OneWayNode<T>(e, this->head);
           this->head = newNode;
           this->elems++;
    }
    void add(T e,int i){
        if (i == 0) {add(e); return;}
        else if (i > this->elems) return;
        Node<T>* buf = this->head;
        for(int x = 1; x < i-1; x++){
            buf = buf->getNext();
        }
            Node<T>* newNode = new OneWayNode<T>(e, buf->getNext());
            buf -> setNext(newNode);
            this->elems++;
    }
    void remove_e(T e) {
        Node<T>* prev_Node = this->head;
        for(Node<T>* i = prev_Node->getNext(); i != LIST_END; i = i->getNext()){
            if(i->getVal() == e){
                prev_Node->setNext(i->getNext());
                this->elems--;
                delete i;
                break;
            }
            else
                prev_Node = i;
        }
    }
    void remove_i(int i){
        Node<T>* buf = this->head,
            *prev_Node;
        if (i > this->elems) return;
        for(int x = 0; x < i; x++){
            prev_Node = buf;
            buf = buf->getNext();
        }
        if (i == 0)
            this->head = buf->getNext();
        else
            prev_Node->setNext(buf->getNext());
        this->elems--;
        delete buf;
    }
    bool contains(T e) {
        Node<T>* currNode = this->head;
        while(currNode != LIST_END){
            if (currNode->getVal() == e)
                return true;
            else
                currNode = currNode->getNext();
        }
        return false;
    }
    void sort() {

        Node<T> *current = this->head, *index = nullptr;
        if (current == LIST_END) return;
        while (current != LIST_END){
            index = current->getNext();
            while(index != LIST_END){
                if (current->getVal() > index->getVal()){
                    swap_v(current,index);
                }
                index = index->getNext();
            }
            current = current->getNext();
        }

    }

    void swap_v(Node<T>* n1, Node<T>* n2){
        T val = n1->getVal();
        n1->setVal(n2->getVal());
        n2->setVal(val);
    }
    void print(){
        std::cout << std::endl;

        Node<T>* buf = this->head;
        while(buf != LIST_END){
            std::cout << buf->getVal() << " ";
            buf = buf->getNext();
        }
        std::cout << std::endl;
    }
};


template <class T> class TwoWayPointerList : public PointerList<T>{

    Node<T>*last{LIST_END};

public:

    void add(T e){
            Node<T>* newNode = new TwoWayNode<T>(e, LIST_END, this->head);
            if (this->elems > 0)
                this->head->setPrev(newNode);
            this->head = newNode;
            if (this->elems == 0)
                last = this->head;
            this->elems++;
    }
    void add(T e,int i){
        if (i == 0) {add(e); return;}
        else if (i > this->elems) return;
        Node<T>* buf = this->head;
        for(int x = 1; x < i-1; x++){
            buf = buf->getNext();
        }
            Node<T>* newNode = new TwoWayNode<T>(e,buf, buf->getNext());
            (buf->getNext())->setPrev(newNode);
            buf->setNext(newNode);
            this->elems++;
    }
    void remove_e(T e) {
        Node<T>* i = this->head;
        while(i != LIST_END){
            if(i->getVal() == e){
                Node<T>* prev_Node = i->getPrev(),
                    *next_Node = i->getNext();
                prev_Node->setNext(next_Node);
                next_Node->setPrev(prev_Node);
                this->elems--;
                delete i;
                break;
            }
        }
    }
    void remove_i(int i){
        Node<T>* buf = this->head;
        if (i > this->elems) return;
        for(int x = 1; x < i; x++){
            buf = buf->getNext();
        }
        if (i == 0)
            this->head = buf->getNext();
        else {
            Node<T>* prev_Node = buf->getPrev(),
                    *next_Node = buf->getNext();
            prev_Node->setNext(next_Node);
            next_Node->setPrev(prev_Node);
        }
        delete buf;
    }
    T removeLast(){
        Node<T> *prev = last->getPrev();
        T v = last->getVal();
        prev->getNext(LIST_END);
        delete last;
        last = prev;
        return v;
    }
    bool contains(T e) {
        Node<T>* i = this->head;
        while(i != this->head){
            if (i->getVal() == e)
                return true;
            else
                i = i->getNext();
        }
        return false;
    }
    void sort() {
        Node<T> *current = this->head, *index = nullptr;
        if (current == LIST_END) return;
        while (current != LIST_END){
            index = current->getNext();
            while(index != LIST_END){
                if (current->getVal() > index->getVal()){
                    swap_v(current,index);
                }
                index = index->getNext();
            }
            current = current->getNext();
        }
    }

    void print(){
        std::cout << std::endl;

        Node<T>* buf = this->last;
        while(buf != LIST_END){
            std::cout << buf->getVal() << " ";
            buf = buf->getPrev();
        }
        std::cout << std::endl;
    }

    void swap_v(Node<T>* n1, Node<T>* n2){
        T val = n1->getVal();
        n1->setVal(n2->getVal());
        n2->setVal(val);
    }

};

#endif