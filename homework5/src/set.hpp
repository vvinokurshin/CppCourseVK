#pragma once

#include <iostream>
#include <iterator>
#include <memory>

#include "rb_tree.hpp"

template <class T, class Comparator = std::less<T>>
class set {
 public:
    class iterator {
     public:
        friend class set<T, Comparator>;
        using difference_type = ptrdiff_t;
        using value_type = T;
        using reference = const T &;
        using pointer = const T *;
        using iterator_category = std::bidirectional_iterator_tag;

        explicit iterator(RBNode<T> *ptr = nullptr);
        iterator(const iterator &);
        iterator &operator=(const iterator &);

        iterator &operator++();
        iterator operator++(int);
        reference operator*() const;
        pointer operator->() const;
        iterator &operator--();
        iterator operator--(int);

        bool operator==(iterator other) const;
        bool operator!=(iterator other) const;

     private:
        typename RBTree<T, Comparator>::iterator it;
    };

    class const_iterator {
     public:
        friend class set<T, Comparator>;
        using difference_type = ptrdiff_t;
        using value_type = T;
        using reference = const T &;
        using pointer = const T *;
        using iterator_category = std::bidirectional_iterator_tag;

        explicit const_iterator(RBNode<T> *ptr = nullptr);
        const_iterator(const const_iterator &);
        const_iterator &operator=(const const_iterator &);

        const_iterator &operator++() const;
        const_iterator operator++(int) const;
        reference operator*() const;
        pointer operator->() const;
        const_iterator &operator--() const;
        const_iterator operator--(int) const;

        bool operator==(const_iterator other) const;
        bool operator!=(const_iterator other) const;

     private:
        typename RBTree<T, Comparator>::const_iterator it;
    };

    using reverse_iterator = std::reverse_iterator<iterator>;
    using const_reverse_iterator = std::reverse_iterator<const_iterator>;

    Comparator cmp;

    set();
    template <class Iter>
    set(Iter ibegin, Iter iend);
    explicit set(std::initializer_list<T> list);
    set(const set &other);
    // ~set() = default;

    set &operator=(const set &);

    void insert(T value);
    void erase(T value);

    size_t size() const;
    bool empty() const;

    iterator find(const T value) const;
    iterator lower_bound(const T value) const;

    iterator begin() const;
    iterator end() const;
    const_iterator cbegin() const;
    const_iterator cend() const;

    reverse_iterator rbegin() const;
    reverse_iterator rend() const;
    const_reverse_iterator crbegin() const;
    const_reverse_iterator crend() const;

 private:
    RBTree<T, Comparator> tree;
    size_t setSize;
};

template <class T, class Comparator>
set<T, Comparator>::iterator::iterator(RBNode<T> *ptr) : it{ptr} {}

template <class T, class Comparator>
set<T, Comparator>::iterator::iterator(const iterator &other) : it{other.it} {}

template <class T, class Comparator>
typename set<T, Comparator>::iterator &set<T, Comparator>::iterator::operator=(const iterator &other) {
    it = other.it;
    return *this;
}

template <class T, class Comparator>
typename set<T, Comparator>::iterator &set<T, Comparator>::iterator::operator++() {
    ++it;
    return *this;
}

template <class T, class Comparator>
typename set<T, Comparator>::iterator set<T, Comparator>::iterator::operator++(int) {
    ++it;
    return *this;
}

template <class T, class Comparator>
typename set<T, Comparator>::iterator::reference set<T, Comparator>::iterator::operator*() const {
    return *it;
}

template <class T, class Comparator>
typename set<T, Comparator>::iterator::pointer set<T, Comparator>::iterator::operator->() const {
    return it;
}

template <class T, class Comparator>
typename set<T, Comparator>::iterator &set<T, Comparator>::iterator::operator--() {
    --it;
    return *this;
}

template <class T, class Comparator>
typename set<T, Comparator>::iterator set<T, Comparator>::iterator::operator--(int) {
    --it;
    return *this;
}

template <class T, class Comparator>
bool set<T, Comparator>::iterator::operator==(iterator other) const {
    return it == other.it;
}

template <class T, class Comparator>
bool set<T, Comparator>::iterator::operator!=(iterator other) const {
    return it != other.it;
}

template <class T, class Comparator>
set<T, Comparator>::const_iterator::const_iterator(RBNode<T> *ptr) : it{ptr} {}

template <class T, class Comparator>
set<T, Comparator>::const_iterator::const_iterator(const const_iterator &other) : it{other.it} {}

template <class T, class Comparator>
typename set<T, Comparator>::const_iterator &
set<T, Comparator>::const_iterator::operator=(const const_iterator &other) {
    it = other.it;
    return *this;
}

template <class T, class Comparator>
typename set<T, Comparator>::const_iterator &set<T, Comparator>::const_iterator::operator++() const {
    ++it;
    return *this;
}

template <class T, class Comparator>
typename set<T, Comparator>::const_iterator set<T, Comparator>::const_iterator::operator++(int) const {
    ++it;
    return *this;
}

template <class T, class Comparator>
typename set<T, Comparator>::const_iterator::reference set<T, Comparator>::const_iterator::operator*() const {
    return *it;
}

template <class T, class Comparator>
typename set<T, Comparator>::const_iterator::pointer set<T, Comparator>::const_iterator::operator->() const {
    return it;
}

template <class T, class Comparator>
typename set<T, Comparator>::const_iterator &set<T, Comparator>::const_iterator::operator--() const {
    --it;
    return *this;
}

template <class T, class Comparator>
typename set<T, Comparator>::const_iterator set<T, Comparator>::const_iterator::operator--(int) const {
    --it;
    return *this;
}

template <class T, class Comparator>
bool set<T, Comparator>::const_iterator::operator==(const_iterator other) const {
    return it == other.it;
}

template <class T, class Comparator>
bool set<T, Comparator>::const_iterator::operator!=(const_iterator other) const {
    return it != other.it;
}

template <class T, class Comparator>
typename set<T, Comparator>::iterator set<T, Comparator>::begin() const {
    return iterator(tree.getMin());
}

template <class T, class Comparator>
typename set<T, Comparator>::iterator set<T, Comparator>::end() const {
    return iterator(tree.getLast());
}

template <class T, class Comparator>
typename set<T, Comparator>::const_iterator set<T, Comparator>::cbegin() const {
    return const_iterator(tree.getMin());
}

template <class T, class Comparator>
typename set<T, Comparator>::const_iterator set<T, Comparator>::cend() const {
    return const_iterator(tree.getLast());
}

template <class T, class Comparator>
typename set<T, Comparator>::reverse_iterator set<T, Comparator>::rbegin() const {
    return reverse_iterator(end());
}

template <class T, class Comparator>
typename set<T, Comparator>::reverse_iterator set<T, Comparator>::rend() const {
    return reverse_iterator(begin());
}

template <class T, class Comparator>
typename set<T, Comparator>::const_reverse_iterator set<T, Comparator>::crbegin() const {
    return const_reverse_iterator(cend());
}

template <class T, class Comparator>
typename set<T, Comparator>::const_reverse_iterator set<T, Comparator>::crend() const {
    return const_reverse_iterator(cbegin());
}

template <class T, class Comparator>
set<T, Comparator>::set() : tree(), setSize(0) {}

template <class T, class Comparator>
template <class Iter>
set<T, Comparator>::set(Iter ibegin, Iter iend) : setSize(0) {
    for (auto it = ibegin; it != iend; it++) {
        insert(*it);
    }
}

template <class T, class Comparator>
set<T, Comparator>::set(std::initializer_list<T> list) : tree(list), setSize(list.size()) {}

template <class T, class Comparator>
set<T, Comparator>::set(const set &other) : cmp(other.cmp), tree(other.tree), setSize(other.setSize) {}

template <class T, class Comparator>
set<T, Comparator> &set<T, Comparator>::operator=(const set &other) {
    if (this != &other) {
        tree.~RBTree();
        cmp = other.cmp;
        setSize = other.setSize;
        tree = other.tree;
    }

    return *this;
}

template <class T, class Comparator>
void set<T, Comparator>::insert(T value) {
    if (tree.insert(value)) {
        ++setSize;
    }
}

template <class T, class Comparator>
void set<T, Comparator>::erase(T value) {
    if (tree.remove(value)) {
        --setSize;
    }
}

template <class T, class Comparator>
size_t set<T, Comparator>::size() const {
    return setSize;
}

template <class T, class Comparator>
bool set<T, Comparator>::empty() const {
    return setSize == 0;
}

template <class T, class Comparator>
typename set<T, Comparator>::iterator set<T, Comparator>::find(const T value) const {
    RBNode<T> *node = tree.search(value);

    if (node) {
        return iterator(tree.search(value));
    }

    return end();
}

template <class T, class Comparator>
typename set<T, Comparator>::iterator set<T, Comparator>::lower_bound(const T value) const {
    if (!empty()) {
        for (auto it = begin(); it != end(); ++it) {
            if (!cmp(*it, value)) {
                return it;
            }
        }
    }

    return end();
}
