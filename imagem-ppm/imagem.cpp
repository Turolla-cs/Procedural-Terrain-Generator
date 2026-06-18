#include "imagem.h"
#include <iostream>
#include <string>
#include <fstream>


Imagem::Imagem() {}

Imagem::Imagem(int i, int j) {
    largura = i;
    altura = j;
    matriz = new int[i * j];
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


Pixel& Imagem::obterPixel(int i, int j) {
    return matriz[i * largura + j];
}



bool Imagem::lerPPM(std::string nomeArquivo) {
    std::ifstream file(nomeArquivo);
    if (file.is_open()) {
        std::string s;
        getline(file, s);
        if (s == "P3") {
            getline(file, s);
            int alturaLargura = stoi(s);
            int largura = alturaLargura/10;
            int altura = alturaLargura%10;
            getline(file,s);
            int valorMaxRgb = stoi(s);
            for (int i = 0; i < (altura*largura); i++) {
                
            }
        }
        else {
            std::cout << "Tipo de imagem incorreto, utilize o tipo PPM P3"; 
        }
            
    }
}


bool Imagem::salvarPPM(std::string nomeArquivo) {

}