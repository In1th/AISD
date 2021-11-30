/**
 * ArrayList implementation
 *
 * @author Mateusz Kruk
 * @version 1.0
 */

#ifndef ARRAYLIST_H
#define ARRAYLIST_H

#include <iostream>
#include <array>
#include <vector>

#define NMAX 20
#define LIST_END -1
#define TO_OVERRIDE -2

template <class T> class Node {
protected:
    T val;
public:
    virtual int getPrev() = 0;
    virtual T getVal() = 0;
    virtual int getNext() = 0;

    virtual void setPrev(int p) = 0;
    virtual void setVal(T v) = 0;
    virtual void setNext(int n) = 0;

    //virtual void swap(Node<T> n1, Node<T> n2) = 0;

};

template <class T> class OneWayNode : public Node<T> {
protected:
    int next{};
public:
    OneWayNode(T v, int next){
        this-> val = v;
        this-> next = next;
    }

    T getVal() {
        return this->val;
    }
    int getNext() {
        return this->next;
    }

    int getPrev(){
        return LIST_END;
    }

    void setVal(T v){
        this->val = v;
    }
    void setNext(int n){
        this->next = n;
    }

    void setPrev(int p){
           }

};

template <class T> class TwoWayNode : public Node<T>{
protected:
        int next{};
        int previous{};
public:
     TwoWayNode(T v,int prev, int next){
        this-> val = v;
        this-> next = next;
        this->previous =prev;
    }


    T getVal() {
        return this->val;
    }
    int getNext() {
        return this->next;
    }

    int getPrev(){
        return this->previous;
    }

    void setVal(T v){
        this->val = v;
    }
    void setNext(int n){
        this->next = n;
    }

    void setPrev(int p){
         this->previous = p;
    }

};

template <class T> class ArrayList{
protected:
    const static int removesNeeded{2};

    int head{LIST_END};
    int freeIndex{0};
    int removeCount{0};
    int elems{0};
    public:

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
    virtual bool contains(T e) = 0;

    /**
     * Sorts an ArrayList ascending
     */
    virtual void sort() = 0;

    /**
     * Fills the gaps between nodes.
     *
     * This method is called when removes are equal to removeCount
     */
    virtual void repair() = 0;

    virtual void print() = 0;

};


template <class T> class OneWayArrayList : public ArrayList<T>{
protected:
    std::vector<OneWayNode<T>> arr;
public:

    /**
     * OneWayArrayList constructor
     *
     * initializes all ArrayList variables and a vector
     **/
    explicit OneWayArrayList(){
        for (int i = 0; i < NMAX; i++)
            this->arr.push_back(OneWayNode<T>(NULL,TO_OVERRIDE));
    }


    void add(T e){
        if (this->freeIndex < NMAX) {
           this->arr[this->freeIndex] = OneWayNode<T>(e, this->head);
           this->head = this-> freeIndex++;
            this->elems++;
        }
    }
    void add(T e,int i){
        if (i == 0) {add(e); return;}
        else if (i > this->elems) return;
        int buf = this->head;
        for(int x = 1; x < i-1; x++){
            buf = this->arr[buf].getNext();
        }
        if (this->freeIndex < NMAX) {
            this->arr[this->freeIndex] = OneWayNode<T>(e, this->arr[buf].getNext());
            this->arr[buf].setNext(this-> freeIndex++);
            this->elems++;

        }
    }
    void remove_e(T e) {
        int prev_Node = this->head;
        for(int i = this->arr[prev_Node].getNext(); i != LIST_END; i = this->arr[i].getNext()){
            if(this->arr[i].getVal() == e){
                this->arr[prev_Node].setNext(this->arr[i].getNext());
                this->arr[i].setNext(TO_OVERRIDE);
                this->removeCount++;
                this->elems--;
                if (this->removeCount == ArrayList<T>::removesNeeded)
                    this->repair();
                break;
            }
            else
                prev_Node = i;
        }
    }
    void remove_i(int i){
        int buf = this->head,
            prev_Node;
        if (i > this->elems) return;
        for(int x = 0; x < i; x++){
            prev_Node = buf;
            buf = this->arr[buf].getNext();
        }
        if (i == 0)
            this->head = this->arr[buf].getNext();
        else
            this->arr[prev_Node].setNext(this->arr[buf].getNext());
        this->arr[buf].setNext(TO_OVERRIDE);
        this->removeCount++;
        this->elems--;
        if (this->removeCount == ArrayList<T>::removesNeeded)
            this->repair();
    }
    bool contains(T e) {
        for(int i = 0; i < this->freeIndex; i++){
            if (this->arr[i].getVal() == e){
                return true;
            }
        }
        return false;
    }
    void sort() {
        int left, right;
        for (int i = 0; i < this->elems - 1; i++){
            left = this->head;
            for (int j = 0; j < this->elems-i-1; j++){
                right = this->arr[left].getNext();
                if (this->arr[left].getVal() > this->arr[right].getVal())
                    swap_v(left,right);
                left = right;
            }
        }

    }
    void repair() {
        this->removeCount = 0;
        for (int i = 0; i < this->freeIndex; i++){
            while(this->arr[i].getNext() == TO_OVERRIDE){
                if (i != this->freeIndex) swap(i,--this->freeIndex);
                this->arr[this->freeIndex] = OneWayNode<T>(0,TO_OVERRIDE);
            }
        }
    }
    void swap(int n1, int n2){
        for(int i = 0; i < this->arr.size(); i++){
            if (this->arr[i].getNext() == n2)
                this->arr[i].setNext(n1);
        }
        OneWayNode<T> buf = this->arr[n1];
        this->arr[n1] = this->arr[n2];
        this->arr[n2] = buf;
        if (this->head == n2)
            this->head = n1;
    }
    void swap_v(int n1, int n2){
        T val = this->arr[n1].getVal();
        this->arr[n1].setVal(this->arr[n2].getVal());
        this->arr[n2].setVal(val);
    }
    void print(){
        std::cout << std::endl;

        printf("%2s %6s %5s\n","ID","value","next");
        for(int i = 0; i < NMAX; i++){
            OneWayNode<T> n = this->arr[i];
            if (i == this->head) printf("\033[31m%2d\033[0m %6d %5d     ",i,n.getVal(),n.getNext());
            else printf("%2d %6d %5d     ",i,n.getVal(),n.getNext());
            switch (i) {
                case 1: std::cout << "Wpisz:"; break;
                case 2: std::cout << "1 - add(e)"; break;
                case 3: std::cout << "2 - add(e,i)"; break;
                case 4: std::cout << "3 - remove(e)"; break;
                case 5: std::cout << "4 - remove(i)"; break;
                case 6: std::cout << "5 - contains(e)"; break;
                case 7: std::cout << "6 - sort()"; break;
                case 8: std::cout << "7 - wyjdź"; break;
                case 10: std::cout << "liczba elementów: "<<this->elems; break;
                case 11: std::cout << "Liczba usunięć do koretky: "<<ArrayList<T>::removesNeeded - this->removeCount; break;
                case 12: std::cout << "Wolny indeks: "<<this->freeIndex; break;
            }
            std::cout << std::endl;
        }
    }
};


template <class T> class TwoWayArrayList : public ArrayList<T>{
protected:
    std::vector<TwoWayNode<T>> arr;
public:
    explicit TwoWayArrayList(){
        for (int i = 0; i < NMAX; i++){
            this->arr.push_back(TwoWayNode<T>(NULL,TO_OVERRIDE,TO_OVERRIDE));
        }
    }

    void add(T e){
        if (this->freeIndex < NMAX) {
            if (this->elems > 0)
                this->arr[this->head].setPrev(this->freeIndex);
            this->arr[this->freeIndex] = TwoWayNode<T>(e, LIST_END, this->head);
            this->head = this-> freeIndex++;
            this->elems++;
        }
    }
    void add(T e,int i){
        if (i == 0) {add(e); return;}
        else if (i > this->elems) return;
        int buf = this->head;
        for(int x = 1; x < i-1; x++){
            buf = this->arr[buf].getNext();
        }
        if (this->freeIndex < NMAX) {
            this->arr[this->freeIndex] = TwoWayNode<T>(e,buf, this->arr[buf].getNext());
            this->arr[this->arr[buf].getNext()].setPrev(this->freeIndex);
            this->arr[buf].setNext(this-> freeIndex++);
            this->elems++;
        }
    }
    void remove_e(T e) {
        for(int i = this->head; i != LIST_END; i = this->arr[i].getNext()){
            if(this->arr[i].getVal() == e){
                int prev_Node = this->arr[i].getPrev(),
                    next_Node = this->arr[i].getNext();
                this->arr[prev_Node].setNext(next_Node);
                this->arr[next_Node].setPrev(prev_Node);
                this->arr[i].setNext(TO_OVERRIDE);
                this->removeCount++;
                this->elems--;
                if (this->removeCount == ArrayList<T>::removesNeeded)
                    this->repair();
                break;
            }
        }
    }
    void remove_i(int i){
        int buf = this->head;
        if (i > this->elems) return;
        for(int x = 1; x < i; x++){
            buf = this->arr[buf].getNext();
        }
        if (i == 0)
            this->head = this->arr[buf].getNext();
        else {
            int prev_Node = this->arr[buf].getPrev(),
                    next_Node = this->arr[buf].getNext();
            this->arr[prev_Node].setNext(next_Node);
            this->arr[next_Node].setPrev(prev_Node);
        }
        this->arr[buf].setNext(TO_OVERRIDE);
        this->elems--;
        this->removeCount++;
        if (this->removeCount == ArrayList<T>::removesNeeded)
            this->repair();
    }
    bool contains(T e) {
        for(int i = 0; i < this->freeIndex; i++){
            if (this->arr[i].getVal() == e){
                return true;
            }
        }
        return false;
    }
    void sort() {
        int left, right;
        for (int i = 0; i < this->elems - 1; i++){
            left = this->head;
            for (int j = 0; j < this->elems-i-1; j++){
                right = this->arr[left].getNext();
                if (this->arr[left].getVal() > this->arr[right].getVal())
                    swap_v(left,right);
                left = right;
            }
        }
    }
    void repair() {
        this->removeCount = 0;
        for (int i = 0; i < this->freeIndex; i++){
            while(this->arr[i].getNext() == TO_OVERRIDE){
                if (i != this->freeIndex) swap(i,--this->freeIndex);
                this->arr[this->freeIndex] = TwoWayNode<T>(0,TO_OVERRIDE,TO_OVERRIDE);
            }
        }
    }
    void print(){
        std::cout << std::endl;

        printf("%2s %6s %5s %5s\n","ID","value","prev","next");
        for(int i = 0; i < NMAX; i++){
            TwoWayNode<T> n = this->arr[i];
            if (i == this->head) printf("\033[31m%2d\033[0m %6d %5d %5d     ",i,n.getVal(),n.getPrev(),n.getNext());
            else printf("%2d %6d %5d %5d     ",i,n.getVal(),n.getPrev(),n.getNext());
            switch (i) {
                case 1: std::cout << "Wpisz:"; break;
                case 2: std::cout << "1 - add(e)"; break;
                case 3: std::cout << "2 - add(e,i)"; break;
                case 4: std::cout << "3 - remove(e)"; break;
                case 5: std::cout << "4 - remove(i)"; break;
                case 6: std::cout << "5 - contains(e)"; break;
                case 7: std::cout << "6 - sort()"; break;
                case 8: std::cout << "7 - wyjdź"; break;
                case 10: std::cout << "liczba elementów: "<<this->elems; break;
                case 11: std::cout << "Liczba usunięć do koretky: "<<ArrayList<T>::removesNeeded - this->removeCount; break;
            }
            std::cout << std::endl;
        }
    }
    void swap(int n1, int n2){
         int bef_n2 = this->arr[n2].getPrev(),
             aft_n2 = this->arr[n2].getNext();

         this->arr[bef_n2].setNext(n1);
         this->arr[aft_n2].setPrev(n1);
        TwoWayNode<T> buf = this->arr[n1];
        this->arr[n1] = this->arr[n2];
        this->arr[n2] = buf;
        if (this->head == n2)
            this->head = n1;
    }
    void swap_v(int n1, int n2){
        T val = this->arr[n1].getVal();
        this->arr[n1].setVal(this->arr[n2].getVal());
        this->arr[n2].setVal(val);
    }

};

#endif