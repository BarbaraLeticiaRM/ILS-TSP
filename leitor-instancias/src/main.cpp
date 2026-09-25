#include "Data.h"
#include "Construcao.h"

#include <iostream>

using namespace std; 

int main(int argc, char** argv) {

    auto data = Data(argc, argv[1]);
    data.read();
    size_t n = data.getDimension();

    // cout << "Exemplo de Solucao s = ";
    // double cost = 0.0;
    // for (size_t i = 1; i < n; i++) {
    //     cout << i << " -> ";
    //     cost += data.getDistance(i, i+1);
    // }
    // cost += data.getDistance(n, 1);
    // cout << n << " -> " << 1 << endl;
    // cout << "Custo de S: " << cost << endl;

    // TESTES: 
    // Ponto de partida (nós iniciais): 

    Solution sol; 
    // sol.sequence = escolher3NosAleatorios(data);
    // for (int i = 0; i < sol.sequence.size(); i++)
    // {
    //     cout << sol.sequence[i] << "->"; 
    // }
    // cout << endl; 

    

    // // Nós restantes: 
    // vector<int> CL = nosRestantes(data, sol.sequence);
    // cout << "Nos restantes: " << endl;
    // for (int i = 0; i < CL.size(); i++)
    // {
    //     cout << CL[i] << "->"; 
    // }
    // cout << endl;


    // // Custo de Inserção: 
    // vector<InsertionInfo> custoIns = calcularCustoInsercao(sol, CL, data);

    // cout << "Custo Inserção: " << endl; 
    // for (int i = 0; i < custoIns.size(); i++)
    // {
    //     cout << custoIns[i].custo  << "->"; 
    // }
    // cout << endl;

    // ordenarEmOrdemCrescente(custoIns, 0, custoIns.size() - 1); 

    // for (int i = 0; i < custoIns.size(); i++)
    // {
    //     cout << custoIns[i].custo  << "->"; 
    // }
    // cout << endl;

    // double alpha = (double) rand() / RAND_MAX;
    // int selecionado = rand() % ((int) ceil(alpha * custoIns.size()));
    // cout << endl << selecionado << endl;

    sol = Construcao(data); 

    cout << endl << "Solucao: ";
    for(int i=0; i < sol.sequence.size(); i++)
    {
        cout << sol.sequence[i] << "->";
    }

    cout << endl; 


    return 0;
}