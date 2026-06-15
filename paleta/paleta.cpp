#include "paleta.h"
#include <iostream>
#include <fstream>



Cor hexaInt(std::string hexa) {
    int r = 0, g = 0, b = 0;
    for (int i = 1; i < 7; i++) {
        int valor;
        if (hexa[i] >= 48 && hexa[i] <= 57) {
            valor = hexa[i] - '0';
        } else {
            if (hexa[i] == 'a') {
                valor = 10;
            } else if (hexa[i] == 'b') {
                valor = 11;
            } else if (hexa[i] == 'c') {
                valor = 12;
            } else if (hexa[i] == 'd') {
                valor = 13;
            } else if (hexa[i] == 'e') {
                valor = 14;
            } else if (hexa[i] == 'f') {
                valor = 15;
            }
        }
        if (i < 3) {
            if (i == 2) {
                r += valor;
            } else {
                r += 16*valor;
            }
        } else if (i < 5) {
            if (i == 4) {
                g += valor;
            } else {
                g += 16*valor;
            }
        } else {
            if (i == 6) {
                b += valor;
            } else {
                b += 16*valor;
            }
        }
    }
    Cor saida;
    saida.r = r;
    saida.g = g;
    saida.b = b;
    return saida;
}

Paleta::Paleta() {
    tamanho = 0;
}

Paleta::Paleta(std::string nomeDoArquivo){
    tamanho = 0;
    std::ifstream file(nomeDoArquivo);
    if (file.is_open()) {
        std::string hexadecimal;
        
        while (getline(file, hexadecimal)) {
            if (!hexadecimal.empty()) {
                cores.push_back(hexaInt(hexadecimal));
                tamanho++;
            }
        }
        file.close();
    } else {
        std::cout << "Erro 52: nome de arquivo incorreto\n";
    }
}

void Paleta::adicionarCor(Cor novaCor){
    cores.push_back(novaCor);
    tamanho++;
}

int Paleta::obterTamanho(){
    return tamanho;
}

Cor Paleta::obterCor(int indice){
    if (indice < tamanho) {
        Cor gabriel;
        gabriel.r = cores[indice].r;
        gabriel.g = cores[indice].g;
        gabriel.b = cores[indice].b;
        return gabriel;
    } else {
        Cor invalida = {0, 0, 0};
        return invalida;
    }
}
