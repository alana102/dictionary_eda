#include "AVL/dictionaryAVL.hpp"
#include "RBTree/dictionaryRB.hpp"
#include "HashEnc/dictionaryHashEnc.hpp"
#include<iostream>
using namespace std;


int main(){

    cout << "AVL:" << endl;
    dictionaryAVL<string, int> dic1;
    dic1.insert("alana", 2);
    dic1.insert("alana", 3);
    dic1.insert("clara", 4);
    dic1.insert("guilherme", 4);
    cout << "Qntd de palavras: " << dic1.qntPalavras() << "." << endl;
    dic1.remove("guilherme");
    cout << "Qntd de palavras: " << dic1.qntPalavras() << "." << endl;
    dic1.printMetricas();
    dic1.contains("guilherme")? cout << "true" << endl : cout << "false" << endl;

    cout << "RB:" << endl;
    dictionaryRB<string, int> dic2;
    dic2.insert("alana", 2);
    dic2.insert("alana", 3);
    dic2.insert("clara", 4);
    dic2.insert("guilherme", 4);
    cout << "Qntd de palavras: " << dic2.qntPalavras() << "." << endl;
    dic2.remove("guilherme");
    cout << "Qntd de palavras: " << dic2.qntPalavras() << "." << endl;
    dic2.printMetricas();
    dic2.contains("guilherme")? cout << "true" << endl : cout << "false" << endl;

    cout << "hashEnc:" << endl;
    dictionaryHashEnc<string, int> dic3;
    dic3.insert("alana", 2);
    dic3.insert("alana", 3);
    dic3.insert("clara", 4);
    dic3.insert("guilherme", 4);
    cout << "Qntd de palavras: " << dic3.qntPalavras() << "." << endl;
    dic3.remove("guilherme");
    cout << "Qntd de palavras: " << dic3.qntPalavras() << "." << endl;
    dic3.printMetricas();
    dic3.contains("guilherme")? cout << "true" << endl : cout << "false" << endl;




}