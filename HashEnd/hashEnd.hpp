// Alana Maria Sousa Augusto - 564976
#ifndef HASHEND_HPP
#define HASHEND_HPP

#include<iostream>
#include<vector>
#include <cmath>

using namespace std;

// enum para o status do slot 
enum status{
    EMPTY,
    ACTIVE,
    DELETED
};

template<typename key, typename value>
// struct para o tipo do vetor
struct type{
    pair<key, value> tuple; // chave do tipo par(typename key, typename value)
    status s; // status de cada slot da hash

    // construtor que define cada slot como empty inicialmente
    type(){
        s = EMPTY;
    }
};

template<typename key, typename value, typename hash = hash<key>>
class hashEnd{
private:
    vector<type<key, value>> m_table; // vetor para representar a tabela
    size_t m_tabSize; // tamanho da tabela
    size_t m_numElements; // nº de elementos
    mutable int counter_compare; // contador de comparações de chaves
    int counter_rehash; // contador de rehash

    float m_maxLoad; // define o máximo fator de carga
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

    // função de sondagem baseada em hashing duplo
    size_t sondagem(const key& k, int i) const{ 
        size_t hash1 = m_hash(k) % m_tabSize;
        size_t hash2 = 1 + (m_hash(k) % (m_tabSize-1));
        return (hash1 + (i * hash2)) % m_tabSize;
    }

public:
    // construtor vazio
    hashEnd(size_t size = 10, float maxLoad = 0.75){
        m_tabSize = getNextPrime(size);
        m_numElements = 0;

        if(maxLoad > 0.75){
            m_maxLoad = 0.75;
        } else {
            m_maxLoad = maxLoad;
        }

        m_table.resize(m_tabSize);
        counter_compare = 0;
        counter_rehash = 0;
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
    size_t bucketCount() const{
        return m_tabSize;
    }

    // retorna o fator de carga da hash
    float load_factor() const{
        return static_cast<float>(m_numElements)/m_tabSize;
    }

    // função que procura uma chave na tabela e retorna
    // o índice de sua posição
    int aux_hash_search(const key& k) const{
        size_t i = 0;
        int j;
        do{
            j = sondagem(k, i);
            if(m_table[j].s == ACTIVE && m_table[j].tuple.first == k){
                counter_compare++;
                return j;
            }
            i = i + 1;
        } while (m_table[j].s != EMPTY && i < m_tabSize);
        return -1;
    }

    // procura o valor associado a uma chave na tabela e retorna ele
    const value& hash_search(const key& k) const{
        int j = aux_hash_search(k);
        if(j != -1){
            return m_table[j].tuple.second;
        } else {
            throw out_of_range("key not found");
        }
    }

    // insere um elemento na tabela T
    bool hash_insert(const key& k, const value& v){
        if(load_factor() >= m_maxLoad){
            rehash(2 * m_tabSize);
            counter_rehash++;
        }

        

        int m = aux_hash_search(k);
        if(m != -1){
            m_table[m].tuple.second = v;
            return true;
        }
        size_t i = 0;
        size_t j;
        do{
            j = sondagem(k, i);
            if(m_table[j].s != ACTIVE){
                m_table[j].tuple.first = k;
                m_table[j].tuple.second = v;
                m_table[j].s = ACTIVE;
                m_numElements++;
                return true;
            }
            i++;
        } while (i != m_tabSize);

        return false;
    }

    // deleta um elemento da tabela
    bool hash_delete(const key& k){
        int i = aux_hash_search(k);
        if(i != -1){
            m_table[i].s = DELETED;
            m_numElements--;
            return true;
        } else {
            return false;
        }
    }

    // aumenta o tamanho da tabela e realoca os valores
    // que já estavam previamente na tabela
    void rehash(size_t m){
        size_t new_tabSize = getNextPrime(m);

        if(new_tabSize > m_tabSize){
            vector<type<key, value>> old_vec;
            old_vec = m_table;
            m_table.clear();
            m_table.resize(new_tabSize);
            m_numElements = 0;
            m_tabSize = new_tabSize;
            for(size_t i = 0; i < old_vec.size(); ++i){
                if(old_vec[i].s == ACTIVE){
                    hash_insert(old_vec[i].tuple.first, old_vec[i].tuple.second);
                }
            }

        }

    }

    // função que faz um rehash a fim da tabela conter pelo menos n elementos
    void reserve(size_t n){
        if(n > m_tabSize*m_maxLoad){
            rehash(n/m_maxLoad);
            counter_rehash++;
        }
    }

    // deleta todos os elementos da tabela, marcando todas as
    // posições da hash como vazia
    void clear(){
        for(size_t i = 0; i < m_tabSize; i++){
            if(m_table[i].s == ACTIVE){
                m_table[i].s = EMPTY;
            }
        }
        m_numElements = 0;
    }

    // muda o fator de carga máximo
    void set_max_load_factor(float lf){
        if(lf <= 0 || lf > 0.75){
            throw out_of_range("invalid value");
        }

        m_maxLoad = lf;

        reserve(m_numElements);
    }

    // sobrecarga do operador colchete
    // se k for uma chave da tabela, só retorna seu valor referenciado
    // se k não existir na tabela, k é inserido na tabela
    value& operator[](const key& k){
        if(load_factor() >= m_maxLoad){
            rehash(2*m_tabSize);
            counter_rehash++;
        }

        size_t i = 0;
        size_t j = 0;

        int aux = -1;

        do{
            j = sondagem(k, i);
            if(m_table[j].s == ACTIVE && m_table[j].tuple.first == k){
                counter_compare++;
                aux = j;
                break;
            }
            i = i + 1;
        } while (m_table[j].s != EMPTY && i < m_tabSize);

        if(aux == -1){
            m_table[j].tuple = make_pair(k, value {});
            m_table[j].s = ACTIVE;
            m_numElements++;
            aux = j;
        }

        return m_table[j].tuple.second;
        
    }

    // versão const da sobrecarga do operador colchete
    // retorna o valor associado a chave k
    const value& operator[](const key& k) const{
        size_t i = 0;
        size_t j = 0;

        int aux = -1;

        do{
            j = sondagem(k, i);
            if(m_table[j].s == ACTIVE && m_table[j].tuple.first == k){
                counter_compare++;
                aux = j;
                break;
            }
            i = i + 1;
        } while (m_table[j].s != EMPTY && i < m_tabSize);

        if(aux != -1){
            return m_table[aux].tuple.second;
        }

        throw out_of_range("key doesn't exist in the table");
 
    }  

    // retorna quantas comparações foram feitas
    int getCounterCompare(){
        return counter_compare;
    }

    // retorna quantos rehashs foram feitos
    int getCounterRehash(){
        return counter_rehash;
    }

    // destrutor
    ~hashEnd(){
        clear();
    }


};


#endif