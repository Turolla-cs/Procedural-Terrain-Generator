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
    Paleta paletaCinza("paletaCinza.txt");

    int tamanho;
    double rugosidade = 25000;

    std::cout << "Qual o tamanho desejado para o mapa de altitudes? ";
    std::cin >> tamanho;

    Terreno terreno(std::pow(2, tamanho) + 1, rugosidade);

    Imagem imagem(terreno, paleta);
    Imagem imagemCinza(terreno, paletaCinza);

    std::cout << "Qual o nome do arquivo que será criado? ";
    std::cin >> nomeArquivo;
    std::string nomeArquivoCinza = nomeArquivo + "Cinza";

    imagem.salvarPPM(nomeArquivo);
    imagemCinza.salvarPPM(nomeArquivoCinza);
    terreno.salvarMatriz("terreno.txt");

    std::cout << "Arquivos criados: \n- Um arquivo chamado " << nomeArquivo <<"\n- Um arquivo chamado " << nomeArquivo <<"Cinza\n- Um arquivo chamado terreno.txt com as altitudes do seu terreno\n Todos estarão na pasta output\n";

    return 0;
}