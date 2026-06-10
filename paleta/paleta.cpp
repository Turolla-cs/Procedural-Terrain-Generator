#include <iostream>
#include <fstream>

#include <string>
#include <vector>

struct Cor {
    int R, G, B;
};

Cor hexaInt(std::string hexa) {
    int r = 0, g = 0, b = 0;
    for (int i = 0; i < 6; i++) {
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
        if (i < 2) {
            if (i == 1) {
                r += valor;
            } else {
                r += 16*valor;
            }
        } else if (i < 4) {
            if (i == 3) {
                g += valor;
            } else {
                g += 16*valor;
            }
        } else {
            if (i == 5) {
                b += valor;
            } else {
                b += 16*valor;
            }
        }
    }
    Cor saida;
    saida.R = r;
    saida.G = g;
    saida.B = b;
    return saida;
}

class Paleta {
    std::vector<Cor> cores;
    int tamanho;

    public:
        Paleta() { tamanho = 0; }

        Paleta(std::ifstream& file) {
            tamanho = 0;
            std::string hexadecimal;
            while (getline(file, hexadecimal)) {
                if (!hexadecimal.empty()) {
                    cores.push_back(hexaInt(hexadecimal));
                    tamanho++;
                }
            }
        }

        Cor getCor(int indice) {
            Cor gabriel;
            gabriel.R = cores[indice].R;
            gabriel.G = cores[indice].G;
            gabriel.B = cores[indice].B;
            return gabriel;
        }

        int getTamanho() {
            return tamanho;
        }
};

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
        Paleta turolla(file);
        for (int i = 0; i < turolla.getTamanho(); i++) {
            std::cout << turolla.getCor(i).R << " " << turolla.getCor(i).B << " " << turolla.getCor(i).B << "\n";
        }
        file.close();
        remove("paleta.txt");
    } else {
        std::cout << "Erro na criação da paleta\n";
    }

    return 0;
}