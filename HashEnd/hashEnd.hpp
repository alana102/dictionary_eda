#ifndef HASHEND
#define HASHEND
#include<iostream>
#include<vector>
#include<cmath>
#include<functional>

#define empty 0
#define active 1
#define deleted 2

template<typename key, typename value>
struct type{
    key k;
    value v;
    int status;

    type(){
        status = empty;
    }
};

template<typename key, typename value>
class hashEnd{
private:
    vector<type> m_table;
    size_t m_capacity;
    size_t m_size;

    Hash m_hash;

    size_t sondagem(){
        
    }

public:

    hashEnd(){

    }

};


#endif