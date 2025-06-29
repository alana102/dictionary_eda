 #ifndef HASHEND_DICTIONARY
 #define HASHEND_DICTIONARY

 #include "hashEnd.hpp"
 #include<iostream>
 #include<vector>

template<typename key, typename value>
class dictionaryHashEnd{
private:

    hashEnd<key, value> hashTable;

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
    dictionaryHashEnd(){
        
    }

    // construtor que recebe como parâmetro uma lista de palavras
    // e adicona elas no dicionário (desserializa)
    dictionaryHashEnd(vector<pair<key, value>>& vec){
        for(size_t i = 0; i < vec.size(); i++){
            hashTable.add(vec.at(i).first, vec.at(i).second);
        }
    }

    void insert(key k, value v){
        if(hashTable.aux_hash_search(k) != -1){
            update(k, v);
        }
        hashTable.hash_insert(k, v);
    }

    void remove(key k){
        if(hashTable.aux_hash_search(k) == -1){
            throw out_of_range("key doesn't exist already");
        }
        hashTable.hash_delete(k);
    }

    void update(key k, value v){
        hashTable[k] = v;
    }

    // retorna quantas palavras estão presentes no dicionário
    int qntPalavras(){
        return hashTable.size();
    }

    // verifica se uma chave existe no dicionário
    bool contains(key k){
        return hashTable.aux_hash_search(k) != -1;
    }

    void printMetricas(){
        int compare = hashTable.getCounterCompare();
        int rehash = hashTable.getCounterRehash();

        cout << "Num de comparacoes de chaves: " << compare << "." << endl;
        cout << "Num de rehashs: " << rehash << "." << endl;
        cout << hashTable["alana"] << endl;
    }

};

 #endif