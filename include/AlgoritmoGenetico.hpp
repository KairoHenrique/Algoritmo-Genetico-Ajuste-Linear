#ifndef ALGORITMOGENETICO_HPP
#define ALGORITMOGENETICO_HPP

#include "Individuo.hpp"
#include <vector>
#include <string>

class AlgoritmoGenetico {
private:
    std::vector<Individuo> populacao;
    std::vector<Ponto> dataset;
    int n, m, G;

public:
    AlgoritmoGenetico();

    bool carregarDados(const std::string& arquivo_entrada);
    void inicializarPopulacao(double limite_min, double limite_max);
    void executar();
};

#endif