 #ifndef DICTIONARYRB
 #define DICTIONARYRB

 #include "RBTree.hpp"
 #include<iostream>
 #include<vector>

template<typename key, typename value>
class dictionaryRB{
private:

    RBTree<key, value>* rbTree;

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
    dictionaryRB(){
        rbTree = new RBTree<key, value>();
    }

    // construtor que recebe como parâmetro uma lista de palavras
    // e adicona elas no dicionário
    dictionaryRB(vector<pair<key, value>>& vec) : dictionaryRB(){
        for(const auto& p : vec){
            rbTree->insert(p);
        }
    }

    // insere uma palavra e um valor associado a ela no dicionário
    void insert(key k, value v){
        rbTree->insert(make_pair(k, v));
    }

    // deleta uma palavra do dicionário
    void remove(key k){
        if(!rbTree->search(k)){
            throw out_of_range("key doesn't exist already");
        }
        rbTree->remove(k);
    }

    // atualiza o valor de uma palavra
    void update(key k, value v){
        rbTree->insert(make_pair(k, v));
    }

    // retorna o valor associado a uma palavra
    value& get(const key& k){
        return rbTree->at(k);
    }

    // retorna quantas palavras estão presentes no dicionário
    int qntPalavras(){
        return rbTree->size();
    }

    // verifica se uma palavra existe no dicionário
    bool contains(key k){
        return rbTree->search(k);
    }

    // limpa o dicionário
    void clear(){
        rbTree->clear();
    }

    // printa as métricas de comparação e de rotação
    void printMetricas(){
        int compare = rbTree->getCounterCompare();
        int rotation = rbTree->getCounterRotation();

        cout << "Num de comparacoes de chaves: " << compare << "." << endl;
        cout << "Num de rotacoes: " << rotation << "." << endl;
    }

};

#endif