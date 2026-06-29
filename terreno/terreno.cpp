#include "terreno.h"
#include <cstdlib>
#include <ctime>
#include <filesystem>

struct Ponto {
    int linha;
    int coluna;
};

bool checkLincoln(int n) {
    int k = n - 1;
    if (k <= 0) {
        return false;
    }
    while (k > 1) {
        if (k % 2 != 0) {
            return false;
        }
        k /= 2;
    }
    if (k == 1) {
        return true;
    }
    return false;
}

double obterRugosidade(double r) {
    double rugosidade = (rand() % (int)(r+r+1)) - r;
    return rugosidade;
}

Terreno::Terreno() {
    lincoln = 0;
    rug = 0;
    mapaAltitudes = nullptr; 
    mapaBool = nullptr;
}

int pontosSquare(int n, Ponto alvo, Ponto diamond, const Terreno& x, double r) {
    int d = (n-1)/2;
    if (alvo.linha == diamond.linha-d) {
        return (((x.obterAltitude(alvo.linha, alvo.coluna-d) + x.obterAltitude(alvo.linha, alvo.coluna+d) + x.obterAltitude(alvo.linha+d, alvo.coluna))/3) + obterRugosidade(r));
    }
    else if (alvo.linha == diamond.linha+d) {
        return (((x.obterAltitude(alvo.linha, alvo.coluna-d) + x.obterAltitude(alvo.linha, alvo.coluna+d) + x.obterAltitude(alvo.linha-d, alvo.coluna))/3) + obterRugosidade(r));
    }
    else if (alvo.coluna == diamond.coluna-d) {
        return (((x.obterAltitude(alvo.linha-d, alvo.coluna) + x.obterAltitude(alvo.linha, alvo.coluna+d) + x.obterAltitude(alvo.linha+d, alvo.coluna))/3) + obterRugosidade(r));
    }
    else if (alvo.coluna == diamond.coluna+d) {
        return (((x.obterAltitude(alvo.linha, alvo.coluna-d) + x.obterAltitude(alvo.linha-d, alvo.coluna) + x.obterAltitude(alvo.linha+d, alvo.coluna))/3) + obterRugosidade(r));
    }
    else {
        return (((x.obterAltitude(alvo.linha, alvo.coluna-d) + x.obterAltitude(alvo.linha-d, alvo.coluna) + x.obterAltitude(alvo.linha+d, alvo.coluna) + x.obterAltitude(alvo.linha, alvo.coluna+d))/4) + obterRugosidade(r));
    }
}

void diamondSquare(Ponto p, int n, Terreno& x, double rugosidadeAnterior) {
    Ponto p1, p2, p3, p4, p12, p13, p24, p34;
    int d = (n-1)/2;
    double rugosidadeAtual = rugosidadeAnterior / 2.5;

    p1.linha = p.linha-d;
    p1.coluna = p.coluna-d;

    p2.linha = p.linha-d;
    p2.coluna = p.coluna+d;

    p3.linha = p.linha+d;
    p3.coluna = p.coluna-d;

    p4.linha = p.linha+d;
    p4.coluna = p.coluna+d;

    double r = obterRugosidade(rugosidadeAtual);

    int alt = ((x.obterAltitude(p1.linha, p1.coluna) + x.obterAltitude(p2.linha, p2.coluna) + x.obterAltitude(p3.linha, p3.coluna) + x.obterAltitude(p4.linha, p4.coluna))/4) + r;
    x.definirAltitude(p.linha, p.coluna, alt);

    p12.linha = p1.linha;
    p12.coluna = p.coluna;

    p13.linha = p.linha;
    p13.coluna = p1.coluna;

    p24.linha = p.linha;
    p24.coluna = p4.coluna;

    p34.linha = p3.linha;
    p34.coluna = p.coluna;

    x.definirAltitude(p12.linha, p12.coluna, pontosSquare(n, p12, p, x, rugosidadeAtual));
    x.definirAltitude(p13.linha, p13.coluna, pontosSquare(n, p13, p, x, rugosidadeAtual));
    x.definirAltitude(p24.linha, p24.coluna, pontosSquare(n, p24, p, x, rugosidadeAtual));
    x.definirAltitude(p34.linha, p34.coluna, pontosSquare(n, p34, p, x, rugosidadeAtual));

    if (n != 3) {
        Ponto p5, p6, p7, p8;
        int c = d/2;

        p5.linha = p.linha-c;
        p5.coluna = p.coluna-c;

        p6.linha = p.linha-c;
        p6.coluna = p.coluna+c;

        p7.linha = p.linha+c;
        p7.coluna = p.coluna-c;

        p8.linha = p.linha+c;
        p8.coluna = p.coluna+c;
    
        diamondSquare(p5, (d+1), x, rugosidadeAtual);
        diamondSquare(p6, (d+1), x, rugosidadeAtual);
        diamondSquare(p7, (d+1), x, rugosidadeAtual);
        diamondSquare(p8, (d+1), x, rugosidadeAtual);
    }
}

Terreno::Terreno(int n, double rugos) {
    lincoln = 0;
    rug = 0;
    mapaAltitudes = nullptr; 
    mapaBool = nullptr;
    if (checkLincoln(n)){
        
        mapaAltitudes = new int*[n];
        for (int i = 0; i<n; i++) {
            mapaAltitudes[i] = new int[n]();
        }
        mapaBool = new bool[n*n]();
        
        for (int i = 0; i < n*n; i++) {
            mapaBool[i] = false;
        }

        lincoln = n;
        rug = rugos;
        Ponto diamond;
        diamond.linha = diamond.coluna = (n-1)/2;


        int min = 0; 
        int max = 10000;
        int rnd1 = (rand() % (max-min+1)) + min;
        int rnd2 = (rand() % (max-min+1)) + min;
        int rnd3 = (rand() % (max-min+1)) + min;
        int rnd4 = (rand() % (max-min+1)) + min;



        mapaAltitudes[0][0] = rnd1;
        mapaAltitudes[0][n-1] = rnd2;
        mapaAltitudes[n-1][0] = rnd3;
        mapaAltitudes[n-1][n-1] = rnd4;

        mapaBool[0] = true;
        mapaBool[n-1] = true;
        mapaBool[n*(n-1)] = true;
        mapaBool[(n-1)*(n+1)] = true;

        diamondSquare(diamond, n, *this, rug);

    }
    else {
        std::cout << "Erro: Tamanho inválido\n";
    }
} 

Terreno::~Terreno() {
    for (int i = 0; i < lincoln ; i++) {
        delete[] mapaAltitudes[i];
    }
    delete[] mapaAltitudes;
    delete[] mapaBool;
}

int Terreno::obterAltitude(int lin, int col) const {
    return mapaAltitudes[lin][col];
}

int Terreno::obterLincoln() const {
    return lincoln;
}

bool Terreno::salvarMatriz(std::string nomeArquivo) {
    std::string Caminho = "output";
    std::filesystem::path destino = std::filesystem::path (Caminho)/nomeArquivo;
    std::ofstream file(destino);

    if (file.is_open()) {
        file << lincoln << ' ' << rug << '\n';
        for (int i = 0; i < lincoln; i++) {
            for (int j = 0; j < lincoln; j++) {
                file << mapaAltitudes[i][j] << ' ';
            }
            file << "\n";
        }
    } else {
        std::cout << "Erro ao criar arquivo\n";
        return false;
    }

    return true;
}

bool Terreno::lerMatriz(std::string nomeArquivo) {
    std::string Caminho = "input";
    std::filesystem::path fonte = std::filesystem::path (Caminho)/nomeArquivo;
    std::ifstream file(fonte);

    if (!file.is_open()) {
        std::cerr << "Erro 52: nome de arquivo incorreto\n";
        return false;
    }

    std::string s;

    file >> lincoln >> rug;

    if (mapaAltitudes != nullptr) {
        for (int i = 0; i < lincoln ; i++) {
            delete[] mapaAltitudes[i];
        }
        delete[] mapaAltitudes;
    }

    if (mapaBool != nullptr) {
        delete[] mapaBool;
    }

    mapaAltitudes = new int*[lincoln]();
    for (int i = 0; i<lincoln; i++) {
        mapaAltitudes[i] = new int[lincoln];
    }
    mapaBool = new bool[lincoln*lincoln]();
    
    for (int i = 0; i < lincoln; i++) {
        for (int j = 0; j < lincoln; j++) {
            file >> mapaAltitudes[i][j];
        }
    }

    return true;
}

void Terreno::definirAltitude(int lin, int col, int alt) {
    if (!mapaBool[lin*lincoln+col]) {
        mapaAltitudes[lin][col] = alt;
        mapaBool[lin*lincoln+col] = true;
    }
}

double Terreno::obterRug() const {
    return rug;
}