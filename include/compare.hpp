// Alana Maria Sousa Augusto
#ifndef COMPARE_HPP
#define COMPARE_HPP
#include <unicode/unistr.h>
#include <unicode/coll.h>     
#include <unicode/locid.h>    
#include <iostream>

using namespace icu;
using namespace std;

// arquivo auxiliar com funções que comparam dois valores distintos de string
// com acentos, utilizando o collator da biblioteca unicode 
template <typename T>
struct CollatorCompare {
    Collator* coll;

    // construtor, define o collator em português e cria ele
    CollatorCompare(const Locale& locale = Locale("pt_BR")) {
        UErrorCode status = U_ZERO_ERROR;
        coll = Collator::createInstance(locale, status);
        if (U_FAILURE(status)) {
            cerr << "Erro ao criar Collator: " << u_errorName(status) << endl;
            coll = nullptr;
        }
    }

    // sobrecarga do operador parênteses
    // retorna true se "a" atenceder "b" e false caso contrário
    bool operator()(const T& a, const T& b) const {
        if (!coll) return false;

        UnicodeString ua = UnicodeString::fromUTF8(a);
        UnicodeString ub = UnicodeString::fromUTF8(b);

        return coll->compare(ua, ub) < 0;
    }

        // destrutor
    ~CollatorCompare() {
        delete coll;
    }
};

#endif
