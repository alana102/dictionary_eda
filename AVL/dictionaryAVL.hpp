 #ifndef DICTIONARYAVL
 #define DICTIONARYAVL

 #include "AVL.hpp"
 #include<iostream>
 #include<vector>

template<typename key, typename value>
class dictionaryAVL{
private:

    AVL<key, value> avlTree;

public:

    /*
    Funcionalidades:
    Criação -> criar um dicionário vazio ou com pares iniciais OK
    Inserção -> inserir um novo par no dicionário OK
    Atualização -> modificar o valor de uma chave
    Acesso -> recuperar o valor associado a uma chave
    Remoção -> remover um par usando a chave OK
    Verificar existência -> verifica se a chave existe OK
    Iteração -> percorre os pares
    Tamanho -> retorna nº de pares OK
    Limpeza -> remove todos os pares
    */

    /*
    //Função em pré-ordem que vai lendo uma stringstream
    //e gerando os nós da árvore
    Node* desserializa(std::stringstream ss){
        std::string token;
        ss>>token;
        if(token=="#"){
            return nullptr;
        }else{
            int val=std::stoi(token);
            Node *aux=new Node(val, nullptr, nullptr);
        }
    }
    */

    // construtor vazio
    dictionaryAVL(){
        
    }

    // construtor que recebe como parâmetro uma lista de palavras
    // e adicona elas no dicionário (desserializa)
    dictionaryAVL(vector<pair<key, value>>& vec){
        for(size_t i = 0; i < vec.size(); i++){
            avlTree.insert(vec.at(i));
        }
    }

    void insert(key k, value v){
        if(avlTree.contains(k)){
            //update(k, v);
        }
        avlTree.insert(make_pair(k, v));
    }

    void remove(key k){
        if(!avlTree.contains(k)){
            throw out_of_range("key doesn't exist already");
        }
        avlTree.erase(make_pair(k, value {}));
    }

    /*void update(key k, value v){

    }*/

    // retorna quantas palavras estão presentes no dicionário
    int qntPalavras(){
        return avlTree.size();
    }

    // verifica se uma chave existe no dicionário
    bool contains(key k){
        return avlTree.contains(k);
    }

    void printMetricas(){
        int compare = avlTree.getCounterCompare();
        int rotation = avlTree.getCounterRotation();

        cout << "Num de comparacoes de chaves: " << compare << "." << endl;
        cout << "Num de rotacoes: " << rotation << "." << endl;
    }

};

 #endif