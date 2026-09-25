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

    //O ultimo no eh o 1 
    nosAleatorios.push_back(1); 

    return nosAleatorios;
}

// Cria o vetor de nos restantes CL:
vector<int> nosRestantes(Data data, vector<int> sequence)
{
    int n = data.getDimension();
    vector<int> CL;

    // Cria um vetor de booleanos 
    vector<bool> utilizado;

    // Preenchendo o veltor 'utilizado' com false
    for (int i = 0; i < n; i++)
    {
        utilizado.push_back(false);
    }

    // Marca os nos que ja estão na sequencia como true 
    for (int i = 0; i < sequence.size(); i++)
    {
        utilizado[sequence[i]] = true;
    }

    // Adiciona ao CL apenas os nos que continuam false
    for (int i = 1; i <= n; i++)
    {
        if (!utilizado[i])
        {
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


// Para ordenação utilizei o metodo mergesort (codigo do geeksForGeeks)
void merge(vector<InsertionInfo>& vetor, int esquerda, int mid, int direita){
                         
    int n1 = mid - esquerda + 1;
    int n2 = direita - mid;

    // Cria vetores temporários E (esquerda) e D (direita)
    vector<InsertionInfo> E(n1), D(n2);

    // Copia os dados para os vetores temporários E e D 
    for (int i = 0; i < n1; i++)
        E[i] = vetor[esquerda + i];
    for (int j = 0; j < n2; j++)
        D[j] = vetor[mid + 1 + j];

    int i = 0, j = 0;
    int k = esquerda;

    // Merge: 
    while (i < n1 && j < n2) {
        if (E[i].custo <= D[j].custo) {
            vetor[k] = E[i];
            i++;
        }
        else {
            vetor[k] = D[j];
            j++;
        }
        k++;
    }

    // Copia os elementos restantes de E (se houver)
    while (i < n1) {
        vetor[k] = E[i];
        i++;
        k++;
    }

    // Copia os elementos restantes de D (se houver)
    while (j < n2) {
        vetor[k] = D[j];
        j++;
        k++;
    }
}


void ordenarEmOrdemCrescente(vector<InsertionInfo>& custoInsercao, int esquerda, int direita){
    
    // Caso base
    if (esquerda >= direita)
        return;

    // Lógica do MergeSort 
    int meio = esquerda + (direita - esquerda) / 2;
    ordenarEmOrdemCrescente(custoInsercao, esquerda, meio);
    ordenarEmOrdemCrescente(custoInsercao, meio + 1, direita);
    merge(custoInsercao, esquerda, meio, direita);
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
    // Insere o no selecionado no lugar da aresta removida  
    s->sequence.insert(s->sequence.begin() + custoInsercao.arestaRemovida, custoInsercao.noInserido);
}


Solution Construcao(Data data)
{
    Solution s;

    s.sequence = escolher3NosAleatorios(data);
    
    vector<int> CL = nosRestantes(data, s.sequence); 

    while(!CL.empty()) {
        vector<InsertionInfo> custoInsercao = calcularCustoInsercao(s, CL, data);
        ordenarEmOrdemCrescente(custoInsercao, 0, custoInsercao.size() - 1);
        double alpha = (double) rand() / RAND_MAX;
        int selecionado = rand() % ((int) ceil(alpha * custoInsercao.size()));
        // O primeiro no eh fixo (1)
        if(custoInsercao[selecionado].arestaRemovida != 0 )
        {
            removerDeCL(custoInsercao[selecionado].noInserido, CL);
            inserirNaSolucao(&s, custoInsercao[selecionado]);
        }
    }
    return s;
}