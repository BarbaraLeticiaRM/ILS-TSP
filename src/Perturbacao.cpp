#include "Perturbacao.h"

Solution Perturbacao(Solution s, Data data)
{
    Solution sol = s;

    int V = sol.sequence.size(); 

    if (V < 4) {
        return sol;
    }

    int tam_max = ceil(V/10); 

    bool flag = false; 

    int tam1, tam2, start1, start2; 
    while(flag == false)
    {
        // x + rand() % (y - x + 1)
        tam1 = 2 + rand() % (tam_max - 1);
        tam2 = 2 + rand() % (tam_max - 1);

        start1 = rand() % (V - tam1 + 1);

        vector<int> posicoes_start2; 
        
        // Espaco antes do start1 
        if(start1 >= tam2)
        {
            for (int i = 0; i <= start1 - tam2; i++) 
            {
                posicoes_start2.push_back(i);
            }
        }

        // Espaco depois do start1
        if(V - (start1 + tam1) >= tam2)
        {
            for (int i = start1 + tam1; i <= V - tam2; i++) 
            {
                posicoes_start2.push_back(i);
            }
        }

        // Se houver posições válidas, sorteia o segundo

        if (!posicoes_start2.empty()) {
            int idx = rand() % (posicoes_start2.size() - 1);
            start2 = posicoes_start2[idx];
            flag = true; 
        }
        else 
            flag = false; 
    }

    // Identifica quem vem primeiro para facilitar a reconstrução
    int start_a, tam_a, start_b, tam_b;
    if (start1 < start2) {
        start_a = start1; tam_a = tam1;
        start_b = start2; tam_b = tam2;
    } else {
        start_a = start2; tam_a = tam2;
        start_b = start1; tam_b = tam1;
    }

    vector<int> nova_solucao;
    nova_solucao.reserve(V); // Otimização de alocação de memória
    
    // Início até o começo do segmento A
    for (int i = 0; i < start_a; i++) nova_solucao.push_back(sol.sequence[i]);
    
    // Inserir Segmento B no lugar do A
    for (int i = start_b; i < start_b + tam_b; i++) nova_solucao.push_back(sol.sequence[i]);
    
    // O meio entre o segmento A e o segmento B
    for (int i = start_a + tam_a; i < start_b; i++) nova_solucao.push_back(sol.sequence[i]);
    
    // Inserir Segmento A no lugar do B
    for (int i = start_a; i < start_a + tam_a; i++) nova_solucao.push_back(sol.sequence[i]);
    
    // Do final do segmento B até o final do vetor
    for (int i = start_b + tam_b; i < V; i++) nova_solucao.push_back(sol.sequence[i]);
    
    sol.sequence = nova_solucao; 

    sol.custo = calculaCustoSolucao(sol.sequence, data);  


    return sol; 
}
