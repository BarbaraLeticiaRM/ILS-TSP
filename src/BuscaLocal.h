#ifndef BUSCALOCAL_H
#define BUSCALOCAL_H

#include "Construcao.h"

bool bestImprovementSwap(Solution *s, Data data); 
void swap_edges(vector<int> &path, int i, int j);
bool bestImprovement2Opt(Solution *s, Data data); 
void reinsertion(vector<int> &path, int i, int j, int tamanho);
bool bestImprovementOrOpt(Solution *s, int tamanho, Data data); 
void BuscaLocal(Solution *s, Data data); 

#endif
