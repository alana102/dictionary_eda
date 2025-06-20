#ifndef HASHENC_HPP
#define HASHENC_HPP

#include<vector>
#include<list>
#include<cmath>

using namespace std;

template <typename key, typename value, typename hash = hash<key>>
class hashEnc{

private:

    size_t m_numElements;
    size_t m_tabSize;

    float m_maxLoad;

    vector<list<pair<key, value>>> m_table;

    hash m_hash;

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

    size_t hashCode(const key& k) const {
        return m_hash(k) % m_tabSize;
    }


public:

    // construtor vazio
    hashEnc(size_t size = 19){
        m_numElements = 0;
        m_tabSize = getNextPrime(size);
        m_table.resize(m_tabSize);
        m_maxLoad = 1;
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
         }

         int slot = hashCode(k);

         // for-each (para cada elemento da lista do slot)
         for(auto p : m_table[slot]){
            if(p.first == k){
               return false;
            }
         }

         m_table[slot].push_back[make_pair(k, v)];
         m_numElements++; 

         return true;
     }

     // verifica se uma chave k está presente na tabela
     bool contains(const key& k){
        int slot = hashCode(k);

        for(auto p : m_table[slot]){
            if(p.first == k){
                return true;
            }
        }

        return false;
     }

     // retorna a chave associada a chave k na tabela
     value& at(const key& k){

        if(!contains(k)){
            throw out_of_range("invalid key");
        }

        int slot = hash_code(k);

        for(auto p : m_table[slot]){
            if(p.first == k){
                return p.second;
            }
        }

     }

    /**
     * @brief Recebe um inteiro nao negativo m e faz com que o tamanho
     * da tabela seja um numero primo maior ou igual a m.
     * Se m for maior que o tamanho atual da tabela, um rehashing eh realizado.
     * Se m for menor que o tamanho atual da tabela, a funcao nao tem nenhum efeito.
     * Um rehashing eh uma operacao de reconstrucao da tabela:
     * Todos os elementos no container sao rearranjados de acordo 
     * com o seu valor de hashing dentro na nova tabela.
     * Isto pode alterar a ordem de iteracao dos elementos dentro do container.
     * Operacoes de rehashing sao realizadas automaticamente pelo container 
     * sempre que load_factor() ultrapassa o m_max_load_factor.
     * 
     * @param m := o novo tamanho da tabela hash
     */
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

    void reserve(size_t n){
        if(n > m_tabSize*m_maxLoad){
            rehash(n/m_maxLoad);
        } else {
            return;
        }
    }

    // remove um elemento de chave k da tabela
    bool remove(const key& k) {
        if(!contains(k)){
            return false;
        }

        int slot = hashCode(k);

        for(auto it = m_table[slot].begin(); it != m_table[slot].end(); ++it) {
            if(it->first == k){
                m_table[slot].erase(it);
                return true;
            }
        }   

        return false;
    
    }

    // muda o fator de carga máximo
    void set_max_load_factor(float lf){
        if(lf < 0){
            throw out_of_range("invalid value");
        }

        m_maxLoad = lf;

        reserve(m_numElements);
    }

    /**
     * @brief Sobrecarga do operador de indexacao.
     * Se k corresponder a chave de um elemento na tabela, a funcao
     * retorna uma referencia ao seu valor mapeado. Caso contrario, 
     * se k nao corresponder a chave de nenhum elemento na tabela, 
     * a funcao insere um novo elemento com essa chave e retorna um
     * referencia ao seu valor mapeado. Observe que isso sempre aumenta 
     * o tamanho da tabela em um, mesmo se nenhum valor mapeado for atribuido 
     * ao elemento (o elemento eh construido usando seu construtor padrao).
     * 
     * @param k := chave
     * @return Value& := valor associado a chave
     */
    value& operator[](const key& k){
        size_t slot = hashCode(k);
        for (auto& par : m_table(slot)){
           if(par.first == k){
              return par.second;
           }
        }
        m_table[slot].push_back({k, value{}});
        m_numElements++;
        return m_table[slot].back().second;
    }


    /**
     * @brief Versao const da sobrecarga do operador de indexacao.
     * Se k corresponder a chave de um elemento na tabela, a funcao
     * retorna uma referencia ao seu valor mapeado. Caso contrario, 
     * se k nao corresponder a chave de nenhum elemento na tabela, 
     * a funcao lanca uma out_of_range exception.
     * 
     * @param k := chave
     * @return Value& := valor associado a chave
     */
    const value& operator[](const key& k) const{
        return at(k);
    }

     

     // destrutor
    ~hashEnc(){
        clear();
    }



};

#endif