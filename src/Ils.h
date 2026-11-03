#ifndef ILS_H
#define ILS_H
#include "Perturbacao.h"
#include <chrono>

Solution ILS(int maxIter, int maxIterIls, Data data);

void resolveILS(int maxIter, int maxIterIls, Data data, double* tempoMedio, double* custoMedio, int n); 

void imprimeSolucao(Solution sol);






#endif