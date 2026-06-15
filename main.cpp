#include "paleta.h"
#include <iostream>
#include <fstream>


int main() {

    std::ofstream file("paleta.txt");
    std::cout << "Quantas cores deseja na paleta? ";
    int n;
    std::cin >> n;

    std::cout << "Insira as cores em formato hexadecimal:\n";
    if (file.is_open()) {
        for (int i = 0; i < n; i++) {
            std::string hexadecimal;
            std::cin >> hexadecimal;
            file << hexadecimal << std::endl;
        }
        file.close();
        std::ifstream file("paleta.txt");
        Paleta turolla("paleta.txt");
        for (int i = 0; i < turolla.obterTamanho(); i++) {
            std::cout << turolla.obterCor(i).r << " " << turolla.obterCor(i).g << " " << turolla.obterCor(i).b << "\n";
        }
        file.close();
        remove("paleta.txt");
    } else {
        std::cout << "Erro na criação da paleta\n";
    }

    return 0;
}