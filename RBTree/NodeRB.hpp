#ifndef NodeRB_HPP
#define NodeRB_HPP
#include <iostream>

#define red true
#define black false

template <typename k, typename value>
struct NodeRB {

    pair<k, value> key;
    NodeRB* left;
    NodeRB* right;
    NodeRB* parent;
    bool color; 

    NodeRB (pair<k, value> key, NodeRB* left, NodeRB* right, NodeRB* parent, bool color){
        this->key = key;
        this->left = left;
        this->right = right;
        this->parent = parent;
        this->color = color; 
    }

};

#endif