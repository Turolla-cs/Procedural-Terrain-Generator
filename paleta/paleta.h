#ifndef PALETA_H
#define PALETA_H

#include <string>
#include <vector>

struct Cor {
    int r, g, b;
};

class Paleta {
    private:
        std::vector<Cor> cores;
        int tamanho;

    public:
        Paleta();
        Paleta(std::string nomeDoArquivo);

        Cor obterCor(int indice);
        void adicionarCor(Cor novaEntrada);
        int obterTamanho();
};

#endif