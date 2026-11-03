#include "Ils.h"

Solution ILS(int maxIter, int maxIterIls, Data data)
{

    Solution bestOfAll;
    bestOfAll.custo = INFINITY;

    for(int i = 0; i < maxIter; i++)
    {
        Solution s = Construcao(data);
        Solution best = s;
        int iterIls = 0;

        while(iterIls <= maxIterIls)
        {
            BuscaLocal(&s, data);

            if(s.custo < best.custo)
            {
                best = s;
                iterIls = 0;
            }

            s = Perturbacao(best, data);
            iterIls++;  
        }

        if (best.custo < bestOfAll.custo)
            bestOfAll = best;

    }

    return bestOfAll;
}

void resolveILS(int maxIter, int maxIterIls, Data data, double* tempoMedio, double* custoMedio, int n)
{

    Solution sol; 

    chrono::duration<double> tempoTotal;    
    double custoTotal = 0; 

    for (int i = 0; i < 10; i++)
    {
        auto inicio = chrono::steady_clock::now();

        sol = ILS(maxIter, maxIterIls, data); 

        auto fim = chrono::steady_clock::now();

        chrono::duration<double> tempo_decorrido = fim - inicio;

        custoTotal += sol.custo;
        tempoTotal += tempo_decorrido; 
    }

    *tempoMedio = tempoTotal.count()/10; 
    *custoMedio = custoTotal/10.0; 

} 


void imprimeSolucao(Solution sol)
{
    for (int i = 0; i < sol.sequence.size(); i++)
    {
        cout << sol.sequence[i]  << "->"; 
    }
    cout << sol.sequence[0] << endl; 
    cout << endl << sol.custo << endl; 
}