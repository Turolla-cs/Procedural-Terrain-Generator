#include "imagem.h"

#include <iostream>
#include <string>
#include <fstream>
#include <cmath>


Imagem::Imagem() { 
    largura = 0;
    altura = 0;
    matriz = nullptr;
}

Imagem::Imagem(int j, int i) {
    altura = i;
    largura = j;
    matriz = new Pixel[largura * altura];
}

Imagem::~Imagem() {
    delete[] matriz;
}

int Imagem::obterLargura() {
    return largura;
}

int Imagem::obterAltura() {
    return altura;
}


Pixel& Imagem::obterPixel(int j, int i) {
    return matriz[i * largura + j];
}

void Imagem::definirPixel(int j, int i, const Pixel cor) {
    matriz[i * largura + j] = cor;
}

bool Imagem::lerPPM(std::string nomeArquivo) {
    std::ifstream file(nomeArquivo);

    if (!file.is_open()) {
        std::cerr << "Erro 52: nome de arquivo incorreto\n";
        return false;
    }

    std::string s;

    file >> s;
    if (s == "P3") {

        if (matriz != nullptr) {
            delete[] matriz;
        }

        int valorMaxRgb;
        file >> largura >> altura >> valorMaxRgb;

        matriz = new Pixel[largura * altura];
        
        for (int m = 0; m < altura; m++) {
            for (int n = 0; n < largura; n++) {
                int red, green, blue;
                file >> red >> green >> blue;
                Pixel p = {red, green, blue};
                definirPixel(n, m, p);
            }
        }

        file.close();
        return true;

    } else {

        std::cerr << "Tipo de imagem incorreto, utilize o tipo PPM P3";
        file.close();
        return false;

    }

    return true;
}


bool Imagem::salvarPPM(std::string nomeArquivo) {
    std::ofstream file(nomeArquivo);

    if (file.is_open()) {
        file << "P3\n" << largura << " " << altura << "\n" << "255\n";
        for (int k = 0; k < altura*largura; k++) {
            Pixel p = obterPixel(k%largura, k/largura);
            file << p.r << " " << p.g << " " << p.b << "\n";
        }
    } else {
        std::cout << "Erro ao criar arquivo\n";
        return false;
    }

    return true;
}



Imagem::Imagem(const Terreno& terreno, const Paleta& paleta) {

    double *luminosidade;
    luminosidade = new double[terreno.obterLincoln()*terreno.obterLincoln()];

    largura = altura = terreno.obterLincoln();

    matriz = new Pixel[largura * altura];
    int t = paleta.obterTamanho();

    int altMax, altMin;
    altMax = altMin = terreno.obterAltitude(0, 0);

    for (int i = 0; i < largura; i++) {
        for (int j = 0; j < altura; j++) {
            if (altMax < terreno.obterAltitude(i, j)) {
                altMax = terreno.obterAltitude(i, j);
            }
            if (altMin > terreno.obterAltitude(i, j)) {
                altMin = terreno.obterAltitude(i, j);
            }
        }
    }

    for (int i = 0; i < largura; i++) {

        for (int j = 0; j < altura; j++) {
            bool abraham = true;
            luminosidade[i*largura+j] = 1;
            
            

            for (int k = 0; k < t && abraham; k++) {

                if (terreno.obterAltitude(i, j) <= (int)(((double)(k + 1) / t) * (altMax-altMin)) || k == t - 1) {

                    Cor truta = paleta.obterCor(k);

                    if (i > 0 && j > 0) {

                        int a = terreno.obterAltitude(i, j);
                        int b = terreno.obterAltitude(i-1, j-1);
                        int n;


                        if (largura > 1024) {
                            n = std::log2(altura-1);
                        } else {
                            n = 1;
                        }

                        if (n*b/largura > n*a/largura) {
                        
                            luminosidade[i*largura+j] = 0.5;

                        } else if (n*a/largura > n*b/largura) {
                            
                            luminosidade[i*largura+j] = 1;
                        } else {
                            luminosidade[i*largura+j] = 0.75;
                        }

                        truta.r *= luminosidade[i*largura+j];
                        truta.g *= luminosidade[i*largura+j];
                        truta.b *= luminosidade[i*largura+j];
                    }
                    definirPixel(j, i, truta);
                    abraham = false;
                }

            }


        }
    }

    delete[] luminosidade;
}

