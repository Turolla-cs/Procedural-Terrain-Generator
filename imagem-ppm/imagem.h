#ifndef IMAGEM_H
#define IMAGEM_H

#include "../paleta/paleta.h" 

struct Pixel {
    Cor cor;
};

class Imagem {
    private:
        int largura;
        int altura;
        int *matriz;
    public:
        Imagem(int x, int y);
        ~Imagem();

        Pixel obterPixel(int x, int y);
        void definirPixel(int x, int y, Pixel cor);
        bool lerPPM(std::string nomeArquivo);
        bool salvarPPM(std::string nomeArquivo);
        int obterLargura();
        int obterAltura();
};


#endif