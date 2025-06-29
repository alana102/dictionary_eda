// Alana Maria Sousa Augusto - 564976
#ifndef AVL_HPP
#define AVL_HPP
#include<vector>
#include<iostream>

using namespace std;

template <typename k, typename value>
// struct que define como é cada nó da árvore
struct Node{

    pair<k, value> key; // chave do tipo par<template chave, template valor> 
    Node *right; // ponteiro para direita
    Node *left; // ponteiro para esquerda
    int height; // altura da árvore

    // construtor do nó
    Node(pair<k, value> newKey, Node *r, Node *l){
        key = newKey;
        right = r;
        left = l;
        height = 1;
    }
};

template<typename k, typename value>
class AVL {
private:
    Node<k, value>* root; // raiz da árvore
    int counter_compare; // contador de comparações
    int counter_rotations; // contador de rotações

    // função que limpa a árvore inteira,
    // apagando todos os nós recursivamente
    Node<k,value> *clear(Node<k, value>* node){
        if(node != nullptr){
            node->left = clear(node->left);
            node->right = clear(node->right);
            delete node;
        }
        return nullptr;
    }

    // função que retorna a altura de determinado nó
    int height(Node<k, value>* node){
   
        if(node == nullptr){
            return 0;
        } else {
            return node->height;
        }
    }

    // função que retorna o tamanho da árvore
    int size(Node<k, value>* node){
        if(node == nullptr){
            return 0;
        }

        int left = size(node->left);
        int right = size(node->right);

        return 1 + left + right;
    }

    // função que ajeita os nós em caso de desbalanceamento durante
    // o processo de remoção de um nó
    Node<k, value> *fixup_deletion(Node<k, value>* node){
        int bal = balance(node);

        if(bal > 1 && balance(node->right) >=0 ){
            counter_rotations++;
            return rotation_left(node);
        } else if (bal > 1 && balance(node->right) < 0) {
            node->right = rotation_right(node->right);
            counter_rotations++;
            counter_rotations++;
            return rotation_left(node);
        } else if (bal < -1 && balance(node->left) <= 0) {
            counter_rotations++;
            return rotation_right(node);
        } else if (bal < -1 && balance(node->left) > 0) {
            node->left = rotation_left(node->left);
            counter_rotations++;
            counter_rotations++;
            return rotation_right(node);

        }

        node->height = 1 + max(height(node->left), height(node->right));
        return node;
    }

    // função que remove um elemento da árvore
    // se tiver filho direito, chama a função de remover sucessor
    // se não tiver apenas faz com que o filho esquerdo assuma o lugar do nó
    // depois disso ajeita o balanceamento do nó
    Node<k, value> *remove(Node<k, value> *node, pair<k, value> key){
        if (node == nullptr){
            return nullptr;
        } 
        if (key.first < node->key.first){
            counter_compare++;
            node->left = remove(node->left, key);
        } else if (key.first > node->key.first) {
            counter_compare+=2;
            node->right = remove(node->right, key);
        } else if (node->right == nullptr){
            Node<k, value> *filho = node->left;
            delete node;
            return filho;
        } else {
            counter_compare+=2;
            node->right = remove_successor(node, node->right);
        }

        node = fixup_deletion(node);
        return node;

    }    

    // função chamada em caso de remoção de um nó que possui filho direito
    // essa função faz com que o nó a ser removido receba a chave de seu sucessor
    // e logo em seguida o sucessor é liberado
    Node<k, value> *remove_successor(Node<k, value> *root, Node<k, value> *node) {
        if(node->left != nullptr){
            node->left = remove_successor(root, node->left);
        } else {
            root->key = node->key;
            Node<k, value> *aux = node->right;
            delete node;
            return aux;
        }
        node = fixup_deletion(node);
        return node;
    }

    // função que retorna um nó de acordo com 
    // a chave passada como parâmetro
    Node<k, value> *get(Node<k, value> *node, k key){
        if (node == nullptr) {
            return nullptr;
        }

        if(node->key.first == key){
            counter_compare++;
            return node;
        } else if (key < node->key.first) {
            counter_compare+=2;
            return get(node->left, key);
        } else {
            counter_compare+=2;
            return get(node->right, key);
        } 


    }


    // função que rotaciona a subárvore de node à direita
    Node<k, value> *rotation_right(Node<k, value> *node){
        Node<k, value> *u = node->left;
        node->left = u->right;
        u->right = node;

        node->height = 1 + max(height(node->right), height(node->left));
        u->height = 1 + max(height(u->right), height(u->left));

        return u;
    }

    // função que rotaciona a subárvore de node à esquerda
    Node<k, value> *rotation_left(Node<k, value> *node){
        Node<k, value> *u = node->right;
        node->right = u->left;
        u->left = node;

        node->height = 1 + max(height(node->right), height(node->left));
        u->height = 1 + max(height(u->right), height(u->left));

        return u;
    }

    // função que retorna o balanço de um nó
    int balance(Node<k, value> *node){
        return height(node->right) - height(node->left);
    }

    // função que conserta o balanço dos nós
    // caso exista algum nó desbalanceado após a inserção
    Node<k, value> *fixup_insertion(Node<k, value> *p, pair<k, value> key){

        p->height = 1 + max(height(p->left), height(p->right));

        int bal = balance(p);

        if(bal < -1 && key.first < p->left->key.first){
            counter_compare++;
            counter_rotations++;
            return rotation_right(p);
        } else if(bal < -1 && key.first > p->left->key.first){
            counter_compare+=2;
            p->left = rotation_left(p->left);
            counter_rotations+=2;
            return rotation_right(p);  
        } else if(bal > 1 && key.first > p->right->key.first){
            counter_compare+=3;
            counter_rotations++;
            return rotation_left(p);
        } else if(bal > 1 && key.first < p->right->key.first){
            counter_compare+=4;
            p->right = rotation_right(p->right);
            counter_rotations+=2;
            return rotation_left(p);  
        } else {
            counter_compare+=4;
        }
        
        return p;

    }

    // função que insere um elemento na árvore recursivamente
    Node<k, value> *insert(Node<k, value>* node, pair<k, value> key){

        if(node == nullptr){
            return new Node<k, value>(key, nullptr, nullptr);
        } else if (key.first < node->key.first) {
            counter_compare++;
            node->left = insert(node->left, key);
        } else if (key.first > node->key.first) {
            counter_compare+=2;
            node->right = insert(node->right, key);
        } else {
            node->key.second = key.second;
            counter_compare+=2;
            return node;
        }

        node = fixup_insertion(node, key);

        return node;
    }

    // função que retorna o valor associado a uma chave na árvore
    // caso a chave não existe, um novo nó é criado com a chave 
    // e inserido na árvore 
    value& at(Node<k, value>*& node, const k& key){
        if(node == nullptr){
            node = insert(node, make_pair(key, value{}));
            return node->key.second;
        }

        if (key < node->key.first) {
            counter_compare++;
            return at(node->left, key);
        } else if (key > node->key.first) {
            counter_compare+=2;
            return at(node->right, key);
        } else {
            counter_compare+=2;
            return node->key.second;
        }
        
    }

    // função que escreve a árvore com seus
    // elementos em ordem crescente
    void printInfix(Node<k, value>* node, bool& espaco) {
        if (node != nullptr) {
            printInfix(node->left, espaco);
            if (espaco) {
                cout << "(" << node->key.first << ", " << node->key.second <<")";
                espaco = false;
            } else {
                cout << ", " << "(" << node->key.first << ", " << node->key.second <<")";
            }
            printInfix(node->right, espaco);
        }
    }

    // função auxiliar que copia um nó em outro
    // auxilia na lógica da sobrecarga do operador de atribuição
    Node<k, value>* copiaNo(Node<k, value>* no){
        if(no == nullptr){
            return nullptr;
        }

        Node<k, value>* novo_no = new Node<k, value>(no->key, nullptr, nullptr);

        novo_no->left = copiaNo(no->left);
        novo_no->right = copiaNo(no->right);
        novo_no->height = no->height;

        return novo_no;
    }

    // função que retorna o menor elemento 
    Node<k, value> *minimum(Node<k, value> *node){
        if(node != nullptr && node->left != nullptr){
            return minimum(node->left);
        } else {
            return node;
        }
    }




public:

    // construtor vazio
    AVL(){
        root = nullptr;
        counter_compare = 0;
        counter_rotations = 0;
    }

    // função que insere um novo elemento na árvore
    void insert(pair<k, value> key){
        root = insert(root, key);
    }

    // função que remove um elemento da árvore
    void erase(pair<k, value> key){
        root = remove(root, key);
    }

    // função que retorna a altura total da árvore
    int total_height(){
        return height(root);
    }

    // função que retorna a altura de um determinado nó
    int height(k key){
        if(get(root, key) == nullptr){
            return 0;
        } else {
            return height(get(root, key));
        }
    }

    // função pública que retorna tamanho da árvore
    // chamando a sua versão privada
    int size(){
        return size(root);
    }

    // retorna o valor associado a uma chave
    // ou insere a chave na árvore caso ela não exista
    value& at(const k &key){
        return at(root, key);
    }

    // verifica se a árvore é vazia
    bool empty(){
        return root == nullptr;
    }

    // verifica se um elemento pertence aa árvore
    bool contains(k key){
        return get(root, key) != nullptr;
    }

    // função que retorna quantas comparações foram feitas
    int getCounterCompare(){
        return counter_compare;
    }

    // função que retorna quantas rotações foram feitas
    int getCounterRotation(){
        return counter_rotations;
    }

    // sobrecarga do operador de atribuição
    AVL& operator=(const AVL& s){

        if (this == &s){
            return *this;
        }

        this->clear(root);

        this->root = copiaNo(s.root);

        return *this;
    }

    // função publica que limpa uma árvore
    // deletando todos os seus elementos
    void clear(){
        root = clear(root);
    }

    // função que printa os nós da árvore em
    // ordem crescente
    void print(){
        bool espaco = true;
        printInfix(root, espaco);
        cout << endl;
    }


    // destrutor
    ~AVL(){
        root = clear(root);
    }

    
};


#endif