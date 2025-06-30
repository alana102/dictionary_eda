 #ifndef DICTIONARYAVL
 #define DICTIONARYAVL

 #include "AVL.hpp"
 #include<iostream>
 #include<vector>

template<typename key, typename value>
class dictionaryAVL{
private:

    AVL<key, value>* avlTree;

public:

    /*
    Funcionalidades:
    Criação -> criar um dicionário vazio ou com pares iniciais OK
    Inserção -> inserir um novo par no dicionário OK
    Atualização -> modificar o valor de uma chave OK
    Acesso -> recuperar o valor associado a uma chave OK
    Remoção -> remover um par usando a chave OK
    Verificar existência -> verifica se a chave existe OK
    Iteração -> percorre os pares ?
    Tamanho -> retorna nº de pares OK
    Limpeza -> remove todos os pares OK
    */

    // construtor vazio
    dictionaryAVL(){
        avlTree = new AVL<key, value>();
    }

    // construtor que recebe como parâmetro uma lista de palavras
    // e adicona elas no dicionário 
    dictionaryAVL(vector<pair<key, value>>& vec) : dictionaryAVL(){
        for(const auto& p : vec){
            avlTree->insert(p);
        }
    }

    // insere uma palavra no dicionário
    void insert(key k, value v){
        avlTree->insert(make_pair(k, v));
    }

    // remove uma palavra do dicionário
    void remove(key k){
        if(!avlTree->contains(k)){
            throw out_of_range("key doesn't exist already");
        }
        avlTree->erase(make_pair(k, value {}));
    }

    // atualiza o valor de uma chave no dicionário
    void update(key k, value v){
        avlTree->insert(make_pair(k, v));
    }

    // retorna quantas palavras estão presentes no dicionário
    int qntPalavras(){
        return avlTree->size();
    }

    // verifica se uma chave existe no dicionário
    bool contains(key k){
        return avlTree->contains(k);
    }

    // retorna o valor associado a uma chave
    value& at(const key& k){
        return avlTree->at(k);
    }

    // limpa todo o dicionário
    void clear(){
        avlTree->clear();
    }

    // printa todas as palavras do dicionário em ordem alfabética
    void printDic(){
        avlTree->print();
    }

    // printa as métricas de comparação e de rotação
    void printMetricas(){
        int compare = avlTree->getCounterCompare();
        int rotation = avlTree->getCounterRotation();

        cout << "Num de comparacoes de chaves: " << compare << "." << endl;
        cout << "Num de rotacoes: " << rotation << "." << endl;
    }

};

 #endif