#ifndef IMAGEM_H
#define IMAGEM_H

#include "../paleta/paleta.h"
#include "../terreno/terreno.h"

using Pixel = Cor;

class Imagem {
    private:
        int largura;
        int altura;
        Pixel *matriz;
    public:
        Imagem();
        Imagem(int j, int i);

        Imagem(const Terreno& terreno, const Paleta& paleta);

        ~Imagem();

        Pixel& obterPixel(int j, int i);
        void definirPixel(int j, int i, const Pixel cor);
        bool lerPPM(std::string nomeArquivo);
        bool salvarPPM(std::string nomeArquivo);
        int obterLargura();
        int obterAltura();
};


#endif