// Alana Maria Sousa Augusto - 564976
#ifndef NODEAVL_HPP
#define NODEAVL_HPP
#include<iostream>
using namespace std;

template <typename k, typename value>
struct Node{

    pair<k, value> key;
    Node *right;
    Node *left;
    int height;

    Node(pair<k, value> newKey, Node *r, Node *l){
        key = newKey;
        right = r;
        left = l;
        height = 1;
    }

    ~Node(){
        cout << "no (" << key.first << ", " << key.second << ") removido com sucesso" << endl;
    }

};

#endif