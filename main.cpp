#include "paleta/paleta.cpp"
#include "imagem-ppm/imagem.cpp"
#include "terreno/terreno.cpp"

#include <iostream>
#include <fstream>
#include <cmath>

int main() {

    srand(time(0));

    std::string nomeArquivo;

    std::cout << "Qual arquivo desejas usar como paleta de cores? ";
    std::cin >> nomeArquivo;

    Paleta paleta(nomeArquivo);

    int tamanho;
    double rugosidade = 25000;

    std::cout << "Qual o tamanho desejado para o mapa de altitudes? ";
    std::cin >> tamanho;

    Terreno terreno(std::pow(2, tamanho) + 1, rugosidade);

    Imagem imagem(terreno, paleta);

    std::cout << "Qual o nome do arquivo desejado? ";
    std::cin >> nomeArquivo;

    imagem.salvarPPM(nomeArquivo);
    terreno.salvarMatriz("terreno.txt");

    std::cout << "Um arquivo " << nomeArquivo << " com a sua imagem foi criado\n";
    std::cout << "Um arquivo terreno.txt com as altitudes do seu terreno foi criado\n";

    return 0;
}