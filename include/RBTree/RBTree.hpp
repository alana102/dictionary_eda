// Alana Maria Sousa Augusto - 564976
#ifndef RBTREE_HPP
#define RBTREE_HPP
#include<iostream>
#include<stack>
#include "../compare.hpp"

using namespace std;

// definição de cores para tipo booleano
#define red true
#define black false

template <typename k, typename value>
// struct que define como é cada nó da árvore
struct NodeRB {

    pair<k, value> key; // chave do tipo par<template chave, template valor> 
    NodeRB* left; // ponteiro para esquerda
    NodeRB* right; // ponteiro para direita
    NodeRB* parent; // ponteiro para pai
    bool color; // variável para cor (vermelho ou preto)

    // construtor do nó
    NodeRB (pair<k, value> key, NodeRB* left, NodeRB* right, NodeRB* parent, bool color){
        this->key = key;
        this->left = left;
        this->right = right;
        this->parent = parent;
        this->color = color; 
    }

};

template <typename k, typename value>
class RBTree{
private:
    NodeRB<k, value>* root; // ponteiro para raiz
    NodeRB<k, value>* nil; // ponteiro para nil
    int counter_compare; // contador de comparações
    int counter_rotation; // contador de rotações

    // objeto que compara strings com acento
    CollatorCompare<k> compare;

    // retorna o valor mínimo de uma sub-árvore de raiz node
    NodeRB<k, value> *minimum(NodeRB<k, value> *node){
        if(node != nil && node->left != nil){
            return minimum(node->left);
        } else {
            return node;
        }
    }

    // função que escreve a árvore com seus
    // elementos em ordem crescente
    void printInfix(NodeRB<k, value>* node, bool& espaco) {
        if (node != nil) {
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

    // função que limpa a árvore inteiro,
    // apagando todos os nós recursivamente
    NodeRB<k,value> *clear(NodeRB<k, value>* node){
        if(node != nil){
            node->left = clear(node->left);
            node->right = clear(node->right);
            delete node;
        }
        return nil;
    }

    
public:

    // construtor vazio
    RBTree(){
        nil = new NodeRB<k, value>(make_pair(k{}, value{}), nullptr, nullptr, nullptr, black);
        nil->left = nil->right = nil;
        root = nil;
        root->parent = nil;
        counter_compare = 0;
        counter_rotation = 0;
    }

    // função que rotaciona a subárvore de node à esquerda
    void leftRotation(NodeRB<k, value>* x){
        NodeRB<k, value> *y = x->right;
        x->right = y->left;
        if(y->left != nil){
            y->left->parent = x;
        }
        y->parent = x->parent;

        if(x->parent == nil){
            root = y;
        } else if (x == x->parent->left){
            x->parent->left = y;
        } else {
            x->parent->right = y;
        }

        y->left = x;
        x->parent = y;  
    }

    // função que rotaciona a subárvore de node à direita
    void rightRotation(NodeRB<k, value>* x){
        NodeRB<k, value> *y = x->left;
        x->left = y->right;
        if(y->right != nil){
            y->right->parent = x;
        }
        y->parent = x->parent;

        if(x->parent == nil){
            root = y;
        } else if (x == x->parent->right){
            x->parent->right = y;
        } else {
            x->parent->left = y;
        }

        y->right = x;
        x->parent = y; 
    }

    // função que retorna se uma chave existe ou não na árvore
    bool search(k key){
        NodeRB<k, value>* aux = root;

        // enquanto eu nn chegar em uma folha (nil)
        while(aux != nil){

            // verificação do valor da chave para sabe pra onde deslocamos o aux
            if(compare(key, aux->key.first)){
                counter_compare++;
                aux = aux->left;
            } else if (compare(aux->key.first, key)){
                counter_compare+=2;
                aux = aux->right;
            } else {
                counter_compare+=2;
                // caso em que a chave já existe na árvore
                return true;
            }
        }

        return false;
    }

    // função que retorna um valor associado uma chave
    // ou insere a chave na árvore, caso ela não exista
    value& at(const k& key){

        NodeRB<k, value>* aux = root;

        // enquanto eu nn chegar em uma folha (nil)
        while(aux != nil){

            // verificação do valor da chave para sabe pra onde deslocamos o aux
            if(compare(key, aux->key.first)){
                counter_compare++;
                aux = aux->left;
            } else if (compare(aux->key.first, key)){
                counter_compare+=2;
                aux = aux->right;
            } else {
                counter_compare+=2;
                // caso em que a chave já existe na árvore
                return aux->key.second;
            }
        }

        insert(make_pair(key, value {}));
        aux = get(key);
        return aux->key.second;

    }

    // retorna o nó correspondente à uma chave passado por parâmetro
    NodeRB<k, value>* get(const k& key){
        NodeRB<k, value>* aux = root;

        // enquanto eu nn chegar em uma folha (nil)
        while(aux != nil){

            // verificação do valor da chave para sabe pra onde deslocamos o aux
            if(compare(key, aux->key.first)){
                counter_compare++;
                aux = aux->left;
            } else if (compare(aux->key.first, key)){
                counter_compare+=2;
                aux = aux->right;
            } else {
                counter_compare+=2;
                // caso em que a chave já existe na árvore
                return aux;
            }
        }

        throw out_of_range("key not found");
    }

    // função que ajeita a árvore em caso de desbalanceamento
    void RBfixup_insert(NodeRB<k, value>* node){

        while(node->parent->color == red){
            // caso em que o tio está do lado direito
            if(node->parent == node->parent->parent->left){
                NodeRB<k, value>* tio = node->parent->parent->right;

                // caso 1 (tio é vermelho)
                if(tio->color == red){
                    node->parent->color = black; // pinta o pai do novo de preto
                    tio->color = black; // pinta o tio do novo de preto
                    node->parent->parent->color = red; // pinta o avô do novo de vermelho
                    node = node->parent->parent; // novo vira o avô (o problema provavelmente subiu pra lá)
                // caso 2 e 3 (tio é preto)
                } else {
                    // caso 2 (novo é um filho direito)
                    if(node == node->parent->right){
                        node = node->parent; // faço logo antes da rotação pra nn perder o ponteiro
                        leftRotation(node);
                        counter_rotation++;
                    }
                    // caso 3 (novo é um filho esquerdo)
                    node->parent->color = black;
                    node->parent->parent->color = red;
                    
                    rightRotation(node->parent->parent);
                    counter_rotation++;

                }
            // caso em que o tio está do lado esquerdo (simétrico)
            } else {
                NodeRB<k, value>* tio = node->parent->parent->left;

                // caso 1 (tio é vermelho)
                if(tio->color == red){
                    node->parent->color = black; // pinta o pai do novo de preto
                    tio->color = black; // pinta o tio do novo de preto
                    node->parent->parent->color = red; // pinta o avô do novo de vermelho
                    
                    node = node->parent->parent; // novo vira o avô (o problema provavelmente subiu pra lá)
                // caso 2 e 3 (tio é preto)
                } else {
                    // caso 2 (novo é um filho esquerdo)
                    if(node == node->parent->left){
                        node = node->parent; // faço logo antes da rotação pra nn perder o ponteiro
                        rightRotation(node);
                        counter_rotation++;
                    }
                    // caso 3 (novo é um filho direito)
                    node->parent->color = black;
                    node->parent->parent->color = red;
                    
                    leftRotation(node->parent->parent);
                    counter_rotation++;

                }
            }

        }


        root->color = black;
        
    }

    // função que insere um nó na árvore
    void insert(pair<k, value> key){
        // ponteiros para o nó atual (aux) que estou verificando e seu pai (pai)
        NodeRB<k, value>* aux = root;
        NodeRB<k, value>* pai = nil;

        // enquanto eu nn chegar em uma folha (nil)
        while(aux != nil){
            // vamos deslocar os ponteiros, então pai recebe o que antes era o nó atual
            pai = aux;
            // verificação do valor da chave para sabe pra onde deslocamos o aux
            if(compare(key.first, aux->key.first)){
                counter_compare++;
                aux = aux->left;
            } else if (compare(aux->key.first, key.first)){
                counter_compare+=2;
                aux = aux->right;
            } else {
                counter_compare+=2;
                aux->key.second = key.second;
                // caso em que a chave já existe na árvore
                return;
            }
        }

        // cria novo nó com a chave
        NodeRB<k, value> *z = new NodeRB<k, value>(key, nil, nil, nullptr, red);

        // caso em que a árvore é vazia 
        // novo nó vai ser justamente a raiz
        if(pai == nil){
            root = z;
            z->parent = nil;
        // árvore não é vazia
        } else {
            // o pai do novo nó vira o ponteiro pai que declaramos antes
            // esse ponteiro vai ser necessariamente o pai do novo nó 
            // porque é onde ele parou no laço while
            z->parent = pai;

            // verifica de que lado do pai inserimos o novo nó
            if(compare(key.first, pai->key.first)){
                counter_compare++;
                pai->left = z;
            } else {
                counter_compare++;
                pai->right = z;
            }
        }

        // função para ajeitar a árvore mantendo-a como rubro-negra
        // após a inserção
        RBfixup_insert(z);
    }

    // função de remover nó
    void remove(k keyremove){
        NodeRB<k, value>* p = root;
        while(p != nil && p->key.first != keyremove){
            if(compare(keyremove, p->key.first)){
                counter_compare++;
                p = p->left;
            } else {
                counter_compare++;
                p = p->right;
            }
        }

        if(p != nil){
            RB_delete(p);
        }
    }

    // função auxiliar de remoção
    void RB_delete(NodeRB<k, value>* z){
        NodeRB<k, value>* y = nil;
        NodeRB<k, value>* x = nil;
        if(z->left == nil || z->right == nil){
            y = z;
        } else {
            y = minimum(z->right);
        }

        if(y->left != nil){
            x = y->left;
        } else {
            x = y->right;
        }

        x->parent = y->parent;
        if(y->parent == nil){
            root = x;
        } else {
            if(y == y->parent->left){
                y->parent->left = x;
            } else {
                y->parent->right = x;
            }
        }

        if(y != z){
            z->key = y->key;
        }

        if(y->color == black){
            RBfixup_delete(x);
        }

        delete y;
    }

    // função que ajeita as colorações dos nós após uma remoção
    void RBfixup_delete(NodeRB<k, value>* x){
        NodeRB<k, value>* w;
        while(x != root && x->color == black){
            if(x == x->parent->left){
                w = x->parent->right;
                if(w->color == red){
                    w->color = black;
                    x->parent->color = red;
                    
                    leftRotation(x->parent);
                    counter_rotation++;
                    w = x->parent->right;
                }

                if(w->left->color == black && w->right->color == black){
                    w->color = red;
                    
                    x = x->parent;
                } else{
                    if(w->right->color == black){
                        w->left->color = black;
                        w->color = red;
                        
                        rightRotation(w);
                        counter_rotation++;
                        w = x->parent->right;
                    }

                    w->color = x->parent->color;
                    x->parent->color = black;
                    w->right->color = black;
                    
                    leftRotation(x->parent);
                    counter_rotation++;
                    x = root;
                }
        // caso simétrico        
        } else {
            w = x->parent->left;
                if(w->color == red){
                    w->color = black;
                    x->parent->color = red;
                    
                    rightRotation(x->parent);
                    counter_rotation++;
                    w = x->parent->left;
                }

                if(w->right->color == black && w->left->color == black){
                    w->color = red;
                    
                    x = x->parent;
                } else{
                    if(w->left->color == black){
                        w->right->color = black;
                        w->color = red;
                        
                        leftRotation(w);
                        counter_rotation++;
                        w = x->parent->left;
                    }

                    w->color = x->parent->color;
                    x->parent->color = black;
                    w->left->color = black;
                    
                    rightRotation(x->parent);
                    counter_rotation++;
                    x = root;
                }

        }

        

        }
        x->color = black;
        
    }


    // função que retorna a altura negra da árvore
    int blackHeight(){
        int contador = 0;
        NodeRB<k, value>* aux = root;
        while(aux != nil){
            aux = aux->left;
            if(aux->color == black){
                contador++;
            }
        }
        return contador;
    }

    // retorna a quantidade de comparações feitas
    int getCounterCompare(){
        return counter_compare;
    }

    // retorna a quantidade de rotações feitas
    int getCounterRotation(){
        return counter_rotation;
    }

    // função que printa os nós da árvore em
    // ordem crescente
    void print(){
        bool espaco = true;
        printInfix(root, espaco);
        cout << endl;
    }

    // função que retorna quantos nós a árvore possui
    int size(){
        int contador = 0;

        if(root == nil){
            return contador;
        }

        stack<NodeRB<k, value>*> pilha;
        pilha.push(root);

        while(!pilha.empty()){
            NodeRB<k, value>* aux = pilha.top();
            pilha.pop();

            if(aux != nil){
                contador++;
                pilha.push(aux->left);
                pilha.push(aux->right);
            }
        }

        return contador;
    }

    // função pública que limpa a árvore toda
    void clear(){
        root = clear(root);
    }

    // destrutor
    ~RBTree(){
        root = clear(root);
        counter_compare = 0;
        counter_rotation = 0;
    }
};

#endif
