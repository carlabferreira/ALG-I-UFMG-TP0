//---------------------------------------------------------------------
// Arquivo	: tp0.cpp
// Conteudo	: implementacao do TP0
// Autor	: Carla Ferreira
// Historico	: 2024-03-22 - arquivo criado
//                2024-03-30 - edição do modo de armazenagem dos numeros aleatorios para ter
//                             50 arquivos salvos
//                2024-04-01 - (...)
//---------------------------------------------------------------------

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <vector>
#include <string>
#include <chrono>
#include <thread>
#include "fibonacci.hpp"
#include "ordenacao.hpp"

using namespace std;
using namespace std::chrono;

void geraAleatorios(int qtddNumeros, ofstream&  arquivo, int i);
void criarArquivos(int qtddArquivos, int qtddNumeros);
vector<int> leArquivo(string nomeArquivo);
void criaVetoresIguaisParaOrdenacao (int qtddArquivos, int qtddNumeros);
void ContaTempoRecursivo (int tempoLimite);

void SegundosFibonacci ();

int main() {
    srand(time(0));

    //Inicializando variáveis
    int op;
    int qtddArquivos = 50;
    int qtddNumeros = 10000;

    cout << "Selecione a opcao:" << endl;
    cout << "(0) gerar conjunto de numeros aleatorios" << endl
         << "(1) Ordenacao" << endl
         << "(2) Fibonacci" << endl;

    cin >> op;

    if (op == 0) criarArquivos(qtddArquivos, qtddNumeros);
    else if (op == 1) criaVetoresIguaisParaOrdenacao(qtddArquivos, qtddNumeros);
    else if (op == 2) SegundosFibonacci();
    else cout << "opcao inválida!" << endl;

    return 0;
}


void criaVetoresIguaisParaOrdenacao (int qtddArquivos, int qtddNumeros){
    string nomeArquivo;
    vector<int> dados;
    vector<int> vetorCopia;

    //Tempo marcado em milissegundos
    int tempoQRP = 0; // QuickSort Recursivo Puro
    int tempoQRI = 0; // QuickSort Recursivo Com Insercao
    int tempoQNRP = 0; // QuickSort Não Recursivo Puro
    int tempoQNRI = 0; // QuickSort Não Recursivo Com Insercao


    for (int i = 1; i <= qtddArquivos; i++){
        nomeArquivo = "arq/arquivo" + to_string(i) + ".txt";
        dados = leArquivo(nomeArquivo);
        
        // ---------- QuickSort Recursivo Puro ---------- 
        vetorCopia.assign(dados.begin(), dados.end());
        time_point start = high_resolution_clock::now();
        QuicksortRecursivoPuro(vetorCopia, 0, vetorCopia.size() - 1);
        time_point stop = high_resolution_clock::now();
        milliseconds duration = duration_cast<milliseconds>(stop - start);
        tempoQRP += (int) duration.count();
        //cout << "v na main: " << endl;
        //printaVector(vetorCopia);

        // ---------- QuickSort Recursivo Com Insercao ----------
        vetorCopia.assign(dados.begin(), dados.end());
        start = high_resolution_clock::now();
        QuicksortRecursivo_InsertionSort(vetorCopia, 0, vetorCopia.size()-1);
        stop = high_resolution_clock::now();
        duration = duration_cast<milliseconds>(stop - start);
        tempoQRI += (int) duration.count();

        // ---------- QuickSort Não Recursivo Puro ----------
        vetorCopia.assign(dados.begin(), dados.end());
        start = high_resolution_clock::now();
        QuicksortNaoRecursivoPuro(vetorCopia);
        stop = high_resolution_clock::now();
        duration = duration_cast<milliseconds>(stop - start);
        tempoQNRP += (int) duration.count();

        // ---------- QuickSort Não Recursivo Com Insercao ----------
        vetorCopia.assign(dados.begin(), dados.end());
        start = high_resolution_clock::now();
        QuicksortNaoRecursivo_InsertionSort(vetorCopia);
        stop = high_resolution_clock::now();
        duration = duration_cast<milliseconds>(stop - start);
        tempoQNRI += (int) duration.count();

        //cout << "tempo QRP do arquivo "<< i << "= " << duration << endl;
        //cout << "menor = " << vetorCopia[0] << endl;
    }
    cout << "tempo QRP " << tempoQRP << endl;
    cout << "tempo QRI " << tempoQRI << endl;
    cout << "tempo QNRP " << tempoQNRP << endl;
    cout << "tempo QNRI " << tempoQNRI << endl;

    cout << "media de temp QRP = " << ((float)(tempoQRP))/(qtddArquivos*1.0) << endl;
    cout << "media de temp QRI = " << ((float)(tempoQRI))/(qtddArquivos*1.0) << endl;
    cout << "media de temp QNRP = " << ((float)(tempoQNRP))/(qtddArquivos*1.0) << endl;
    cout << "media de temp QNRI = " << ((float)(tempoQNRI))/(qtddArquivos*1.0) << endl;
}


void printaVector (vector<int> V){
    for (int i = 0; i < (int)V.size(); i++){
        cout << V[i] << ' ';
    }
    cout << endl;
}

