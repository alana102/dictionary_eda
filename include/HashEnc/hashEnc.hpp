// Alana Maria Sousa Augusto - 564976
#ifndef HASHENC_HPP
#define HASHENC_HPP

#include<vector>
#include<list>
#include<cmath>
#include "../compare.hpp"

using namespace std;

template <typename key, typename value, typename hash = hash<key>>
class hashEnc{

private:

    size_t m_numElements; // nº de elementos da tabela
    size_t m_tabSize; // tamanho da tabela
    mutable int counterCompare; // contador de comparações
    int counterRehash; // contador de rehash

    float m_maxLoad; // define o máximo fator de carga

    // objeto que compara strings com acento
    CollatorCompare<key> compare;

    vector<list<pair<key, value>>> m_table; // vetor de lista de pares que representa a tabela

    hash m_hash; // objeto da classe hash para gerenciar operações na tabela

    // retorna o próximo nº primo
    size_t getNextPrime(size_t size){
        if(size <= 2) return 3;
        size = (size % 2 == 0) ? size + 1 : size;

        bool notPrime = true;

        while(notPrime) {
            notPrime = false;
            for(int i = 3; i <= sqrt(size); i+=2){
                if(size % i == 0){
                    notPrime = true;
                    break;
                }
            }
            size+=2;
        }
        return size-2;
    }

    // função de hashCode que determina para qual slot uma chave será mapeada
    size_t hashCode(const key& k) const {
        return m_hash(k) % m_tabSize;
    }


public:

    // construtor vazio
    hashEnc(size_t size = 10, float maxLoad = 1){
        m_numElements = 0;
        m_tabSize = getNextPrime(size);
        m_table.resize(m_tabSize);

        if(maxLoad > 1){
            m_maxLoad = 1;
        } else {
            m_maxLoad = maxLoad;
        }

        counterCompare = 0;
        counterRehash = 0;
    }

    // retorna quantos elementos tem na tabela
    size_t size() const{
        return m_numElements;
    }

    // verifica se a tabela está vazia ou não
    bool empty() const{
        return m_numElements == 0;
    }

    // retorna quantos slots tem na hash
    size_t bucketCount(){
        return m_tabSize;
    }

    // retorna o tamanho da lista do slot n
    size_t bucketSize(size_t n) const{
        if(n < 0 || n >= m_tabSize){
            throw out_of_range("invalid index");
        }

        return m_table[n].size();
    }

    // retorna o slot para onde a chave k é mapeada
    size_t bucket(const key& k) const{
        return hashCode(k);
    }

    // retorna o fator de carga da hash
    float load_factor() const{
        return static_cast<float>(m_numElements)/m_tabSize;
    }

    // retorna o maior valor que o fator de carga pode assumir
    float max_load_factor() const{
        return m_maxLoad;
    }

    // limpa a tabela inteira
    void clear(){
        for(size_t i = 0; i < m_tabSize; i++){
            m_table[i].clear();
        }

        m_numElements = 0;
    }

    // adiciona um elemento na tabela, caso sua chave já não esteja presente
    bool add(const key& k, const value& v){
        if (load_factor() >= m_maxLoad) {
            rehash(2*m_tabSize);
            counterRehash++;
        }

         size_t slot = hashCode(k);

         // for-each (para cada elemento da lista do slot)
         for(auto p : m_table[slot]){
            counterCompare++;
            if(!compare(p.first, k) && !compare(k, p.first)){
                return false;
            }
         }

         m_table[slot].push_back(make_pair(k, v));
         m_numElements++; 

         return true;
     }

     // verifica se uma chave k está presente na tabela
     bool contains(const key& k){
        size_t slot = hashCode(k);

        for(auto& p : m_table[slot]){
            counterCompare++;
            if(!compare(p.first, k) && !compare(k, p.first)){
                return true;
            }
        }

        return false;
     }

     // retorna a chave associada a chave k na tabela
     value& at(const key& k){
        size_t slot = hashCode(k);

        for(auto& p : m_table[slot]){
            counterCompare++;
            if(!compare(p.first, k) && !compare(k, p.first)){
                return p.second;
            }
        }

        throw out_of_range("invalid key");

     }

    // versão const da função at
    const value& at(const key& k) const{
        size_t slot = hashCode(k);

        for(auto& p : m_table[slot]){
            counterCompare++;
            if(!compare(p.first, k) && !compare(k, p.first)){
                return p.second;
            }
        }

        throw out_of_range("invalid key");
    }


   
    // aumenta o tamanho da tabela para o próximo número primo maior ou igual a m
    // caso m seja maior que o tamanho original da tabela
    void rehash(size_t m){
      size_t new_tabSize = getNextPrime(m);
        if(new_tabSize > m_tabSize) {
            vector<list<pair<key, value>>> old_vec;
            old_vec = m_table; // copia as chaves para uma nova tabela
            m_table.clear(); // apaga todas as chaves da tabela atual e deixa ela vazia
            m_table.resize(new_tabSize); // tabela redimensionada com novo primo
            m_numElements = 0;
            m_tabSize = new_tabSize;
            for(size_t i = 0; i < old_vec.size(); ++i) {
                for(auto& par : old_vec[i]) {
                    add(par.first, par.second);
                }
                old_vec[i].clear(); // opcional
            }            
        }
    }

    // função que faz um rehash a fim da tabela conter pelo menos n elementos
    void reserve(size_t n){
        if(n > m_tabSize*m_maxLoad){
            rehash(n/m_maxLoad);
            counterRehash++;
        }
    }

    // remove um elemento de chave k da tabela
    bool remove(const key& k) {
        if(!contains(k)){
            return false;
        }

        size_t slot = hashCode(k);

        for(auto it = m_table[slot].begin(); it != m_table[slot].end(); ++it) {
            counterCompare++;
            if(!compare(it->first, k) && !compare(k, it->first)){
                m_table[slot].erase(it);
                m_numElements--;
                return true;
            }
        }   

        return false;
    
    }

    // muda o fator de carga máximo
    void set_max_load_factor(float lf){
        if(lf <= 0 || lf > 1){
            throw out_of_range("invalid value");
        }

        m_maxLoad = lf;

        reserve(m_numElements);
    }

    // printa todos os valores da hash
    void print(){
        for (size_t i = 0; i < m_table.size(); ++i) {
            for (auto& p : m_table[i]) {
                std::cout << "(" << p.first << ", " << p.second << ") ";
            }
        }
        cout << endl;
    }

    // retorna quantas comparações foram feitas
    int getCounterCompare(){
        return counterCompare;
    }

    // retorna quantos rehashs foram feitos
    int getCounterRehash(){
        return counterRehash;
    }
 
    // sobrecarga do operador colchete
    // se k for uma chave da tabela, só retorna seu valor referenciado
    // se k não existir na tabela, k é inserido na tabela
    value& operator[](const key& k){
        if(load_factor() >= m_maxLoad){
            rehash(2*m_tabSize);
            counterRehash++;
        }
        size_t slot = hashCode(k);
        for (auto& par : m_table[slot]){
            counterCompare++;
            if(!compare(par.first, k) && !compare(k, par.first)){
                return par.second;
            }
        }
        m_table[slot].push_back({k, value{}});
        m_numElements++;
        return m_table[slot].back().second;
    }

    // versão const da sobrecarga do operador colchete
    // retorna o valor associado a chave k
    const value& operator[](const key& k) const{
        return at(k);
    }   

     // destrutor
    ~hashEnc(){
        clear();
        counterCompare = 0;
        counterRehash = 0;
    }



};

#endif