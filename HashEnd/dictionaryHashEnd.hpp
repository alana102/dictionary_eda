 #ifndef HASHEND_DICTIONARY
 #define HASHEND_DICTIONARY

 #include "hashEnd.hpp"
 #include<iostream>
 #include<vector>

template<typename key, typename value, typename hash = hash<key>>
class dictionaryHashEnd{
private:

    // dicionário baseado em uma hash por endereçamento aberto
    hashEnd<key, value>* hashTable;

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
    dictionaryHashEnd(size_t size = 10, float maxLoad = 0.75){
        hashTable = new hashEnd<key, value, hash>(size, maxLoad);
        
    }

    // construtor que recebe como parâmetro uma lista de palavras
    // e adicona elas no dicionário 
    dictionaryHashEnd(vector<pair<key, value>>& vec) : dictionaryHashEnd(){
        for(const auto& p : vec){
            hashTable->hash_insert(p.first, p.second);
        }
    }

    // retorna o valor associado a uma chave
    value& get(const key& k){
        return (*hashTable)[k];

    }

    // insere uma palavra no dicionário
    void insert(key k, value v){
        if(hashTable->aux_hash_search(k) != -1){
            update(k, v);
        }
        hashTable->hash_insert(k, v);
    }

    // remove uma palavra no dicionário
    void remove(key k){
        if(hashTable->aux_hash_search(k) == -1){
            throw out_of_range("key doesn't exist already");
        }
        hashTable->hash_delete(k);
    }

    // atualiza o valor associado a uma chave
    void update(key k, value v){
        (*hashTable)[k] = v;
    }

    // retorna quantas palavras estão presentes no dicionário
    int qntPalavras(){
        return hashTable->size();
    }

    // verifica se uma chave existe no dicionário
    bool contains(key k){
        return hashTable->aux_hash_search(k) != -1;
    }

    // limpa toda a tabela
    void clear(){
        hashTable->clear();
    }

    // printa as metricas de comparação e de rehash
    void printMetricas(){
        int compare = hashTable->getCounterCompare();
        int rehash = hashTable->getCounterRehash();

        cout << "Num de comparacoes de chaves: " << compare << "." << endl;
        cout << "Num de rehashs: " << rehash << "." << endl;
    }

};

 #endif