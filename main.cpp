#include "AVL/AVL.hpp"
#include "RBTree/RBTree.hpp"
#include<iostream>
using namespace std;


int main(){

    AVL<int, int> arv1;

    arv1.insert(make_pair(12, 3));
    arv1.insert(make_pair(7,1));
    arv1.insert(make_pair(1,2));

    arv1.bshow();

    cout << "Qntd de comparacoes: " << arv1.getCounterCompare() << endl;
    cout << "Qntd de rotacoes: " << arv1.getCounterRotation() << endl;



}