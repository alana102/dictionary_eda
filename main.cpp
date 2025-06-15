#include "AVL/AVL.hpp"
#include "RBTree/RBTree.hpp"
#include<iostream>
using namespace std;


int main(){

    AVL<int, int> arv1;
    RBTree<int, int> arv2;

    arv1.insert(make_pair(12,3));
    arv1.insert(make_pair(7,1));
    arv1.insert(make_pair(6,2));
    arv1.insert(make_pair(1,2));
    arv1.insert(make_pair(0,2));

    arv2.insert(&arv2, make_pair(1,2));
    arv2.insert(&arv2, make_pair(98,2));
    arv2.insert(&arv2, make_pair(12,2));
    arv2.insert(&arv2, make_pair(11,2));

    arv1.erase(make_pair(6,2));
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