#include "Construcao.h"

// Escolher tres nos aleatorios: 
vector<int> escolher3NosAleatorios(Data data)
{
    int dimensao = data.getDimension();
    //No inicial min e no final max
    int min = 2, max = dimensao;
    
    vector<int> nosAleatorios; 
    //O primeiro no eh o 1 
    nosAleatorios.push_back(1); 
    
    //Gerador de numeros pseudoaleatorios da biblioteca random
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> dist(min, max);

    //Gera tres numeros aleatorios, que serao os nos iniciais 
    for(int i = 0; i < 3; i++)
    {
        nosAleatorios.push_back(dist(gen));
    }

    return nosAleatorios;
}

// Cria o vetor de nos restantes CL:
vector<int> nosRestantes(Data data, vector<int> sequence) {
    int n = data.getDimension();
    vector<int> CL;
    
    vector<bool> utilizado(n + 1, false); 

    for (int i = 0; i < sequence.size(); i++) {
        utilizado[sequence[i]] = true;
    }

    for (int i = 1; i <= n; i++) {
        if (!utilizado[i]) {
            CL.push_back(i);
        }
    } 
    return CL;
}


vector<InsertionInfo> calcularCustoInsercao(Solution& s, vector<int>& CL, Data data)
{
    vector<InsertionInfo> custoInsercao = vector<InsertionInfo>((s.sequence.size() - 1) * CL.size());
    int l = 0;
    for(int a = 0; a < s.sequence.size() - 1; a++) {
        int i = s.sequence[a];
        int j = s.sequence[a + 1];
        for (auto k : CL) {
            // data.getDistance pega a distancia das arestas: 
            custoInsercao[l].custo = data.getDistance(i, k) + data.getDistance(j, k) - data.getDistance(i, j); //c[i][k] + c[j][k] - c[i][j] 
            custoInsercao[l].noInserido = k;
            custoInsercao[l].arestaRemovida = a;
            l++;
        }
    }
    return custoInsercao;
}


void ordenarEmOrdemCrescente(vector<InsertionInfo>& custoInsercao){
    // A função lambda serve para mostrar como o vetor deve ser ordenado
    sort(custoInsercao.begin(), custoInsercao.end(), [](const InsertionInfo &a, const InsertionInfo &b) 
    { return a.custo < b.custo; });
}


void removerDeCL(int selecionado, vector<int>& CL)
{
    for (int i = 0; i < CL.size(); i++) 
    {
        if(CL[i] == selecionado)
        {
            // Apaga o elemento na posição i do vetor CL
            CL.erase(CL.begin() + i); 
            // O break eh para nao rodar o loop apos encontrar o selecionado 
            break;
        }
    }

}


void inserirNaSolucao(Solution* s, InsertionInfo custoInsercao)
{
    s->sequence.insert(s->sequence.begin() + custoInsercao.arestaRemovida, custoInsercao.noInserido);
}

double calculaCustoSolucao(vector<int> sequence, Data data)
{
    int n = sequence.size();
    double cost = 0.0;
    for (int i = 0; i < n-1; i++) {
        cost += data.getDistance(sequence[i], sequence[i+1]);
    }
    cost+= data.getDistance(sequence[n-1], sequence[0]);
    return cost;    
}

Solution Construcao(Data data)
{
    Solution s;
    
    s.custo = 0;
    s.sequence = escolher3NosAleatorios(data);
        
    vector<int> CL = nosRestantes(data, s.sequence); 

    while(!CL.empty()) {
        vector<InsertionInfo> custoInsercao = calcularCustoInsercao(s, CL, data);
        ordenarEmOrdemCrescente(custoInsercao);
        double alpha = (double) rand() / RAND_MAX;
        int selecionado = rand() % ((int) ceil(alpha * custoInsercao.size()));
        removerDeCL(custoInsercao[selecionado].noInserido, CL);
        inserirNaSolucao(&s, custoInsercao[selecionado]);
    }

    s.custo = calculaCustoSolucao(s.sequence, data);
    return s;
}