#ifndef TERRENO_H
#define TERRENO_H

#include <string>
#include <iostream>
#include <fstream>

class Terreno{
    private:
        int **mapaAltitudes;
        bool *mapaBool;
        int lincoln; //concatenação entre LINha + COLuna + N
        double rug;
    public:
        Terreno();
        Terreno(int n, double rugos);


        ~Terreno();

        int obterAltitude(int lin, int col) const;
        int obterLincoln() const;
        bool salvarMatriz(std::string nomeArquivo);
        bool lerMatriz(std::string nomeArquivo);
        void definirAltitude(int lin, int col, int alt);
        double obterRug() const;
};

#endif 