#include<iostream>
using namespace std;

int main(int argc, char* argv[]){
    cout << "num de parametros = " << argc << endl;
    for (int i = 0; i < argc; ++i){
        cout << argv[i] << endl;
    }
}