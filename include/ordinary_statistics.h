#pragma once

#include <cstddef>
#include <vector>

const int BLACK = 1;
const int RED = 2;

class RBTree_with_statistics {
    struct node {
        int key;
        int color;
        size_t ltree_size;
        size_t rtree_size;
        node * parent;
        node * left;
        node * right;

        node(int num, node * prev);
    };

    node * root;
    size_t sz;

    node * grandparent(node * cur_node);
    bool parent_is_right(node * cur_node);
    node * uncle(node * cur_node);
    bool uncle_is_red(node * cur_node);
    void right_rotate(node * pivot);
    void left_rotate(node * pivot);
    void repair(node * cur_node);
    void print(node * root) const;

 public:
    RBTree_with_statistics();
    RBTree_with_statistics(std::vector<int>& v);
    size_t size() const;
    void insert(int num);
    bool find(int num) const;
    int operator[](double alpha) const;
    void print() const;
    ~RBTree_with_statistics();
};
