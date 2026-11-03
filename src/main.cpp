#include "Data.h"
#include "Construcao.h"
#include "BuscaLocal.h"
#include "Perturbacao.h"
#include "Ils.h"
#include <iostream>

using namespace std; 


int main(int argc, char** argv) {

    auto data = Data(argc, argv[1]);
    data.read();
    size_t n = data.getDimension();

    int maxIter = 50; 
    int maxIterIls;
    int nExecucoes = 1; 
    double tempoMedio, custoMedio; 

    if(n >= 150){
        maxIterIls = n/2;
    }
    else{
        maxIterIls = n; 
    }

    resolveILS(maxIter, maxIterIls, data, &tempoMedio, &custoMedio, nExecucoes); 

    cout << endl << data.getInstanceName() << endl; 
    cout << "Tempo de execucao: " << tempoMedio << " s" << endl;
    cout << "Custo medio: " << custoMedio << endl;
    cout << "------------------------------------------------" << endl;  

    return 0;
}