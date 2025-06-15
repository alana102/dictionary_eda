// Alana Maria Sousa Augusto - 564976
#ifndef HASHENC_HPP
#define HASHENC_HPP

#include<vector>
#include<list>

using namespace std;

template<typename key, typename value, typename hash = hash<key>>

class hash_t{
   
private: 
     size_t m_numElements;
     size_t m_tabSize;

     float m_maxLoad;

     vector<list<pair<key, value>> m_table;

     hash m_hash;

     // fazer função do próximo primo
     size_t getNextPrime(size_t size){

     }

     size_t hash_code(const key& k) const{
         return m_hash(k) % m_tabsize;
     }

public:

     // construtor
     hash_t(size_t tsize = 19){
        m_numElements = 0;
        m_tabSize = getNextPrime(tsize);
        m_table.resize(m_tabSize);
        m_maxLoad = 1;
     }

     size_t size() const{
        return m_numElements;
     }

     bool empty() const{
        return m_numElements == 0;
     }

     size_t bucket count() const{
        return m_tabSize;
     }

     size_t bucket_size(size_t n) const{
        if(n < 0 || n >= m_tabSize){
            throw out_of_range("invalid index");
        }

        return m_table[n].size();
     }
};


#endif