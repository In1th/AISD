//
// Created by kruk on 29/12/2021.
//

#ifndef TREE_H
#define TREE_H


template <class T> class BinNode{
public:
    typedef BinNode<T>* node_ptr;

    T val;
    node_ptr left{nullptr};
    node_ptr right{nullptr};
    int height{1};


    BinNode() = default;
    explicit BinNode(T val);
    constexpr int numberOfChildren() noexcept;

};

template <class T> class BinTree{

protected:
    typename BinNode<T>::node_ptr root{nullptr};
    bool removed{};
    BinNode<T>* minValNode(BinNode<T>* node) noexcept;

    virtual BinNode<T> *insideInsert(T val, BinNode<T> *node) noexcept;

    virtual BinNode<T> *insideRemove(T val, BinNode<T> *node) noexcept;
public:

    BinTree();
    BinNode<T>* find(T val);
    int getHeight(BinNode<T>* node) noexcept;

};

template <class T> class BSTTree :public BinTree<T>{
    BinNode<T> *insideInsert(T val, BinNode<T> *node) noexcept override;
    BinNode<T> *insideRemove(T val, BinNode<T> *node) noexcept override;
public:

    BSTTree();

    void insert(T val) noexcept;
    bool remove(T val) noexcept;
};


template <class T> class AVLTree : public BinTree<T>{
protected:
    constexpr int getWeight(BinNode<T> *node) noexcept;
    BinNode<T>* correct(BinNode<T>* start, T value) noexcept;
    BinNode<T>* lrotate(BinNode<T>* node) noexcept;
    BinNode<T>* rrotate(BinNode<T>* node) noexcept;
    BinNode<T>* insideInsert(T val, BinNode<T>* node) noexcept override;
    BinNode<T>* insideRemove(T val, BinNode<T> *node) noexcept override;
public:
    AVLTree();
    void insert(T val) noexcept;
    bool remove(T val) noexcept;
};

#include "Tree.tpp"

#endif