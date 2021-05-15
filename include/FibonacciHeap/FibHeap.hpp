//
// Created by Bohdan on 03.04.2021.
//

#pragma once

#include "FibNode.hpp"

template <typename K, typename D>
class FibHeap {
public:
    FibHeap();
    ~FibHeap();

    void PrintHeap() const;
    void Insert(FibNode<K, D>*);
    void Union(FibHeap<K, D>*, FibHeap<K, D>*);
    void DecreaseKey(FibNode<K, D>*, const K & key);
    void DeleteNode(FibNode<K, D>*);
    FibNode<K, D> * GetMinimumNode() const;
    FibNode<K, D> * ExtractMinimumNode();
    bool isEmpty() {return Head == nullptr;}

private:
    void _fib_link(FibNode<K, D>*, FibNode<K, D>*);
    void _delete_node(FibNode<K, D>*);
    void _insert_front_x(FibNode<K, D>*, FibNode<K, D>*);
    void _consolidate();
    void _cut(FibNode<K, D>*, FibNode<K, D>*);
    void _cascading_cut(FibNode<K, D>*);

private:
    FibNode<K, D> * Head;
};

#include "FibHeap.inl"