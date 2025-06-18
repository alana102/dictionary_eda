#include "AVL/AVL.hpp"
#include "RBTree/RBTree.hpp"
#include "HashEnc/hashEnc.hpp"
#include<iostream>
using namespace std;


int main(){

    AVL<string, int> arv1;
    RBTree<int, int> arv2;
    hashEnc<int, string> hash1;

    arv1.insert(make_pair("alana",3));
    arv1.insert(make_pair("oii",1));
    arv1.insert(make_pair("meudeus",2));
    arv1.insert(make_pair("socorro",2));
    arv1.insert(make_pair("vei",2));

    arv1.print();

    arv2.insert(&arv2, make_pair(1,2));
    arv2.insert(&arv2, make_pair(98,2));
    arv2.insert(&arv2, make_pair(12,2));
    arv2.insert(&arv2, make_pair(11,2));

    arv2.remove(&arv2, make_pair(1,2));
    

    arv1.bshow();

    cout << endl;

    arv2.bshow();

    cout << "Qntd de comparacoes AVL: " << arv1.getCounterCompare() << endl;
    cout << "Qntd de rotacoes AVL: " << arv1.getCounterRotation() << endl;

    cout << endl;

    cout << "Qntd de comparacoes RB: " << arv2.getCounterCompare() << endl;
    cout << "Qntd de troca de cores RB: " << arv2.getCounterSwitch() << endl;



}