#pragma once

#include <iostream>
#include <iterator>
#include <memory>

#include "rb_tree.hpp"

template <class T, class Comparator = std::less<T>>
class set {
 public:
    class iterator : RBTree<T, Comparator>::iterator {
        friend class set<T, Comparator>;
        //   explicit iterator(RBNode<T> *ptr = nullptr);
        //   iterator(const iterator &);
        //   iterator &operator=(const iterator &);
    };

    set() : tree(), setSize(0) {}

    size_t size() const;
    bool empty() const;

    void insert(T value);
    void erase(T value);

 private:
    RBTree<T, Comparator> tree;
    size_t setSize;
};

template <class T, class Comparator>
size_t set<T, Comparator>::size() const {
    return setSize;
}

template <class T, class Comparator>
bool set<T, Comparator>::empty() const {
    return setSize == 0;
}

template <class T, class Comparator>
void set<T, Comparator>::insert(T value) {
    if (tree.insert(value)) {
        setSize++;
    }
}

template <class T, class Comparator>
void set<T, Comparator>::erase(T value) {
    if (tree.remove(value)) {
        setSize--;
    }
}
