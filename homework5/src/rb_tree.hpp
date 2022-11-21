#pragma once

#include <iostream>
#include <iterator>
#include <memory>

enum Color { Black, Red };

template <class T>
struct RBNode {
    RBNode(T value, Color clr, RBNode *l, RBNode *r, RBNode *p)
        : data(value), color(clr), left(l), right(r), parent(p) {}
    T data;
    Color color;
    RBNode *left;
    RBNode *right;
    RBNode *parent;
};

template <class T, class Comparator = std::less<T>>
class RBTree {
 public:
    class iterator {
     public:
        friend class RBTree<T, Comparator>;
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
        RBNode<T> *cur;
    };

    class const_iterator {
     public:
        friend class RBTree<T, Comparator>;
        using difference_type = ptrdiff_t;
        using value_type = T;
        using reference = const T &;
        using pointer = const T *;
        using iterator_category = std::bidirectional_iterator_tag;

        explicit const_iterator(RBNode<T> *ptr = nullptr);
        const_iterator(const const_iterator &);
        explicit const_iterator(const iterator &);
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
        RBNode<T> *cur;
    };

    using reverse_iterator = std::reverse_iterator<iterator>;
    using const_reverse_iterator = std::reverse_iterator<const_iterator>;

    Comparator cmp;

    RBTree();
    explicit RBTree(std::initializer_list<T> list);
    RBTree(const RBTree &other);
    ~RBTree();

    RBTree &operator=(const RBTree &);

    iterator begin() const;
    iterator end() const;
    const_iterator cbegin() const;
    const_iterator cend() const;

    reverse_iterator rbegin() const;
    reverse_iterator rend() const;
    const_reverse_iterator crbegin() const;
    const_reverse_iterator crend() const;

    bool insert(T value);
    bool remove(T value);
    RBNode<T> *search(T value) const;

    void print();

    RBNode<T> *getMin() const;
    RBNode<T> *getMax() const;
    RBNode<T> *getLast() const;

 private:
    RBNode<T> *root;
    RBNode<T> *super_root;

    RBNode<T> *copy(const RBNode<T> *other, RBNode<T> *parent);

    void leftRotate(RBNode<T> *x);
    void rightRotate(RBNode<T> *y);

    bool insert(RBNode<T> *node);
    void InsertFixUp(RBNode<T> *node);
    void remove(RBNode<T> *node);
    void removeFixUp(RBNode<T> *node, RBNode<T> *parent);

    RBNode<T> *search(RBNode<T> *node, T value) const;
    void print(RBNode<T> *node) const;

    void destory(RBNode<T> *node);
};

template <class T, class Comparator>
RBTree<T, Comparator>::iterator::iterator(RBNode<T> *ptr) : cur{ptr} {}

template <class T, class Comparator>
RBTree<T, Comparator>::iterator::iterator(const iterator &other) : cur{other.cur} {}

template <class T, class Comparator>
typename RBTree<T, Comparator>::iterator &RBTree<T, Comparator>::iterator::operator=(const iterator &other) {
    cur = other.cur;
    return *this;
}

template <class T, class Comparator>
typename RBTree<T, Comparator>::iterator &RBTree<T, Comparator>::iterator::operator++() {
    if (cur->right) {
        cur = cur->right;

        while (cur->left) {
            cur = cur->left;
        }
    } else {
        RBNode<T> *parent = cur->parent;

        while (cur == parent->right) {
            cur = parent;
            parent = parent->parent;
        }

        if (cur->right != parent) {
            cur = parent;
        }
    }

    return *this;
}

template <class T, class Comparator>
typename RBTree<T, Comparator>::iterator RBTree<T, Comparator>::iterator::operator++(int) {
    RBNode<T> *tmp = cur;
    iterator it(tmp);
    ++(*this);

    return it;
}

template <class T, class Comparator>
typename RBTree<T, Comparator>::iterator &RBTree<T, Comparator>::iterator::operator--() {
    if (cur->left) {
        cur = cur->left;

        while (cur->right) {
            cur = cur->right;
        }
    } else {
        RBNode<T> *parent = cur->parent;

        while (cur == parent->left) {
            cur = parent;
            parent = parent->parent;
        }

        if (cur->left != parent) {
            cur = parent;
        }
    }

    return *this;
}

template <class T, class Comparator>
typename RBTree<T, Comparator>::iterator RBTree<T, Comparator>::iterator::operator--(int) {
    RBNode<T> *tmp = cur;
    iterator it(tmp);
    --(*this);

    return it;
}

template <class T, class Comparator>
typename RBTree<T, Comparator>::iterator::reference RBTree<T, Comparator>::iterator::operator*() const {
    return cur->data;
}

template <class T, class Comparator>
typename RBTree<T, Comparator>::iterator::pointer RBTree<T, Comparator>::iterator::operator->() const {
    return &cur->data;
}

template <class T, class Comparator>
bool RBTree<T, Comparator>::iterator::operator==(iterator other) const {
    return other.cur == cur;
}

template <class T, class Comparator>
bool RBTree<T, Comparator>::iterator::operator!=(iterator other) const {
    return other.cur != cur;
}

template <class T, class Comparator>
RBTree<T, Comparator>::const_iterator::const_iterator(RBNode<T> *ptr) : cur{ptr} {}

template <class T, class Comparator>
RBTree<T, Comparator>::const_iterator::const_iterator(const const_iterator &other) : cur{other.cur} {}

template <class T, class Comparator>
RBTree<T, Comparator>::const_iterator::const_iterator(const iterator &other) : cur{other.cur} {}

template <class T, class Comparator>
typename RBTree<T, Comparator>::const_iterator &
RBTree<T, Comparator>::const_iterator::operator=(const const_iterator &other) {
    cur = other.cur;
    return *this;
}

template <class T, class Comparator>
typename RBTree<T, Comparator>::const_iterator &RBTree<T, Comparator>::const_iterator::operator++() const {
    if (cur->left) {
        cur = cur->right;

        while (cur->left) {
            cur = cur->left;
        }
    } else {
        RBNode<T> *parent = cur->parent;

        while (cur == parent->right) {
            cur = parent;
            parent = parent->parent;
        }

        if (cur->right != parent) {
            cur = parent;
        }
    }

    return *this;
}

template <class T, class Comparator>
typename RBTree<T, Comparator>::const_iterator RBTree<T, Comparator>::const_iterator::operator++(int) const {
    RBNode<T> *tmp = cur;
    const_iterator it(tmp);
    ++(*this);

    return it;
}

template <class T, class Comparator>
typename RBTree<T, Comparator>::const_iterator &RBTree<T, Comparator>::const_iterator::operator--() const {
    if (cur->left) {
        cur = cur->left;

        while (cur->right) {
            cur = cur->right;
        }
    } else {
        RBNode<T> *parent = cur->parent;

        while (cur == parent->left) {
            cur = parent;
            parent = parent->parent;
        }

        if (cur->left != parent) {
            cur = parent;
        }
    }

    return *this;
}

template <class T, class Comparator>
typename RBTree<T, Comparator>::const_iterator RBTree<T, Comparator>::const_iterator::operator--(int) const {
    RBNode<T> *tmp = cur;
    const_iterator it(tmp);
    --(*this);

    return it;
}

template <class T, class Comparator>
typename RBTree<T, Comparator>::const_iterator::reference
RBTree<T, Comparator>::const_iterator::operator*() const {
    return cur->data;
}

template <class T, class Comparator>
typename RBTree<T, Comparator>::const_iterator::pointer
RBTree<T, Comparator>::const_iterator::operator->() const {
    return &cur->data;
}

template <class T, class Comparator>
bool RBTree<T, Comparator>::const_iterator::operator==(const_iterator other) const {
    return other.cur == cur;
}

template <class T, class Comparator>
bool RBTree<T, Comparator>::const_iterator::operator!=(const_iterator other) const {
    return other.cur != cur;
}

template <class T, class Comparator>
typename RBTree<T, Comparator>::iterator RBTree<T, Comparator>::begin() const {
    return iterator(getMin());
}

template <class T, class Comparator>
typename RBTree<T, Comparator>::iterator RBTree<T, Comparator>::end() const {
    return iterator(getLast());
}

template <class T, class Comparator>
typename RBTree<T, Comparator>::const_iterator RBTree<T, Comparator>::cbegin() const {
    return const_iterator(getMin());
}

template <class T, class Comparator>
typename RBTree<T, Comparator>::const_iterator RBTree<T, Comparator>::cend() const {
    return const_iterator(super_root);
}

template <class T, class Comparator>
typename RBTree<T, Comparator>::reverse_iterator RBTree<T, Comparator>::rbegin() const {
    return reverse_iterator(end());
}

template <class T, class Comparator>
typename RBTree<T, Comparator>::reverse_iterator RBTree<T, Comparator>::rend() const {
    return reverse_iterator(begin());
}

template <class T, class Comparator>
typename RBTree<T, Comparator>::const_reverse_iterator RBTree<T, Comparator>::crbegin() const {
    return const_reverse_iterator(cend());
}

template <class T, class Comparator>
typename RBTree<T, Comparator>::const_reverse_iterator RBTree<T, Comparator>::crend() const {
    return const_reverse_iterator(cbegin());
}

template <class T, class Comparator>
RBTree<T, Comparator>::RBTree() : root(0), super_root(0) {}

template <class T, class Comparator>
RBTree<T, Comparator>::RBTree(std::initializer_list<T> list) : root(0), super_root(0) {
    for (auto element : list) {
        insert(element);
    }
}

template <class T, class Comparator>
RBTree<T, Comparator> &RBTree<T, Comparator>::operator=(const RBTree &other) {
    if (this != &other) {
        cmp = other.cmp;
        super_root = new RBNode<T>(0, Black, nullptr, nullptr, nullptr);
        root = copy(other.root, super_root);
        super_root->left = root;
    }

    return *this;
}

template <class T, class Comparator>
RBTree<T, Comparator>::RBTree(const RBTree &other) : cmp(other.cmp) {
    super_root = new RBNode<T>(0, Black, nullptr, nullptr, nullptr);
    root = copy(other.root, super_root);
    super_root->left = root;
}

template <class T, class Comparator>
RBNode<T> *RBTree<T, Comparator>::copy(const RBNode<T> *other, RBNode<T> *parent) {
    if (!other) {
        return nullptr;
    }

    RBNode<T> *node = new RBNode<T>(other->data, other->color, nullptr, nullptr, parent);

    node->left = copy(other->left, node);
    node->right = copy(other->right, node);

    return node;
}

template <class T, class Comparator>
RBTree<T, Comparator>::~RBTree() {
    destory(super_root);
}

template <class T, class Comparator>
RBNode<T> *RBTree<T, Comparator>::search(T value) const {
    return search(root, value);
}

template <class T, class Comparator>
RBNode<T> *RBTree<T, Comparator>::search(RBNode<T> *node, T value) const {
    if (node == nullptr || node->data == value) {
        return node;
    }

    if (cmp(value, node->data)) {
        return search(node->left, value);
    }

    return search(node->right, value);
}

template <class T, class Comparator>
void RBTree<T, Comparator>::leftRotate(RBNode<T> *x) {
    RBNode<T> *y = x->right;
    x->right = y->left;

    if (y->left) {
        y->left->parent = x;
    }

    y->parent = x->parent;

    if (x->parent == super_root) {
        root = y;
        super_root->left = root;

    } else {
        if (x == x->parent->left) {
            x->parent->left = y;
        } else {
            x->parent->right = y;
        }
    }

    y->left = x;
    x->parent = y;
}

template <class T, class Comparator>
void RBTree<T, Comparator>::rightRotate(RBNode<T> *y) {
    RBNode<T> *x = y->left;
    y->left = x->right;

    if (x->right) {
        x->right->parent = y;
    }

    x->parent = y->parent;

    if (y->parent == super_root) {
        root = x;
        super_root->left = root;

    } else {
        if (y == y->parent->right) {
            y->parent->right = x;
        } else {
            y->parent->left = x;
        }
    }

    x->right = y;
    y->parent = x;
}

template <class T, class Comparator>
bool RBTree<T, Comparator>::insert(T value) {
    RBNode<T> *node = new RBNode<T>(value, Red, nullptr, nullptr, nullptr);

    if (!root) {
        super_root = new RBNode<T>(0, Black, node, nullptr, nullptr);
        node->parent = super_root;
    }

    return insert(node);
}

template <class T, class Comparator>
bool RBTree<T, Comparator>::insert(RBNode<T> *node) {
    RBNode<T> *cur = root;
    RBNode<T> *parent = nullptr;

    while (cur) {
        parent = cur;

        if (!cmp(node->data, cur->data) && !cmp(cur->data, node->data)) {
            delete node;
            return false;
        }

        if (cmp(node->data, cur->data)) {
            cur = cur->left;
        } else {
            cur = cur->right;
        }
    }

    if (root) {
        node->parent = parent;
    }

    if (parent && root) {
        if (!cmp(node->data, parent->data) && !cmp(parent->data, node->data)) {
            return false;
        }

        if (cmp(node->data, parent->data)) {
            parent->left = node;
        } else {
            parent->right = node;
        }
    } else {
        root = node;
        super_root->left = root;
    }

    InsertFixUp(node);
    return true;
}

template <class T, class Comparator>
void RBTree<T, Comparator>::InsertFixUp(RBNode<T> *node) {
    RBNode<T> *parent = node->parent;

    while (node != root && parent->color == Red) {
        RBNode<T> *gparent = parent->parent;

        if (gparent->left == parent) {
            RBNode<T> *uncle = gparent->right;

            if (uncle && uncle->color == Red) {
                parent->color = Black;
                uncle->color = Black;
                gparent->color = Red;
                node = gparent;
                parent = node->parent;
            } else {
                if (parent->right == node) {
                    leftRotate(parent);
                    std::swap(node, parent);
                }

                rightRotate(gparent);
                gparent->color = Red;
                parent->color = Black;
                break;
            }
        } else {
            RBNode<T> *uncle = gparent->left;

            if (uncle && uncle->color == Red) {
                gparent->color = Red;
                parent->color = Black;
                uncle->color = Black;

                node = gparent;
                parent = node->parent;
            } else {
                if (parent->left == node) {
                    rightRotate(parent);
                    std::swap(parent, node);
                }

                leftRotate(gparent);
                parent->color = Black;
                gparent->color = Red;
                break;
            }
        }
    }

    root->color = Black;
}

template <class T, class Comparator>
bool RBTree<T, Comparator>::remove(T value) {
    RBNode<T> *deletenode = search(root, value);

    if (deletenode) {
        remove(deletenode);

        return true;
    }

    return false;
}

template <class T, class Comparator>
void RBTree<T, Comparator>::remove(RBNode<T> *node) {
    RBNode<T> *child, *parent;
    Color color;

    if (node->left && node->right) {
        RBNode<T> *replace = node->right;

        while (replace->left) {
            replace = replace->left;
        }

        if (node->parent != super_root) {
            if (node->parent->left == node) {
                node->parent->left = replace;
            } else {
                node->parent->right = replace;
            }
        } else {
            root = replace;
            super_root->left = root;
        }

        child = replace->right;
        parent = replace->parent;
        color = replace->color;

        if (parent == node) {
            parent = replace;
        } else {
            if (child)
                child->parent = parent;

            parent->left = child;
            replace->right = node->right;
            node->right->parent = replace;
        }

        replace->parent = node->parent;
        replace->color = node->color;
        replace->left = node->left;
        node->left->parent = replace;

        if (color == Black) {
            removeFixUp(child, parent);
        }

        delete node;
        return;
    }

    if (node->left) {
        child = node->left;
    } else {
        child = node->right;
    }

    parent = node->parent;
    color = node->color;

    if (child) {
        child->parent = parent;
    }

    if (parent != super_root) {
        if (node == parent->left) {
            parent->left = child;
        } else {
            parent->right = child;
        }
    } else {
        root = child;
        super_root->left = root;
    }

    if (color == Black) {
        removeFixUp(child, parent);
    }

    delete node;
}

template <class T, class Comparator>
void RBTree<T, Comparator>::removeFixUp(RBNode<T> *node, RBNode<T> *parent) {
    RBNode<T> *othernode;

    while (!node || node->color == Black && node != root) {
        if (parent->left == node) {
            othernode = parent->right;

            if (!othernode) {
                return;
            }

            if (othernode->color == Red) {
                othernode->color = Black;
                parent->color = Red;
                leftRotate(parent);
            } else {
                if (!(othernode->right) || othernode->right->color == Black) {
                    othernode->left->color = Black;
                    othernode->color = Red;
                    rightRotate(othernode);
                    othernode = parent->right;
                }

                othernode->color = parent->color;
                parent->color = Black;
                othernode->right->color = Black;
                leftRotate(parent);
                node = root;
                break;
            }
        } else {
            othernode = parent->left;

            if (othernode->color == Red) {
                othernode->color = Black;
                parent->color = Red;
                rightRotate(parent);
                othernode = parent->left;
            }

            if ((!othernode->left || othernode->left->color == Black) &&
                (!othernode->right || othernode->right->color == Black)) {
                othernode->color = Red;
                node = parent;
                parent = node->parent;
            } else {
                if (!(othernode->left) || othernode->left->color == Black) {
                    othernode->right->color = Black;
                    othernode->color = Red;
                    leftRotate(othernode);
                    othernode = parent->left;
                }

                othernode->color = parent->color;
                parent->color = Black;
                othernode->left->color = Black;
                rightRotate(parent);
                node = root;
                break;
            }
        }
    }
    if (node) {
        node->color = Black;
    }
}

template <class T, class Comparator>
void RBTree<T, Comparator>::print() {
    if (root == nullptr)
        std::cout << "empty RBtree\n";
    else
        print(root);
}

template <class T, class Comparator>
void RBTree<T, Comparator>::print(RBNode<T> *node) const {
    if (node == nullptr)
        return;

    if (super_root->left == node) {
        std::cout << node->data << "(" << node->color << ") is root" << std::endl;
    } else if (node->parent->left == node) {
        std::cout << node->data << "(" << node->color << ") is " << node->parent->data << "'s "
                  << "left child" << std::endl;
    } else {
        std::cout << node->data << "(" << node->color << ") is " << node->parent->data << "'s "
                  << "right child" << std::endl;
    }

    print(node->left);
    print(node->right);
}

template <class T, class Comparator>
void RBTree<T, Comparator>::destory(RBNode<T> *node) {
    if (!node) {
        return;
    }

    destory(node->left);
    destory(node->right);
    delete node;
}

template <class T, class Comparator>
RBNode<T> *RBTree<T, Comparator>::getMin() const {
    RBNode<T> *cur = root;

    while (cur->left) {
        cur = cur->left;
    }

    return cur;
}

template <class T, class Comparator>
RBNode<T> *RBTree<T, Comparator>::getMax() const {
    RBNode<T> *cur = root;

    while (cur->right) {
        cur = cur->right;
    }

    return cur;
}

template <class T, class Comparator>
RBNode<T> *RBTree<T, Comparator>::getLast() const {
    return super_root;
}
