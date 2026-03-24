# <h1 align="center"> Otimizador Genético Linear </h1>

## :page_with_curl: Introdução
<p align="justify">
  
Nesse trabalho, o ajuste de curvas e a regressão linear é um problema de otimização: o objetivo é encontrar os parâmetros de uma função matemática que melhor descrevam um conjunto de dados observados. O uso de uma meta-heurística evolutiva permite que o computador "aprenda" os melhores coeficientes através de sucessivas gerações de tentativas, erros, cruzamentos e mutações, aproximando-se gradativamente da reta ideal que minimiza as distâncias para os pontos do conjunto de dados.
</p>
 
## :bookmark_tabs: Descrição do projeto

Este projeto busca o desenvolvimento de um simulador computacional baseado em Algoritmo Genético destinado a ajustar uma função afim $\hat{y}=ax+b$ a um conjunto de pontos bidimensionais $(x, y)$. A representação computacional da população é feita através de objetos modulares alocados dinamicamente. Cada indivíduo carrega em seu "DNA" os genes $a$ e $b$, e a sua aptidão evolui ao longo da simulação de acordo com o Erro Quadrático Médio (MSE) em relação ao dataset.
<p>
<p align="justify">
Além da simulação do cálculo matemático, tambem utilizamos o controle geracional, aplicando as fases de avaliação de aptidão (fitness), seleção dos mais aptos, reprodução (crossover) e mutação genética para manter a diversidade da população.
<p>
<p align="justify">
Este trabalho foi proposto pelo professor Michel Pires Silva, instrutor da disciplina Algoritmos e Estrutura de Dados I, do Centro Federal de Educação Tecnológica de Minas Gerais (CEFET - MG), Campus V - Divinópolis.
<p>

### :pushpin: 1. Representação da População
<p align="justify">
  A população de soluções candidatas é representada computacionalmente por meio de estruturas dinâmicas <code>std::vector</code>. Cada elemento corresponde a um Indivíduo com atributos específicos:
</p>

- **Genes (a, b)**: Coeficientes da reta.
- **Erro**: Discrepância calculada entre a reta do indivíduo e os pontos reais.
- **Fitness**: Valor de aptidão inversamente proporcional ao erro ($1/(1+erro)$).

### :pushpin: 2. Simulação do Processo Evolutivo

<p align="justify">
  A evolução da população ocorre de forma iterativa ao longo de $G$ gerações, seguindo um conjunto de regras biológicas adaptadas para a matemática.
</p>

#### 2.1 Regras de Propagação (Crossover):
<p align="justify">
  A cada iteração, toda a população é avaliada e ranqueada de acordo com o fitness. O algoritmo aplica o elitismo puro, selecionando os dois indivíduos mais aptos (Pai 1 e Pai 2). O cruzamento genético ocorre mesclando o coeficiente angular ($a$) do Pai 1 com o coeficiente linear ($b$) do Pai 2 para gerar uma nova solução candidata (Filho).
</p>

#### 2.2 Mutação Genética:
<p align="justify">
  Para evitar a convergência prematura (estagnação evolutiva), o Filho recém-criado sofre uma mutação controlada. Um valor estocástico $\delta$ entre -0.5 e 0.5 é somado ao seu parâmetro $b$, simulando uma adaptação ambiental e garantindo a exploração de novos resultados.
</p>

#### 2.3 Regras de Substituição:
<p align="justify">
  O ambiente simula a sobrevivência do mais apto. Após a geração e mutação do Filho, o indivíduo com o pior desempenho (menor fitness) de toda a população é sumariamente eliminado e substituído pelo novo descendente.
</p>

## 🖥️ Ambiente de Criação

O código foi desenvolvido utilizando as seguintes ferramentas:

[![Linguagem](https://img.shields.io/badge/Linguagem-C%2B%2B-blue)](https://learn.microsoft.com/cpp/)
[![IDE](https://img.shields.io/badge/IDE-Visual%20Studio%20Code-blueviolet)](https://code.visualstudio.com/docs/?dv=linux64_deb)
[![Sistema Operacional](https://img.shields.io/badge/OS-Linux%20Debian-red)](https://www.debian.org/)


## :file_folder: Estrutura Geral do Projeto

A estrutura do projeto é disposta da seguinte maneira:

```text
Algoritmo-Genetico-AJuste-Linear/
├── Makefile                   # Script para automação da compilação
├── README.md                  # Documentação principal do projeto
├── include/                   # Arquivos de cabeçalho
    ├── AlgoritmoGenetico.hpp  # Estrutura do controlador evolutivo 
    └── Individuo.hpp          # Estrutura do cromossomo/solução 
├── src/                       # Código-fonte das implementações (C++)
    ├── AlgoritmoGenetico.cpp  # Lógica das gerações, seleção e cruzamento
    ├── Individuo.cpp          # Cálculos de avaliação (MSE) e mutação
    └── main.cpp               # Execução principal do programa
├── data/                      # Diretório de dados operacionais
    ├── input.dat              # Arquivo lido pela simulação (N, M, G e coordenadas)
    └── output.dat             # Relatório gerado automaticamente com os resultados
└── misc/                      # Arquivos auxiliares e documentação extra
    ├── input.dat              # Modelo de exemplo para o arquivo de entrada
    └── Trab 1 Aeds.pdf        # Documento com a especificação do trabalho
```

## :man_technologist: Implementação

O fluxo do programa se inicia pela leitura dos dados do problema através do `input.dat`, cujas configurações ditam o tamanho do dataset ($n$), o tamanho da população ($m$) e o total de gerações ($G$).

O construtor populacional utiliza a biblioteca `<random>` do C++ para alocar os indivíduos com instâncias pseudoaleatórias, distribuídas uniformemente, garantindo uma variedade inicial crucial para o processo evolutivo.

```cpp
std::random_device rd;
std::mt19937 gen(rd()); 
std::uniform_real_distribution<> dis(-10.0, 10.0);
for (int i = 0; i < m; i++) {
    populacao.push_back(Individuo(dis(gen), dis(gen)));
}
```

O núcleo do simulador está no loop principal de `AlgoritmoGenetico::executar()`. Para atender aos requisitos técnicos, além do encapsulamento natural do C++, implementou-se um vetor auxiliar obrigatório:

```cpp
vetor_fitness.clear();
for (const auto& ind : populacao) {
    vetor_fitness.push_back(ind.fitness);
}
```

A mutação contínua (com $\delta$ variando dinamicamente entre valores positivos e negativos) garante que o erro possa fazer um ajuste fino da reta tanto aumentando quanto diminuindo sua altura em relação ao eixo $y$. 

## 💬🎯 Análises e Conclusões

A validação da modelagem foi feita observando o log em `output.dat`. Nas gerações iniciais, o erro apresenta grande oscilação, configurando retas que cruzam os pontos de maneira caótica. No entanto, por causa da heurística de substituir sempre o pior indivíduo, a população global se torna cada vez mais precisa. 

Notou-se que a mutação é o motor secundário essencial: sem uma variação $\delta$ bilateral (positiva e negativa), os filhos gerados pelo crossover elitista poderiam "travar" num mínimo local matemático, nunca alcançando o menor Erro Quadrático Médio possível.

### Análise Assintótica

A eficiência do Algoritmo Genético depende profundamente da dimensão da população ($m$) e da quantidade de gerações ($G$).

* No módulo `Individuo.cpp`, a função `avaliar` possui complexidade de tempo de $O(n)$, pois precisa iterar por todos os $n$ pontos do dataset para calcular o erro global (MSE).
* No módulo `AlgoritmoGenetico.cpp`, o laço geracional engloba a avaliação da população inteira, custando $O(m \times n)$. A etapa de ordenação dos indivíduos pelo melhor fitness utiliza o `std::sort` do C++, que apresenta complexidade assintótica de tempo de $O(m \log m)$.
* Operações de crossover, mutação pontual e descarte do pior elemento possuem impacto constante de tempo, $O(1)$. 
* O espaço de memória consumido é majoritariamente $O(m + n)$, refletindo o vetor da população e o vetor do dataset.

| **Operação Genética** | **Tempo (Pior Caso)** | **Espaço (Memória)** |
|-----------------------|-----------------------|----------------------|
| `avaliar()`           | $O(n)$              | $O(1)$               |
| Laço de Avaliação     | $O(m \times n)$       | -                    |
| Seleção (`std::sort`) | $O(m \log m)$         | $O(1)$   |
| Mutação e Crossover   | $O(1)$              | $O(1)$               |
| **Total (Global)** | **$O(G \times (m \times n + m \log m))$** | **$O(m + n)$** |

**Legenda**:
- **G**: Número total de gerações.
- **m**: Tamanho da população.
- **n**: Quantidade de pontos do dataset.


## :keyboard: Instalação e Configuração 

Para a execução correta do software, é recomendado o seguinte ambiente:
  * Compilador C++ (g++ recomendado, com suporte a C++11 ou superior)
  * Utilitário `Make` para *build* .
  * Ambiente Linux (Debian/Ubuntu).

### **Passos e Comandos**

#### **1. Clone o repositório**
No terminal, digite o seguinte comando para clonar o repositório;
```bash
git clone <https://github.com/KairoHenrique/Algoritmo-Genetico-AJuste-Linear>

```

#### **2. Arquivo de Dados (`input.dat`)**
Certifique-se de que existe um arquivo `input.dat` na pasta data com os parâmetros na primeira linha (n, m, G) e as coordenadas x e y nas linhas seguintes. Exemplo:
```text
5 20 100
1.0 3.1
2.0 4.9
...
```

#### **3. Compilar o projeto:**
Comando para compilar:
```bash
make
```
*(Caso queira forçar uma recompilação limpa, utilize `make clean` antes de `make`)*.

#### **4. Executar o projeto:**
```bash
make run
```
A execução lerá os dados e gerará imediatamente o arquivo **`output.dat`** contendo os indicadores de evolução para cada geração processada.


## :busts_in_silhouette: Desenvolvedor do Projeto


[<img loading="lazy" src="https://avatars.githubusercontent.com/u/135791815?v=4" width=115><br><sub>Kairo Henrique</sub>](https://github.com/KairoHenrique)
Estudante de Engenharia de Computação.


## :computer: Ambiente de teste
Este projeto foi executado:
  * **Processador**: 12th Gen Intel® Core™ i7-1255U
  * **Memoria RAM**: 40GB DDR4 3200MHz.
  * **Sistema Operacional**: Debian GNU/Linux 13
  * **Compilador**: GCC (g++).


## :gear: Recursos Utilizados
<p align="left">
  <img alt="Visual Studio Code" height="60" width="60" src="[https://github.com/gui-bus/TechIcons/blob/main/Dark/VSCode.svg](https://github.com/gui-bus/TechIcons/blob/main/Dark/VSCode.svg)">
  <img alt="C++" height="60" width="60" src="[https://github.com/gui-bus/TechIcons/blob/main/Dark/C++.svg](https://github.com/gui-bus/TechIcons/blob/main/Dark/C++.svg)">
</p>
