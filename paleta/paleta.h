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

    public:
        Paleta();
        Paleta(std::string nomeDoArquivo);

        Cor obterCor(int indice) const;
        void adicionarCor(Cor novaEntrada);
        int obterTamanho() const;
};

#endif