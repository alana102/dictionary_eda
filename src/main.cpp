#include <iostream>

#include "../include/AVL/dictionaryAVL.hpp"
#include "../include/RBTree/dictionaryRB.hpp"
#include "../include/HashEnc/dictionaryHashEnc.hpp"
#include "../include/HashEnd/dictionaryHashEnd.hpp"

#include "dic_utils.hpp"

using namespace std;

int main(int argc, char* argv[]) {

    // verifica se o usuário passou 4 argumentos
    if(argc != 4){
        cerr << "Digite 4 argumentos" << endl;
        how_to_use();
        return 1;
    }

    // armazena a estrutura que será utilizada
    string structure = argv[1];
    // armazena o nome do arquivo a ser lido
    string file_in = argv[2];
    // armazena o nome do arquivo que será criado
    string file_out = argv[3];

    
    if(structure == "dicAVL"){
        cout << "avl selecionada" << endl;
        dictionaryAVL<string, int> dicAVL;
        executeDic(file_in, dicAVL, file_out, structure);
    } else if (structure == "dicRB") {
        cout << "rubro negra selecionada" << endl;
        dictionaryRB<string, int> dicRB;
        executeDic(file_in, dicRB, file_out, structure);
    } else if (structure == "dicChainedHash") {
        cout << "hash por encadeamento exterior selecionada" << endl;
        dictionaryHashEnc<string, int> dicHashEnc;
        executeDic(file_in, dicHashEnc, file_out, structure);
    } else if (structure == "dicOpenHash") {
        cout << "hash por endereçamento aberto selecionada" << endl;
        dictionaryHashEnd<string, int> dicHashEnd;
        executeDic(file_in, dicHashEnd, file_out, structure);
    } else {
        cerr << "Digite um nome de estrutura válido" << endl;
        how_to_use();
        return 1;
    }
    

    return 0;
}
