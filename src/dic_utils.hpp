#ifndef DIC_UTILS
#define DIC_UTILS

#include <unicode/unistr.h>
#include <unicode/locid.h>
#include <unicode/uchar.h>
#include <fstream>
#include <string>
#include <streambuf>
#include <iostream>
#include <iomanip>
#include <chrono>

using namespace std;
using namespace icu;
using namespace chrono;

// função que remove as pontuações
string removePunctuationICU(const string& input) {
    UnicodeString ustr = UnicodeString::fromUTF8(input);
    UnicodeString result;

    for (int i = 0; i < ustr.length(); ++i) {
        UChar32 c = ustr.char32At(i);
        if (u_isalpha(c) || u_isdigit(c)) {
            result.append(c);
        } else if (c == '-') {
            // verifica se o hífen está entre letras/dígitos
            bool validBefore = (i > 0) && (u_isalpha(ustr.char32At(i - 1)) || u_isdigit(ustr.char32At(i - 1)));
            bool validAfter  = (i + 1 < ustr.length()) && (u_isalpha(ustr.char32At(i + 1)) || u_isdigit(ustr.char32At(i + 1)));
            if (validBefore && validAfter) {
                result.append(c);
            }
        }
    }

    string output;
    result.toUTF8String(output);
    return output;
}

// função que transforma todos os caracteres maiúsculos em minúsculo se houver
string toLowerICU(const string& input) {
    UnicodeString ustr = UnicodeString::fromUTF8(input);
    ustr.toLower(Locale("pt_BR"));
    string result;
    ustr.toUTF8String(result);
    return result;
}

// função que salva os valores do dicionário em um arquivo .txt
template <typename Dictionary>
void saveToFile(Dictionary& dic, const string& file_out, const string& file_in, const string& structure, nanoseconds time){
    streambuf* coutBuf = cout.rdbuf();

    string file_out2 = "results/"+file_out; 
    ofstream outFile(file_out2);
    if (!outFile.is_open()) {
        cerr << "Erro ao abrir arquivo para salvar saída\n";
        return;
    }

    cout.rdbuf(outFile.rdbuf());

    cout << "======================= INFORMAÇÕES GERAIS =======================" << endl;
    cout << "Dicionário do arquivo: " << file_in << endl;
    cout << "Estrutura utilizada: " << structure << endl;
    cout << "Quantidade de palavras distintas: " << dic.qntPalavras() << endl;
    cout << "========================== ESTATÍSTICAS ==========================" << endl;
    dic.printMetricas();
    cout << "Tempo de construção do dicionário: " << time.count() / 1e9 << " segundos " << endl;
    cout << "==================================================================" << endl;
    cout << endl;

    const int larguraPalavra = 51;
    const int larguraFreq = 12;

    cout << "+" << string(larguraPalavra, '-') << "+" << string(larguraFreq, '-') << "+\n";
    cout << "| " << left << setw(larguraPalavra - 1) << "Palavra" << "| " << setw(larguraFreq - 1) << "Frequência " << "|\n";

    dic.printDic();


    cout.rdbuf(coutBuf);

    outFile.close();
}

// função que lê um arquivo e popula o dicionário
// adicionando chaves e atualizando seus valores de acordo
// com as ocorrências das palavras no arquivo .txt
template <typename Dictionary>
// mudar para void dps dnv
void executeDic(string file_in, Dictionary& dic, string file_out, string structure){
    auto begin = high_resolution_clock::now(); // define o começo da execução
    ifstream file(file_in);
    cout << "Tentando abrir o arquivo: " << file_in << endl;

    if(!file.is_open()){
        cerr << "Falha ao abrir arquivo" << endl;
        return;
    }

    string word;
    while(file >> word){
        // desconsidera sinais de pontuação
        word = removePunctuationICU(word);

        // converte todas as letras maiúsculas em minúsculas se houver
        word = toLowerICU(word);

        // ignora palavras vazias
        if (word.empty()) continue;

        if(dic.contains(word)){
            dic.at(word) += 1;
        } else {
            dic.insert(word, 1);
        }

    }
    file.close();
    auto end = high_resolution_clock::now(); // define o fim da execução
    auto duracao = duration_cast<nanoseconds>(end - begin); // armazena o tempo total de execução em nanossegundos

    saveToFile(dic, file_out, file_in, structure, duracao);

}

// função chamada sempre que o usuário digita algo errado no terminal
// explicando o passo-a-passo para executar este projeto
void how_to_use(){
    cout << "Para executar o programa digite algo como:" << endl;
    cout << ".\\programa.exe structure_type file_in file_out" << endl;
    cout << "Valores válidos para 'structure_type': dicAVL, dicRB, dicChainedHash, dicOpenHash" << endl;
    cout << "Valores válidos para 'file_in': qualquer nome de arquivo presente no projeto com a estensão .txt" << endl;
    cout << "Valores válidos para 'file_out': qualquer nome que deseje" << endl;
}

#endif