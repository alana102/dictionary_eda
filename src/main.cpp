#include <iostream>
#include <fstream>

#include "../include/AVL/dictionaryAVL.hpp"
#include "../include/RBTree/dictionaryRB.hpp"
#include "../include/HashEnc/dictionaryHashEnc.hpp"
#include "../include/HashEnd/dictionaryHashEnd.hpp"

using namespace std;

int main(int argc, char* argv[]) {

    // verifica se o usuário passou apenas 3 argumentos
    if(argc != 3){
        cerr << "Digite apenas 3 argumentos" << endl;
        return 1;
    }

    // armazena a estrutura que será utilizada
    string structure = argv[1];
    // armazena o nome do arquivo
    string file = argv[2];

    
    if(structure == "avl_tree"){
        cout << "avl selecionada" << endl;
    } else if (structure == "red_black_tree") {
        cout << "rubro negra selecionada" << endl;

    } else if (structure == "chained_hash_table") {
        cout << "hash por encadeamento exterior selecionada" << endl;
        
    } else if (structure == "open_hash_table") {
        cout << "hash por endereçamento aberto selecionada" << endl;

    } else {
        cerr << "Digite um nome de estrutura válido" << endl;
        return 1;
    }
    

    return 0;
}
