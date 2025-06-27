 #ifndef DICTIONARYRB
 #define DICTIONARYRB

 #include "RBTree.hpp"
 #include<iostream>
 #include<vector>

template<typename key, typename value>
class dictionaryRB{
private:

    RBTree<key, value> rbTree;

public:

    /*
    Funcionalidades:
    Criação -> criar um dicionário vazio ou com pares iniciais OK
    Inserção -> inserir um novo par no dicionário OK
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
    dictionaryRB(){
        
    }

    // construtor que recebe como parâmetro uma lista de palavras
    // e adicona elas no dicionário (desserializa)
    dictionaryRB(vector<pair<key, value>>& vec){
        for(size_t i = 0; i < vec.size(); i++){
            rbTree.insert(vec.at(i));
        }
    }

    // insere uma palavra e um valor associado a ela no dicionário
    void insert(key k, value v){
        if(rbTree.contains(k)){
            //update(k, v)
        }
        rbTree.insert(make_pair(k, v));
    }

    // deleta uma palavra do dicionário
    void remove(key k){
        if(!rbTree.contains(k)){
            throw out_of_range("key doesn't exist already");
        }
        rbTree.remove(k);
    }

    /*void update(key k, value v){

    }*/

    // retorna quantas palavras estão presentes no dicionário
    int qntPalavras(){
        return rbTree.size();
    }

    // verifica se uma palavra existe no dicionário
    bool contains(key k){
        return rbTree.contains(k);
    }

    // printa as métricas
    void printMetricas(){
        int compare = rbTree.getCounterCompare();
        int rotation = rbTree.getCounterRotation();

        cout << "Num de comparacoes de chaves: " << compare << "." << endl;
        cout << "Num de rotacoes: " << rotation << "." << endl;
    }

};

#endif