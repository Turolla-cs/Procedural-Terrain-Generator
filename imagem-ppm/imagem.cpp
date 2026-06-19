#include "imagem.h"

#include <iostream>
#include <string>
#include <fstream>


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