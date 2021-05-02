//
// Created by Bohdan on 03.04.2021.
//

template<typename K, typename D>
FibHeap<K, D>::FibHeap():
        Head(nullptr), n(0) {}


template<typename K, typename D>
void FibHeap<K, D>::Insert(FibNode<K, D> * newNode) {
    size_t new_n = pow(2, newNode->degree);
    if (Head == nullptr) {
        Head = newNode;
        n = pow(2, newNode->degree);
        return;
    }

    _insert_front_x(newNode, Head);

    if (Head->Key >= newNode->Key) {
        Head = newNode;
    }

    n += new_n;
}


template<typename K, typename D>
FibNode<K, D> *FibHeap<K, D>::GetMinimumNode() const {
    return Head;
}


template<typename K, typename D>
void FibHeap<K, D>::Union(FibHeap<K, D> *F1, FibHeap<K, D> *F2) {
    Head = nullptr;

    FibNode<K, D> * H1 = F1->Head;
    FibNode<K, D> * H2 = F2->Head;

    if (H1 && H2) {
        H2->prev->next = H1->next;
        H1->next->prev = H2->prev;
        H1->next = H2;
        H2->prev = H1;

        Head = (H1->Key > H2->Key)? H2 : H1;
        n    = F1->n + F2->n;
    } else if (H1) {
        Head = H1;
    } else {
        Head = H2;
    }

    F2->Head = F1->Head = nullptr;
}


template<typename K, typename D>
FibNode<K, D> *FibHeap<K, D>::ExtractMinimumNode() {
    FibNode<K, D> * minimum = Head;
    if (minimum) {
        FibNode<K, D> * leftChild     = minimum->child;

        if (leftChild) {
            FibNode<K, D> * tempLeftChild = leftChild;
            while (tempLeftChild->parent) {
                tempLeftChild->parent = nullptr;
                tempLeftChild = tempLeftChild->next;
            }
        }

        minimum->child = nullptr;
        if (leftChild) {
            auto * minNext = minimum->next;
            auto * leftPrev = leftChild->prev;
            minimum->next = leftChild;
            leftChild->prev = minimum;
            leftPrev->next = minNext;
            minNext->prev = leftPrev;
        }

        auto * temp = Head->next;
        _delete_node(minimum);

        n = n - 1;
        if (Head == temp) {
            Head = nullptr;
        } else {
            Head = temp;
            _consolidate();
        }


    }
    return minimum;
}


template<typename K, typename D>
void FibHeap<K, D>::_fib_link(FibNode<K, D> * y, FibNode<K, D> * x) {
    _delete_node(y);

    if (x->child) {
        _insert_front_x(y, x->child);
    } else {
        x->child = y;
        y->parent = x;
    }

    x->degree++;
    y->mark = false;
}


template<typename K, typename D>
void FibHeap<K, D>::_delete_node(FibNode<K, D> * d) {
    d->next->prev = d->prev;
    d->prev->next = d->next;
    d->next = d;
    d->prev = d;
}


template<typename K, typename D>
void FibHeap<K, D>::_insert_front_x(FibNode<K, D> * y, FibNode<K, D> * x) {
    y->next = x->next;
    x->next->prev = y;
    x->next = y;
    y->prev = x;
    //parent
    y->parent = x->parent;
}


template<typename K, typename D>
void FibHeap<K, D>::_consolidate() {
    std::vector<FibNode<K, D>*> DegreeTable(log2(n + 1) + 2, nullptr);

    FibNode<K, D> * temp  = Head;

    do {
        FibNode<K, D>*  x = temp;
        size_t          d = x->degree;

        while (DegreeTable[d] && DegreeTable[d] != x) {
            FibNode<K, D> * y = DegreeTable[d];
            if (x->Key > y->Key) {
                std::swap(x, y);
                temp = x;
            }
            _fib_link(y, x);
            if (Head == y) {
                Head = x;
            }
            DegreeTable[d] = nullptr;
            d = d + 1;
        }
        DegreeTable[d] = x;
//        x->parent = nullptr;

        temp = temp->next;
    } while (Head != temp);

    n    = 0;
    Head = nullptr;

    for (auto Node : DegreeTable) {
        if (Node) {
            Node->prev = Node->next = Node;
            Insert(Node);
            if (Head == nullptr || Node->Key < Head->Key) {
                Head = Node;
            }
        }
    }
}


template<typename K, typename D>
void FibHeap<K, D>::PrintHeap() const {
    if (Head) {
        Head->next->PrintNode(Head, "", Head == Head->next);
        std::cout << "\n";
    }
}

template<typename K, typename D>
FibHeap<K, D>::~FibHeap() {
    if (Head) {
        Head->prev->next = nullptr;
        delete Head;
    }
}


template<typename K, typename D>
void FibHeap<K, D>::DecreaseKey(FibNode<K, D> * x, const K & key) {
    if (key > x->Key) {
        std::cerr << "New key higher than the previous one";
        return;
    }
    x->Key = key;
    FibNode<K, D> * y = x->parent;
    if (y && x->Key <= y->Key) {
        _cut(x,y);
        _cascading_cut(y);
    }
    if (x->Key <= Head->Key) {
        Head = x;
    }
}


template<typename K, typename D>
void FibHeap<K, D>::_cut(FibNode<K, D> * x, FibNode<K, D> * y) {
    x->parent = nullptr;
    if (x == x->next) {
        y->child = nullptr;
    }
    else if (y->child == x) {
        y->child = x->next;
    }
    _delete_node(x);

    _insert_front_x(x, Head);
    if (Head->Key >= x->Key) {
        Head = x;
    }

    x->mark = false;
    y->degree--;
}


template<typename K, typename D>
void FibHeap<K, D>::_cascading_cut(FibNode<K, D> * y) {
    FibNode<K, D> * z = y->parent;
    if (z) {
        if (y->mark == false) {
            y->mark = true;
        } else {
            _cut(y, z);
            _cascading_cut(z);
        }
    }
}


template<typename K, typename D>
void FibHeap<K, D>::DeleteNode(FibNode<K, D> * x) {
    DecreaseKey(x, Head->Key);
    ExtractMinimumNode();
}