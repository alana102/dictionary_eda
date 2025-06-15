#ifndef RBTREE_HPP
#define RBTREE_HPP
#include "NodeRB.hpp"

template <typename k, typename value>

class RBTree{
private:
    // ponteiro para raiz
    NodeRB<k, value>* root;
    // ponteiro para nil
    NodeRB<k, value>* nil;
    // contador de comparações
    int counter_compare;
    // contador de troca de cores
    int counter_switch;

    void bshow(NodeRB<k, value> *node, std::string heranca) {
        if(node != nil && (node->left != nil || node->right != nil))
            bshow(node->right , heranca + "r");

        for(int i = 0; i < (int) heranca.size() - 1; i++)
            std::cout << (heranca[i] != heranca[i + 1] ? "|   " : "    ");

        if(heranca != "")
            std::cout << (heranca.back() == 'r' ? "|-- " : "|-- ");
        
        if(node == nil){
            std::cout << "#" << std::endl;
            return;
        }

        std::cout << "(" << node->key.first << ", " << node->key.second << ")";
        if(node->color == red){
            std::cout << " R" << std::endl;
        } else {
            std::cout << " B" << std::endl;
        }

        if(node != nil && (node->left != nil || node->right != nil))
            bshow(node->left, heranca + "l");
    }

    // retorna o valor mínimo de uma sub-árvore de raiz node
    NodeRB<k, value> *minimum(NodeRB<k, value> *node){
        if(node != nil && node->left != nil){
            return minimum(node->left);
        } else {
            return node;
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
        return nullptr;
    }

    
public:

    // construtor vazio
    RBTree(){
        nil = new NodeRB<k, value>(make_pair(k{}, value{}), nullptr, nullptr, nullptr, black);
        nil->left = nil->right = nil;
        root = nil;
        root->parent = nil;
        counter_compare = 0;
        counter_switch = 0;
    }

    void bshow(){
        bshow(root, "");
    }

    // rotação a esquerda
    void leftRotation(RBTree<k, value>* T, NodeRB<k, value>* x){
        NodeRB<k, value> *y = x->right;
        x->right = y->left;
        if(y->left != T->nil){
            y->left->parent = x;
        }
        y->parent = x->parent;

        if(x->parent == T->nil){
            T->root = y;
        } else if (x == x->parent->left){
            x->parent->left = y;
        } else {
            x->parent->right = y;
        }

        y->left = x;
        x->parent = y;  
    }

    // rotação a direita
    void rightRotation(RBTree<k, value>* T, NodeRB<k, value>* x){
        NodeRB<k, value> *y = x->left;
        x->left = y->right;
        if(y->right != T->nil){
            y->right->parent = x;
        }
        y->parent = x->parent;

        if(x->parent == T->nil){
            T->root = y;
        } else if (x == x->parent->right){
            x->parent->right = y;
        } else {
            x->parent->left = y;
        }

        y->right = x;
        x->parent = y; 
    }

    bool search(RBTree<k, value>* T, pair<k, value> key){
        NodeRB<k, value>* aux = T->root;

        // enquanto eu nn chegar em uma folha (nil)
        while(aux != T->nil){

            // verificação do valor da chave para sabe pra onde deslocamos o aux
            if(key.first < aux->key.first){
                counter_compare++;
                aux = aux->left;
            } else if (key.first > aux->key.first){
                counter_compare++;
                aux = aux->right;
            } else {
                // caso em que a chave já existe na árvore
                return true;
            }
        }

        return false;
    }

    void RBfixup_insert(RBTree<k, value>* T, NodeRB<k, value>* node){

        while(node->parent->color == red){
            // caso em que o tio está do lado direito
            if(node->parent == node->parent->parent->left){
                NodeRB<k, value>* tio = node->parent->parent->right;

                // caso 1 (tio é vermelho)
                if(tio->color == red){
                    node->parent->color = black; // pinta o pai do novo de preto
                    counter_switch++;
                    tio->color = black; // pinta o tio do novo de preto
                    counter_switch++;
                    node->parent->parent->color = red; // pinta o avô do novo de vermelho
                    counter_switch++;
                    node = node->parent->parent; // novo vira o avô (o problema provavelmente subiu pra lá)
                // caso 2 e 3 (tio é preto)
                } else {
                    // caso 2 (novo é um filho direito)
                    if(node == node->parent->right){
                        node = node->parent; // faço logo antes da rotação pra nn perder o ponteiro
                        leftRotation(T, node);
                    }
                    // caso 3 (novo é um filho esquerdo)
                    node->parent->color = black;
                    counter_switch++;
                    node->parent->parent->color = red;
                    counter_switch++;
                    rightRotation(T, node->parent->parent);

                }
            // caso em que o tio está do lado esquerdo (simétrico)
            } else {
                NodeRB<k, value>* tio = node->parent->parent->left;

                // caso 1 (tio é vermelho)
                if(tio->color == red){
                    node->parent->color = black; // pinta o pai do novo de preto
                    counter_switch++;
                    tio->color = black; // pinta o tio do novo de preto
                    counter_switch++;
                    node->parent->parent->color = red; // pinta o avô do novo de vermelho
                    counter_switch++;
                    node = node->parent->parent; // novo vira o avô (o problema provavelmente subiu pra lá)
                // caso 2 e 3 (tio é preto)
                } else {
                    // caso 2 (novo é um filho esquerdo)
                    if(node == node->parent->left){
                        node = node->parent; // faço logo antes da rotação pra nn perder o ponteiro
                        rightRotation(T, node);
                    }
                    // caso 3 (novo é um filho direito)
                    node->parent->color = black;
                    node->parent->parent->color = red;
                    leftRotation(T, node->parent->parent);

                }
            }

        }


        T->root->color = black;
    }

    // função que insere um nó na árvore
    // essa função não vai fazer a rotação por si só
    // ela só implementa a lógica base de uma inserção em uma BST
    // iterativa!!!
    void insert(RBTree<k, value>* T, pair<k, value> key){
        // ponteiros para o nó atual (aux) que estou verificando e seu pai (pai)
        NodeRB<k, value>* aux = T->root;
        NodeRB<k, value>* pai = T->nil;

        // enquanto eu nn chegar em uma folha (nil)
        while(aux != T->nil){
            // vamos deslocar os ponteiros, então pai recebe o que antes era o nó atual
            pai = aux;
            // verificação do valor da chave para sabe pra onde deslocamos o aux
            if(key.first < aux->key.first){
                counter_compare++;
                aux = aux->left;
            } else if (key.first > aux->key.first){
                counter_compare++;
                aux = aux->right;
            } else {
                // caso em que a chave já existe na árvore
                return;
            }
        }

        // cria novo nó com a chave
        NodeRB<k, value> *z = new NodeRB<k, value>(key, T->nil, T->nil, nullptr, red);

        // caso em que a árvore é vazia 
        // novo nó vai ser justamente a raiz
        if(pai == T->nil){
            T->root = z;
            z->parent = nil;
        // árvore não é vazia
        } else {
            // o pai do novo nó vira o ponteiro pai que declaramos antes
            // esse ponteiro vai ser necessariamente o pai do novo nó 
            // porque é onde ele parou no laço while
            z->parent = pai;

            // verifica de que lado do pai inserimos o novo nó
            if(key.first < pai->key.first){
                counter_compare++;
                pai->left = z;
            } else {
                pai->right = z;
            }
        }

        // função para ajeitar a árvore mantendo-a como rubro-negra
        // após a inserção
        RBfixup_insert(T, z);
    }

    // função de remover nó
    void remove(RBTree<k, value>* T, pair<k, value> keyremove){
        NodeRB<k, value>* p = T->root;
        while(p != T->nil && p->key != keyremove){
            if(keyremove.first < p->key.first){
                p = p->left;
            } else {
                p = p->right;
            }
        }

        if(p != T->nil){
            RB_delete(T, p);
        }
    }

    // função auxiliar de remoção
    void RB_delete(RBTree<k, value>* T, NodeRB<k, value>* z){
        NodeRB<k, value>* y = T->nil;
        NodeRB<k, value>* x = T->nil;
        if(z->left == T->nil || z->right == T->nil){
            y = z;
        } else {
            y = minimum(z->right);
        }

        if(y->left != T->nil){
            x = y->left;
        } else {
            x = y->right;
        }

        x->parent = y->parent;
        if(y->parent == T->nil){
            T->root = x;
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
            RBfixup_delete(T, x);
        }

        delete y;
    }

    // função que ajeita as colorações dos nós após uma remoção
    void RBfixup_delete(RBTree<k, value>* T, NodeRB<k, value>* x){
        NodeRB<k, value>* w;
        while(x != T->root && x->color == black){
            if(x == x->parent->left){
                w = x->parent->right;
                if(w->color == red){
                    w->color = black;
                    x->parent->color = red;
                    leftRotation(T, x->parent);
                    w = x->parent->right;
                }

                if(w->left->color == black && w->right->color == black){
                    w->color = red;
                    x = x->parent;
                } else{
                    if(w->right->color == black){
                        w->left->color = black;
                        w->color = red;
                        rightRotation(T, w);
                        w = x->parent->right;
                    }

                    w->color = x->parent->color;
                    x->parent->color = black;
                    w->right->color = black;
                    leftRotation(T, x->parent);
                    x = T->root;
                }
        // caso simétrico        
        } else {
            w = x->parent->left;
                if(w->color == red){
                    w->color = black;
                    x->parent->color = red;
                    rightRotation(T, x->parent);
                    w = x->parent->left;
                }

                if(w->right->color == black && w->left->color == black){
                    w->color = red;
                    x = x->parent;
                } else{
                    if(w->left->color == black){
                        w->right->color = black;
                        w->color = red;
                        leftRotation(T, w);
                        w = x->parent->left;
                    }

                    w->color = x->parent->color;
                    x->parent->color = black;
                    w->left->color = black;
                    rightRotation(T, x->parent);
                    x = T->root;
                }

        }

        

        }
        x->color = black;
    }


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

    int getCounterCompare(){
        return counter_compare;
    }

    int getCounterSwitch(){
        return counter_switch;
    }

    ~RBTree(){
        root = clear(root);
    }
};

#endif
