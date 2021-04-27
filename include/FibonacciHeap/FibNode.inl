//
// Created by Bohdan on 03.04.2021.
//

template<typename K, typename D>
FibNode<K, D>::FibNode(const K & key, const D & data):
        Key(key), Data(data), degree(0), parent(nullptr), child(nullptr),
        prev(this), next(this), mark(false) {}



template<typename K, typename D>
void FibNode<K, D>::PrintNode(FibNode<K, D> * start, const std::string & prefix, bool isLast) const {
    std::cout << prefix;
    std::cout << (isLast ? "└──" : "├──");
    //custom data output
    std::cout << Key
              << std::endl;
    //child
    if (child) {
        child->next->PrintNode(child, prefix + (isLast? "    " : "│   "), child == child->next);
    }

    //isLast??
    if (isLast) {
        return;
    }

    //next
    next->PrintNode(start, prefix, next == start);
}

template<typename K, typename D>
FibNode<K, D>::~FibNode() {
    if (child) {
        child->prev->next = nullptr;
    }
    delete child;
    delete next;
}