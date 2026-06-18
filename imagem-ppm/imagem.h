#ifndef IMAGEM_H
#define IMAGEM_H

#include "../paleta/paleta.h" 

using Pixel = Cor;

class Imagem {
    private:
        int largura;
        int altura;
        int *matriz;
    public:
        Imagem();
        Imagem(int i, int j);
        ~Imagem();

        Pixel& obterPixel(int i, int j);
        void definirPixel(int i, int j);
        bool lerPPM(std::string nomeArquivo);
        bool salvarPPM(std::string nomeArquivo);
        int obterLargura();
        int obterAltura();
};


#endif