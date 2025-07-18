// ARQUIVO DE TESTE - EXECUTANDO BIBLIA 100 VEZES EM CADA DICIONÀRIO
#include <iostream>
#include "../../include/AVL/dictionaryAVL.hpp"
#include "../../include/RBTree/dictionaryRB.hpp"
#include "../../include/HashEnc/dictionaryHashEnc.hpp"
#include "../../include/HashEnd/dictionaryHashEnd.hpp"
#include <chrono>
#include <fstream>

#include "../dic_utils.hpp"

using namespace std;
using std::chrono::nanoseconds;

int main(){
    // Teste 1: Inserindo 100 vezes um mesmo arquivo em um mesmo dicionário
    ofstream testOut("teste1-biblia.txt");
    if (!testOut.is_open()) {
        cerr << "Erro ao abrir o arquivo de teste" << endl;
        return 1;
    }

    testOut << "Teste 1: Inserindo 100 vezes um mesmo arquivo em um mesmo dicionário" << endl;

    dictionaryAVL<string, int> dicAVL;
    dictionaryRB<string, int> dicRB;
    dictionaryHashEnc<string, int> dicChainedHash;
    dictionaryHashEnd<string, int> dicOpenHash;

    // AVL
    double totalTime = 0.0;

    for (int i = 0; i < 100; i++) {

        auto begin = high_resolution_clock::now(); // define o começo da execução
        ifstream file("../files/kjv-bible.txt");
        cout << "Tentando abrir o arquivo: " << "biblia" << endl;

        if(!file.is_open()){
            cerr << "Falha ao abrir arquivo" << endl;
        }

        string word;
        while(file >> word){
            // desconsidera sinais de pontuação
            word = removePunctuationICU(word);

            // converte todas as letras maiúsculas em minúsculas se houver
            word = toLowerICU(word);

            // ignora palavras vazias
            if (word.empty()) continue;

            if(dicAVL.contains(word)){
                dicAVL.at(word) += 1;
            } else {
                dicAVL.insert(word, 1);
            }

        }
        file.close();
        auto end = high_resolution_clock::now(); // define o fim da execução
        auto duracao = duration_cast<nanoseconds>(end - begin); // armazena o tempo total de execução em nanossegundos

        totalTime += duracao.count() / 1e9; // converte para segundos
    }

    double avgTime = totalTime / 100.0;

    testOut << "Tempo médio de execução AVL para BIBLIA: " << avgTime << " segundos" << endl;

    // RB
    totalTime = 0;

    for (int i = 0; i < 100; i++) {
        
        auto begin = high_resolution_clock::now(); // define o começo da execução
        ifstream file("../files/kjv-bible.txt");
        cout << "Tentando abrir o arquivo: " << "biblia" << endl;

        if(!file.is_open()){
            cerr << "Falha ao abrir arquivo" << endl;
        }

        string word;
        while(file >> word){
            // desconsidera sinais de pontuação
            word = removePunctuationICU(word);

            // converte todas as letras maiúsculas em minúsculas se houver
            word = toLowerICU(word);

            // ignora palavras vazias
            if (word.empty()) continue;

            if(dicRB.contains(word)){
                dicRB.at(word) += 1;
            } else {
                dicRB.insert(word, 1);
            }

        }
        file.close();
        auto end = high_resolution_clock::now(); // define o fim da execução
        auto duracao = duration_cast<nanoseconds>(end - begin); // armazena o tempo total de execução em nanossegundos

        totalTime += duracao.count() / 1e9; // converte para segundos
    }

    avgTime = totalTime / 100;

    testOut << "Tempo médio de execução RB para BIBLIA: " << avgTime << " segundos" << endl;

    // Hash Encadeada
    totalTime = 0;

    for (int i = 0; i < 100; i++) {
        
        auto begin = high_resolution_clock::now(); // define o começo da execução
        ifstream file("../files/kjv-bible.txt");
        cout << "Tentando abrir o arquivo: " << "biblia" << endl;

        if(!file.is_open()){
            cerr << "Falha ao abrir arquivo" << endl;
        }

        string word;
        while(file >> word){
            // desconsidera sinais de pontuação
            word = removePunctuationICU(word);

            // converte todas as letras maiúsculas em minúsculas se houver
            word = toLowerICU(word);

            // ignora palavras vazias
            if (word.empty()) continue;

            if(dicChainedHash.contains(word)){
                dicChainedHash.at(word) += 1;
            } else {
                dicChainedHash.insert(word, 1);
            }

        }
        file.close();
        auto end = high_resolution_clock::now(); // define o fim da execução
        auto duracao = duration_cast<nanoseconds>(end - begin); // armazena o tempo total de execução em nanossegundos

        totalTime += duracao.count() / 1e9; // converte para segundos
    }

    avgTime = totalTime / 100;

    testOut << "Tempo médio de execução ChainedHash para BIBLIA: " << avgTime << " segundos" << endl;

    // Hash Aberta
    totalTime = 0;

    for (int i = 0; i < 100; i++) {
        
        auto begin = high_resolution_clock::now(); // define o começo da execução
        ifstream file("../files/kjv-bible.txt");
        cout << "Tentando abrir o arquivo: " << "biblia" << endl;

        if(!file.is_open()){
            cerr << "Falha ao abrir arquivo" << endl;
        }

        string word;
        while(file >> word){
            // desconsidera sinais de pontuação
            word = removePunctuationICU(word);

            // converte todas as letras maiúsculas em minúsculas se houver
            word = toLowerICU(word);

            // ignora palavras vazias
            if (word.empty()) continue;

            if(dicOpenHash.contains(word)){
                dicOpenHash.at(word) += 1;
            } else {
                dicOpenHash.insert(word, 1);
            }

        }
        file.close();
        auto end = high_resolution_clock::now(); // define o fim da execução
        auto duracao = duration_cast<nanoseconds>(end - begin); // armazena o tempo total de execução em nanossegundos

        totalTime += duracao.count() / 1e9; // converte para segundos
    }

    avgTime = totalTime / 100;

    testOut << "Tempo médio de execução OpenHash para BIBLIA: " << avgTime << " segundos" << endl;

    testOut.close();
    return 0;



}