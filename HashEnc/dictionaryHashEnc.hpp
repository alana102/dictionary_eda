 // Alana Maria Sousa Augusto - 564976
 #ifndef HASHENC_DICTIONARY
 #define HASHENC_DICTIONAY

 #include "hashEnc.hpp"
 #include<iostream>
 #include<vector>

template<typename key, typename value, typename hash = hash<key>>
class dictionaryHashEnc{
private:

    // dicionário baseado em uma hash por encadeamento exterior
    hashEnc<key, value>* hashTable;

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
    dictionaryHashEnc(){
        hashTable = new hashEnc<key, value, hash>();
    }

    // construtor que recebe como parâmetro uma lista de palavras
    // e adicona elas no dicionário 
    dictionaryHashEnc(vector<pair<key, value>>& vec) : dictionaryHashEnc(){
        for(const auto& p : vec){
            hashTable->add(p.first, p.second);
        }
    }

    // retorna o valor associado a uma chave
    value& get(const key& k){
        return (*hashTable)[k];

    }

    // insere uma palavra no dicionário
    void insert(key k, value v){
        if(hashTable->contains(k)){
            update(k, v);
        }
        hashTable->add(k, v);
    }

    // remove uma palavra do dicionário
    void remove(key k){
        if(!hashTable->contains(k)){
            throw out_of_range("key doesn't exist already");
        }
        hashTable->remove(k);
    }

    // atualiza o valor associado a uma palavra
    void update(key k, value v){
        (*hashTable)[k] = v;
    }

    // retorna quantas palavras estão presentes no dicionário
    int qntPalavras(){
        return hashTable->size();
    }

    // verifica se uma chave existe no dicionário
    bool contains(key k){
        return hashTable->contains(k);
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