#include "ordinary_statistics.h"
#include <stack>
#include <iostream>
#include <stdexcept>
#include <cmath>

RBTree_with_statistics::node::node(int num, node * prev)
        : key(num), color(RED), ltree_size(0), rtree_size(0), parent(prev), left(nullptr),
          right(nullptr) {}


RBTree_with_statistics::node * RBTree_with_statistics::grandparent(node * cur_node) {
    return cur_node->parent->parent;
}

bool RBTree_with_statistics::parent_is_right(node * cur_node) {
    return (grandparent(cur_node)->right == cur_node->parent);
}

RBTree_with_statistics::node * RBTree_with_statistics::uncle(node * cur_node) {
    if (parent_is_right(cur_node))
        return grandparent(cur_node)->left;
    else
        return grandparent(cur_node)->right;
}

bool RBTree_with_statistics::uncle_is_red(node * cur_node) {
    if (uncle(cur_node) != nullptr)
        return uncle(cur_node)->color == RED;
    return false;
}

void RBTree_with_statistics::right_rotate(node * pivot) {
    if (grandparent(pivot) != nullptr) {
        pivot->parent->ltree_size = pivot->rtree_size;
        pivot->rtree_size = pivot->parent->ltree_size + pivot->parent->rtree_size + 1;
        pivot->parent->left = pivot->right;
        if (pivot->right != nullptr)
            pivot->right->parent = pivot->parent;
        pivot->right = pivot->parent;
        if (parent_is_right(pivot))
            pivot->parent->parent->right = pivot;
        else
            pivot->parent->parent->left = pivot;
        auto ptr = grandparent(pivot);
        pivot->parent->parent = pivot;
        pivot->parent = ptr;
    } else {
        root = pivot;
        pivot->parent->ltree_size = pivot->rtree_size;
        pivot->rtree_size = pivot->parent->ltree_size + pivot->parent->rtree_size + 1;
        pivot->parent->left = pivot->right;
        if (pivot->right != nullptr)
            pivot->right->parent = pivot->parent;
        pivot->right = pivot->parent;
        pivot->parent->parent = pivot;
        pivot->parent = nullptr;
    }
}

void RBTree_with_statistics::left_rotate(node * pivot) {
    if (grandparent(pivot) != nullptr) {
        pivot->parent->rtree_size = pivot->ltree_size;
        pivot->ltree_size = pivot->parent->ltree_size + pivot->parent->rtree_size + 1;
        pivot->parent->right = pivot->left;
        if (pivot->left != nullptr)
            pivot->left->parent = pivot->parent;
        pivot->left = pivot->parent;
        if (parent_is_right(pivot))
            pivot->parent->parent->right = pivot;
        else
            pivot->parent->parent->left = pivot;
        auto ptr = grandparent(pivot);
        pivot->parent->parent = pivot;
        pivot->parent = ptr;
    } else {
        root = pivot;
        pivot->parent->rtree_size = pivot->ltree_size;
        pivot->ltree_size = pivot->parent->ltree_size + pivot->parent->rtree_size + 1;
        pivot->parent->right = pivot->left;
        if (pivot->left != nullptr)
            pivot->left->parent = pivot->parent;
        pivot->left = pivot->parent;
        pivot->parent->parent = pivot;
        pivot->parent = nullptr;
    }
}

void RBTree_with_statistics::repair(node * cur_node) {
    if (cur_node == root) {
        if (cur_node->color == RED)
            cur_node->color = BLACK;
        return;
    }
    if (cur_node->parent->color == BLACK)
        return;
    if (uncle_is_red(cur_node)) {
        grandparent(cur_node)->color = RED;
        cur_node->parent->color = BLACK;
        uncle(cur_node)->color = BLACK;
        repair(grandparent(cur_node));
    } else if (cur_node->parent->right == cur_node && parent_is_right(cur_node)) {
        cur_node->parent->color = BLACK;
        grandparent(cur_node)->color = RED;
        left_rotate(cur_node->parent);
    } else if (cur_node->parent->left == cur_node && !parent_is_right(cur_node)) {
        cur_node->parent->color = BLACK;
        grandparent(cur_node)->color = RED;
        right_rotate(cur_node->parent);
    } else if (cur_node->parent->right == cur_node && !parent_is_right(cur_node)) {
        cur_node->color = BLACK;
        grandparent(cur_node)->color = RED;
        left_rotate(cur_node);
        right_rotate(cur_node);
    } else if (cur_node->parent->left == cur_node && parent_is_right(cur_node)) {
        cur_node->color = BLACK;
        grandparent(cur_node)->color = RED;
        right_rotate(cur_node);
        left_rotate(cur_node);
    }
}

RBTree_with_statistics::RBTree_with_statistics() : root(nullptr), sz(0) {}

RBTree_with_statistics::RBTree_with_statistics(std::vector<int>& v) {
    root = nullptr;
    sz = 0;
    for (auto elem : v) {
        if (sz == 0) {
            root = new node(elem, nullptr);
            root->color = BLACK;
            ++sz;
        } else {
            this->insert(elem);
        }
    }
}

size_t RBTree_with_statistics::size() const {
    return sz;
}

void RBTree_with_statistics::insert(int num) {
    if (sz == 0) {
        root = new node(num, nullptr);
        root->color = BLACK;
        sz = 1;
        return;
    }

    auto cur_pos = root;
    while (true) {
        if (num >= cur_pos->key) {
            if (cur_pos->right != nullptr) {
                ++(cur_pos->rtree_size);
                cur_pos = cur_pos->right;
            } else {
                ++(cur_pos->rtree_size);
                cur_pos->right = new node(num, cur_pos);
                cur_pos = cur_pos->right;
                ++sz;
                break;
            }
        } else if (num < cur_pos->key) {
            if (cur_pos->left != nullptr) {
                ++(cur_pos->ltree_size);
                cur_pos = cur_pos->left;
            } else {
                ++(cur_pos->ltree_size);
                cur_pos->left = new node(num, cur_pos);
                cur_pos = cur_pos->left;
                ++sz;
                break;
            }
        }
    }
    repair(cur_pos);
}

bool RBTree_with_statistics::find(int num) const {
    node * cur_pos = root;
    while (cur_pos != nullptr) {
        if (num < cur_pos->key)
            cur_pos = cur_pos->left;
        else if (num > cur_pos->key)
            cur_pos = cur_pos->right;
        else
            return true;
    }
    return false;
}

int RBTree_with_statistics::operator[](double alpha) const {
    if (alpha < 0 || alpha >= 1)
        throw std::invalid_argument
                (
                        "incorrect argument: std::ceil(alpha * size) must be less than size"
                );

    size_t n = static_cast<size_t>(std::ceil(alpha * sz));
    size_t cur_count = root->ltree_size;
    auto cur_pos = root;
    while (n != cur_count) {
        if (cur_count < n) {
            cur_pos = cur_pos->right;
            cur_count += 1 + cur_pos->ltree_size;
        } else if (cur_count > n) {
            cur_pos = cur_pos->left;
            cur_count -= 1 + cur_pos->rtree_size;
        }
    }
    return cur_pos->key;
}

void RBTree_with_statistics::print(node * cur_node) const {
    if (cur_node == nullptr)
        return;
    print(cur_node->left);
    std::cout << cur_node->key << ' ';
    print(cur_node->right);
}

void RBTree_with_statistics::print() const {
    print(root);
}

RBTree_with_statistics::~RBTree_with_statistics() {
    if (root != nullptr) {
        std::stack<node *> temp;
        temp.push(root);
        while (!temp.empty()) {
            node * cur_node = temp.top();
            temp.pop();
            if (cur_node->left != nullptr)
                temp.push(cur_node->left);
            if (cur_node->right != nullptr)
                temp.push(cur_node->right);
            delete cur_node;
        }
    }
}
