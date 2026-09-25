#ifndef CONSTRUCAO_H
#define CONSTRUCAO_H

#include "Data.h"
#include <iostream>
#include <vector>
#include <cmath>
#include <random>

struct InsertionInfo
{
    int noInserido; // no k a ser inserido
    int arestaRemovida; // aresta {i,j} na qual o no k sera inserido
    double custo; // delta ao inserir k na aresta {i,j}
};

struct Solution
{
    vector<int> sequence; // Sequencia de nos da solucao  
};

vector<int> escolher3NosAleatorios(Data data);
vector<int> nosRestantes(Data data, vector<int> sequence);
vector<InsertionInfo> calcularCustoInsercao(Solution& s, vector<int>& CL, Data data);
void merge(vector<InsertionInfo>& vetor, int esquerda, int mid, int direita);
void ordenarEmOrdemCrescente(vector<InsertionInfo>& custoInsercao, int esquerda, int direita);
void inserirNaSolucao(Solution* s, InsertionInfo custoInsercao);
void removerDeCL(int selecionado, vector<int>& CL);
Solution Construcao(Data data);

#endif