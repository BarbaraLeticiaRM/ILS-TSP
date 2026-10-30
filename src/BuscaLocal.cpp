#include "BuscaLocal.h"

bool bestImprovementSwap(Solution *s, Data data)
{
    double bestDelta = 0;
    int best_i, best_j;

    for(int i = 1; i < s->sequence.size() - 1; i++)
    {
        int vi = s->sequence[i];
        int vi_next = s->sequence[i + 1];
        int vi_prev = s->sequence[i - 1];

        for(int j = i + 1; j < s->sequence.size() - 1; j++)
        {
            int vj = s->sequence[j];
            int vj_next = s->sequence[j + 1];
            int vj_prev = s->sequence[j - 1];
            double delta = 0;

            // Se os nos forem adjacentes
            if (j == i + 1) {
                delta = - data.getDistance(vi_prev, vi) 
                        - data.getDistance(vi, vj) 
                        - data.getDistance(vj, vj_next)
                        + data.getDistance(vi_prev, vj) 
                        + data.getDistance(vj, vi) 
                        + data.getDistance(vi, vj_next);
            } 

            // Se os nos forem nao-adjacentes
            else {
                delta = - data.getDistance(vi_prev, vi) - data.getDistance(vi, vi_next) 
                        - data.getDistance(vj_prev, vj) - data.getDistance(vj, vj_next)
                        + data.getDistance(vi_prev, vj) + data.getDistance(vj, vi_next)
                        + data.getDistance(vj_prev, vi) + data.getDistance(vi, vj_next);
            }
            if (delta < bestDelta)
            {
                bestDelta = delta;
                best_i = i;
                best_j = j;
            }

        }

    }
    if(bestDelta < 0)
    {
        swap(s->sequence[best_i], s->sequence[best_j]);
        s->custo = s->custo + bestDelta;
        return true;
    }
    return false;
}


void swap_edges(vector<int> &path, int i, int j) {
    i += 1;

    // Inverte o vetor de i a j
    while (i < j) {
        swap(path[i] , path[j]);
        i++;
        j--;
    }
}

bool bestImprovement2Opt(Solution *s, Data data)
{
    double bestDelta = 0;
    int best_i, best_j;    

    for (int i = 0; i < s->sequence.size() - 1; i++) {
        int vi = s->sequence[i];
        int vi_next = s->sequence[i + 1];
        for (int j = i + 2; j < s->sequence.size() - 1; j++) {
            int vj = s->sequence[j];
            int vj_next = s->sequence[j + 1];

            float delta = - data.getDistance(vi, vi_next) - data.getDistance(vj, vj_next) 
                          + data.getDistance(vi, vj) + data.getDistance(vi_next, vj_next);  
            
            if (delta < bestDelta) {
                bestDelta = delta;
                best_i = i;
                best_j = j;
            }
        }
    }

    if(bestDelta < 0)
    {
        swap_edges(s->sequence, best_i, best_j);
        s->custo = s->custo + bestDelta;
        return true;
    }
    return false;
}

void reinsertion(vector<int> &path, int i, int j, int tamanho) 
{
    // Validações de segurança
    if (tamanho <= 0 || i < 0 || j < 0 || i + tamanho > path.size() || j > path.size()) {
        return; 
    }
    
    // Ignora se a posição de destino cai no meio do próprio bloco extraído ou no mesmo lugar
    if (j >= i && j <= i + tamanho) {
        return; 
    }

    // Movimentação usando rotate
    if (i < j) {
        // Movendo o bloco para a frente (direita)
        rotate(path.begin() + i, path.begin() + i + tamanho, path.begin() + j);
    } else {
        // Movendo o bloco para trás (esquerda)
        rotate(path.begin() + j, path.begin() + i, path.begin() + i + tamanho);
    }
}



bool bestImprovementOrOpt(Solution *s, int tamanho, Data data)
{
    double bestDelta = 0;
    int best_i, best_j;    

    for (int i = 1; i < s->sequence.size() - tamanho; i++) {

        int antes_i = s->sequence[i-1]; 
        int vi = s->sequence[i];
        int depois_bloco = s->sequence[i + tamanho];
        int fim_bloco = s->sequence[i + tamanho - 1];

        for (int j = i + tamanho; j < s->sequence.size() - 1; j++) {

            int vj = s->sequence[j];
            int depois_j = s->sequence[j + 1];

            float delta = - data.getDistance(vi, antes_i) - data.getDistance(fim_bloco, depois_bloco) + data.getDistance(antes_i, depois_bloco) 
                          - data.getDistance(vj, depois_j) + data.getDistance(vi, vj ) + data.getDistance(fim_bloco, depois_j);  
            
            if (delta < bestDelta) {
                bestDelta = delta;
                best_i = i;
                best_j = j+1;
            }
        }
    }

    if(bestDelta < 0)
    {
        reinsertion(s->sequence, best_i, best_j, tamanho);
        s->custo = s->custo + bestDelta;
        return true;
    }
    return false;    
}

void BuscaLocal(Solution *s, Data data)
{
    vector<int> NL = {1, 2, 3, 4, 5};
    bool improved = false;

    while (NL.empty() == false)
    {
        int n = rand() % NL.size();
        switch (NL[n])
        {
            case 1:
                improved = bestImprovementSwap(s, data);
                break;

            case 2:
                improved = bestImprovement2Opt(s, data);
                break;

            case 3:
                improved = bestImprovementOrOpt(s, 1, data); // Reinsertion
                break;

            case 4:
                improved = bestImprovementOrOpt(s, 2, data); // Or-opt2
                break;

            case 5:
                improved = bestImprovementOrOpt(s, 3, data); // Or-opt3
                break;
        }

        if (improved)
            NL = {1, 2, 3, 4, 5};
        else
            NL.erase(NL.begin() + n);
    }
}