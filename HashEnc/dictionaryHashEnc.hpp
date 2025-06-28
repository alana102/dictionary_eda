 #ifndef HASHENCAVL
 #define HASHENCAVL

 #include "hashEnc.hpp"
 #include<iostream>
 #include<vector>

template<typename key, typename value>
class dictionaryHashEnc{
private:

    hashEnc<key, value> hashTable;

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
    dictionaryHashEnc(){
        
    }

    // construtor que recebe como parâmetro uma lista de palavras
    // e adicona elas no dicionário (desserializa)
    dictionaryHashEnc(vector<pair<key, value>>& vec){
        for(size_t i = 0; i < vec.size(); i++){
            hashTable.add(vec.at(i).first, vec.at(i).second);
        }
    }

    void insert(key k, value v){
        if(hashTable.contains(k)){
            //update(k, v);
        }
        hashTable.add(k, v);
    }

    void remove(key k){
        if(!hashTable.contains(k)){
            throw out_of_range("key doesn't exist already");
        }
        hashTable.remove(k);
    }

    /*void update(key k, value v){

    }*/

    // retorna quantas palavras estão presentes no dicionário
    int qntPalavras(){
        return hashTable.size();
    }

    // verifica se uma chave existe no dicionário
    bool contains(key k){
        return hashTable.contains(k);
    }

    void printMetricas(){
        int compare = hashTable.getCounterCompare();
        int rehash = hashTable.getCounterRehash();

        cout << "Num de comparacoes de chaves: " << compare << "." << endl;
        cout << "Num de rehashs: " << rehash << "." << endl;
    }

};

 #endif