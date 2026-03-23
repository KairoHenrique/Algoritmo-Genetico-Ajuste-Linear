#ifndef INDIVIDUO_HPP
#define INDIVIDUO_HPP

#include <vector>

struct Ponto {
    double x;
    double y;
};

class Individuo {
public:
    double a;
    double b;
    double erro;
    double fitness;

    Individuo(double a_val, double b_val);
    Individuo();

    void avaliar(const std::vector<Ponto>& dados);
    void mutar(double delta);
};

#endif