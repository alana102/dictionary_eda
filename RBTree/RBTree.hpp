#ifndef RBTREE_HPP
#define RBTREE_HPP

template <typename k, typename value>

class RBTree{
private:
    // ponteiro para raiz
    Node<k, value>* root;
    // ponteiro para nil
    Node<k, value>* nil;
    // contador de comparações
    int counter_compare;
    // contador de troca de cores
    int counter_switch;

public:

    // construtor vazio
    RBTree(){
        nil = new Node<k, value>(make_pair((),()), nullptr, nullptr, nullptr, black);
        nil->left = nil->right = nil;
        root = nil;
        root->parent = nil;
    }

    // rotação a esquerda
    void leftRotation(RBTree<k, value>* T, Node<k, value>* x){
        Node<k, value> *y = x->right;
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
    void rightRotation(RBTree<k, value>* T, Node<k, value>* x){
        Node<k, value> *y = x->left;
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

    bool search(RBTree<k, value>* T, int key){
        Node<k, value>* aux = T->root;

        // enquanto eu nn chegar em uma folha (nil)
        while(aux != T->nil){

            // verificação do valor da chave para sabe pra onde deslocamos o aux
            if(key < aux->key){
                counter_compare++;
                aux = aux->left;
            } else if (key > aux->key){
                counter_compare++;
                aux = aux->right;
            } else {
                // caso em que a chave já existe na árvore
                return true;
            }
        }

        return false;
    }

    void RBfixup_insert(RBTree<k, value>* T, Node<k, value>* node){

        while(node->parent->color == red){
            // caso em que o tio está do lado direito
            if(node->parent == node->parent->parent->left){
                Node<k, value>* tio = node->parent->parent->right;

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
                Node<k, value>* tio = node->parent->parent->left;

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
        Node<k, value>* aux = T->root;
        Node<k, value>* pai = T->nil;

        // enquanto eu nn chegar em uma folha (nil)
        while(aux != T->nil){
            // vamos deslocar os ponteiros, então pai recebe o que antes era o nó atual
            pai = aux;
            // verificação do valor da chave para sabe pra onde deslocamos o aux
            if(key < aux->key){
                counter_compare++;
                aux = aux->left;
            } else if (key > aux->key){
                counter_compare++;
                aux = aux->right;
            } else {
                // caso em que a chave já existe na árvore
                return;
            }
        }

        // cria novo nó com a chave
        Node<k, value> *z = new Node(key, T->nil, T->nil, nullptr, red);

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
            if(key < pai->key){
                counter_compare++:
                pai->left = z;
            } else {
                pai->right = z;
            }
        }

        // função para ajeitar a árvore mantendo-a como rubro-negra
        // após a inserção
        RBfixup_insert(T, z);
    }

    int blackHeight(){
        int contador = 0;
        Node<k, value>* aux = root;
        while(aux != nil){
            aux = aux->left;
            if(aux->color == black){
                contador++;
            }
        }
        return contador;
    }
};

#endif
