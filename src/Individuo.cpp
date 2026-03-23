#include "Individuo.hpp"

Individuo::Individuo(double a_val, double b_val) : a(a_val), b(b_val), erro(0.0), fitness(0.0) {}
Individuo::Individuo() : a(0.0), b(0.0), erro(0.0), fitness(0.0) {}

void Individuo::avaliar(const std::vector<Ponto>& dados) {
    double soma_erros = 0.0;
    int n = dados.size();

    for (int i = 0; i < n; i++) {
        double y_estimado = a * dados[i].x + b;
        double e = dados[i].y - y_estimado;
        soma_erros += (e * e);
    }

    this->erro = soma_erros / n;
    this->fitness = 1.0 / (1.0 + this->erro);
}

void Individuo::mutar(double delta) {
    this->b += delta;
}