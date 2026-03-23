#include "AlgoritmoGenetico.hpp"
#include <iostream>

int main() {
    AlgoritmoGenetico ag;

    if (!ag.carregarDados("input.dat")) {
        return 1;
    }

    ag.inicializarPopulacao(-10.0, 10.0);
    ag.executar();

    std::cout << "Execucao concluida! Resultados salvos em output.dat." << std::endl;

    return 0;
}