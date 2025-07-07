#include "include/AVL/dictionaryAVL.hpp"
#include "include/RBTree/dictionaryRB.hpp"
#include "include/HashEnc/dictionaryHashEnc.hpp"
#include "include/HashEnd/dictionaryHashEnd.hpp"
#include<iostream>
#include<vector>

using namespace std;

// arquivo de teste

int main(){

    // vetor para passar como parâmetro no construtor
    vector<pair<string, int>> vec;
    vec.push_back(make_pair("casa", 3));
    vec.push_back(make_pair("vaga", 3));
    vec.push_back(make_pair("amada", 3));
    vec.push_back(make_pair("vida", 3));
    vec.push_back(make_pair("mundo", 3));
    vec.push_back(make_pair("tomada", 3));
    vec.push_back(make_pair("gente", 3));
    vec.push_back(make_pair("povo", 3));
    vec.push_back(make_pair("oculos", 3));
    vec.push_back(make_pair("esmalte", 3));
    vec.push_back(make_pair("jesus", 3));
    vec.push_back(make_pair("deus", 3));
    vec.push_back(make_pair("papel", 3));

    // testes AVL
    cout << "AVL:" << endl;
    dictionaryAVL<string, int> dic1(vec);
    dic1.insert("alana", 2);
    dic1.insert("alana", 3);
    dic1.update("alana", dic1.at("alana")+2);
    dic1.insert("clara", 4);
    dic1.insert("guilherme", 4);
    cout << "Qntd de palavras: " << dic1.qntPalavras() << "." << endl;
    dic1.printDic();
    dic1.remove("guilherme");
    cout << "Qntd de palavras: " << dic1.qntPalavras() << "." << endl;
    dic1.printDic();
    dic1.printMetricas();
    dic1.contains("guilherme")? cout << "true" << endl : cout << "false" << endl;
    dic1.clear();
    cout << "Qntd de palavras: " << dic1.qntPalavras() << "." << endl;
    cout << "\n";

    // testes Rubro-Negra
    cout << "RB:" << endl;
    dictionaryRB<string, int> dic2(vec);
    dic2.insert("alana", 2);
    dic2.insert("alana", 3);
    dic2.insert("clara", 4);
    dic2.insert("guilherme", 4);
    cout << "Qntd de palavras: " << dic2.qntPalavras() << "." << endl;
    dic2.printDic();
    dic2.remove("guilherme");
    cout << "Qntd de palavras: " << dic2.qntPalavras() << "." << endl;
    dic2.printDic();
    dic2.printMetricas();
    dic2.contains("guilherme")? cout << "true" << endl : cout << "false" << endl;
    dic2.clear();
    cout << "Qntd de palavras: " << dic2.qntPalavras() << "." << endl;
    cout << "\n";

    // testes Hash por Encadeamento Exterior
    cout << "hashEnc:" << endl;
    dictionaryHashEnc<string, int> dic3(vec);
    dic3.insert("alana", 2);
    dic3.insert("alana", 3);
    dic3.insert("clara", 4);
    dic3.insert("guilherme", 4);
    cout << "Qntd de palavras: " << dic3.qntPalavras() << "." << endl;
    dic3.printDic();
    dic3.remove("guilherme");
    cout << "Qntd de palavras: " << dic3.qntPalavras() << "." << endl;
    dic3.printDic();
    dic3.printMetricas();
    dic3.contains("guilherme")? cout << "true" << endl : cout << "false" << endl;
    dic3.clear();
    cout << "Qntd de palavras: " << dic3.qntPalavras() << "." << endl;
    cout << "\n";

    // testes Hash por Endereçamento Aberto
    cout << "hashEnd:" << endl; 
    dictionaryHashEnd<string, int> dic4(vec);
    dic4.insert("alana", 2);
    dic4.insert("alana", 3);
    dic4.insert("clara", 4);
    dic4.insert("guilherme", 4);
    cout << "Qntd de palavras: " << dic4.qntPalavras() << "." << endl;
    dic4.printDic();
    dic4.remove("guilherme");
    cout << "Qntd de palavras: " << dic4.qntPalavras() << "." << endl;
    dic4.printDic();
    dic4.printMetricas();
    dic4.contains("guilherme")? cout << "true" << endl : cout << "false" << endl;
    dic4.clear();
    cout << "Qntd de palavras: " << dic4.qntPalavras() << "." << endl;


}