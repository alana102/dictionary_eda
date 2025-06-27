#include "AVL/dictionaryAVL.hpp"
#include<iostream>
using namespace std;


int main(){

    cout << "AVL:" << endl;
    dictionaryAVL<string, int> dic1;
    dic1.insert("alana", 2);
    dic1.insert("clara", 4);
    dic1.insert("guilherme", 4);
    dic1.contains("guilherme")? cout << "true" << endl : cout << "false" << endl;
    dic1.printMetricas();




}