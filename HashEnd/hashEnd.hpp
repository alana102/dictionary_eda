// Alana Maria Sousa Augusto - 564976
#ifndef HASHEND
#define HASHEND
#include<iostream>
#include<vector>

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
    pair<key, value> tuple;
    status s;

    type(){
        s = EMPTY;
    }
};

template<typename key, typename value, typename hash = hash<key>>
class hashEnd{
private:
    vector<type<key, value>> m_table;
    size_t m_tabSize; // tamanho da tabela
    size_t m_numElements; // nº de elementos
    int counter_compare; // contador de comparações de chaves

    float m_maxLoad; 
    hash m_hash;

    // função de sondagem baseada em hashing duplo
    size_t sondagem(const key& k, int i){ // rever depois
        return (m_hash(k) % m_tabSize) + (i * (1 + (m_hash(k) % m_tabSize-1)));
    }

public:
    // construtor vazio
    hashEnd(size_t size = 10){
        m_tabSize = size;
        m_numElements = 0;
        m_maxLoad = 0.5;
        m_table.resize(m_tabSize);
        counter_compare = 0;
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

    // retorna o slot pra qual slot a chave k é mapeada
    size_t bucket(const key& k, int i) const{
        return sondagem(k, i);
    }

    // retorna o fator de carga da hash
    float load_factor() const{
        return static_cast<float>(m_numElements)/m_tabSize;
    }

    // função que procura uma chave na tabela e retorna
    // o índice de sua posição
    int aux_hash_search(const key& k){
        int i = 0;
        int j;
        do{
            j = sondagem(k, i);
            if(m_table[j].s == ACTIVE && m_table[j].tuple.first == k){
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
        int m = aux_hash_search(k);
        if(m != -1){
            m_table[m].tuple.second = v;
            return true;
        }
        int i = 0;
        int j;
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
        } while (i < m_tabSize);

        return false;
    }

    // deleta um elemento da tabela
    bool hash_delete(const key& k){
        int i = aux_hash_search(k);
        if(i != -1){
            m_table[i].s = DELETED;
            return true;
        } else {
            return false;
        }
    }

    /*
    rehash
    reserve
    sobrecarregar operadores
    métrica adicional
    incrementar counter compare
    clear
    destrutor
    avl: arrumar insert/update
    */

    




};


#endif