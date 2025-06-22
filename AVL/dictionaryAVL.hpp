 #ifndef DICTIONARYAVL
 #define DICTIONARYAVL

 #include "AVL.hpp"
 #include<iostream>

class dictionaryAVL{
private:

    AVL<string, int> avlTree;

public:

    /*
    Funcionalidades:
    Criação -> criar um dicionário vazio ou com pares iniciais
    Inserção -> inserir um novo par no dicionário
    Atualização -> modificar o valor de uma chave
    Acesso -> recuperar o valor associado a uma chave
    Remoção -> remover um par usando a chave
    Verificar existência -> verifica se a chave existe
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
    dictionaryAVL(){

    }

    // retorna quantas palavras estão presentes no dicionário
    int qntPalavras(){
        return avlTree.size();
    }

    bool contains(string key){
        return avlTree.contains(key);
    }

};

 #endif