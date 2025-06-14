#ifndef NODERB_HPP
#define NODERB_HPP
#include <iostream>

#define red true
#define black false

template <typename k, typename value>
struct Node {

    pair<k, value> key;
    Node* left;
    Node* right;
    Node* parent;
    bool color; 

    Node (pair<k, value> key, Node* left, Node* right, Node* parent, bool color){
        this->key = key;
        this->left = left;
        this->right = right;
        this->parent = parent;
        this->color = color; 
    }

    ~Node(){
        std::cout << "O nó " << key << " foi deletado" << std::endl;
    }
};

#endif