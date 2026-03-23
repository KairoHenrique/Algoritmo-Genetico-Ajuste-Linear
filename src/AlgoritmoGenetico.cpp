#include "AlgoritmoGenetico.hpp"
#include <iostream>
#include <fstream>
#include <random>
#include <algorithm>

AlgoritmoGenetico::AlgoritmoGenetico() : n(0), m(0), G(0) {}

bool AlgoritmoGenetico::carregarDados(const std::string& arquivo_entrada) {
    std::ifstream file(arquivo_entrada);
    if (!file.is_open()) {
        std::cerr << "Erro ao abrir " << arquivo_entrada << std::endl;
        return false;
    }

    file >> n >> m >> G;

    for (int i = 0; i < n; i++) {
        Ponto p;
        file >> p.x >> p.y;
        dataset.push_back(p);
    }
    
    file.close();
    return true;
}

void AlgoritmoGenetico::inicializarPopulacao(double limite_min, double limite_max) {
    std::random_device rd;
    std::mt19937 gen(rd()); 
    std::uniform_real_distribution<> dis(limite_min, limite_max);

    for (int i = 0; i < m; i++) {
        populacao.push_back(Individuo(dis(gen), dis(gen)));
    }
}

void AlgoritmoGenetico::executar() {
    std::ofstream arquivo_saida("output.dat");

    for (int geracao = 0; geracao < G; geracao++) {
        
        for (auto& ind : populacao) {
            ind.avaliar(dataset);
        }

        std::sort(populacao.begin(), populacao.end(), [](const Individuo& i1, const Individuo& i2) {
            return i1.fitness > i2.fitness;
        });

        Individuo pai1 = populacao[0];
        Individuo pai2 = populacao[1];

        Individuo filho(pai1.a, pai2.b);

        double delta = 0.5;
        filho.mutar(delta);
        filho.avaliar(dataset); 

        populacao.back() = filho;

        std::sort(populacao.begin(), populacao.end(), [](const Individuo& i1, const Individuo& i2) {
            return i1.fitness > i2.fitness;
        });

        arquivo_saida << populacao[0].fitness << " " 
                      << populacao[0].erro << " " 
                      << populacao[0].a << " " 
                      << populacao[0].b << "\n";
    }
    
    arquivo_saida.close();
}