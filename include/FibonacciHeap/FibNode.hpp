//
// Created by Bohdan on 03.04.2021.
//

#pragma once

#include <cstdio>
#include <vector>
#include <cmath>
#include <string>
#include <iostream>

template <typename K, typename D>
class FibHeap;

template <typename K, typename D>
class FibNode {
public:
    explicit FibNode(const K & key = K(), const D & data = D());
    ~FibNode();

    void PrintNode (FibNode<K, D> * start, const std::string & prefix = "", bool isLast = false) const;
    inline K GetKey() const { return Key; }
    inline D GetData() const { return Data; }

private:
    FibNode * parent;
    FibNode * child;

    FibNode * prev;
    FibNode * next;

    size_t    degree;
    K         Key;
    D         Data;
    bool      mark;

    friend class FibHeap<K, D>;
};

#include "FibNode.inl"