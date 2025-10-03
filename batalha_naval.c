#include <stdio.h>

int main() {
    // Letras para referência das colunas
    char colunas[10] = {'A','B','C','D','E','F','G','H','I','J'};

    // 1. Criar o tabuleiro 10x10 e inicializar com 0 (água)
    int tabuleiro[10][10];
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            tabuleiro[i][j] = 0;
        }
    }

    // 2. Criar os navios (vetores unidimensionais com tamanho fixo = 3)
    int navioHorizontal[3] = {3, 3, 3};
    int navioVertical[3]   = {3, 3, 3};

    // 3. Definir coordenadas iniciais dos navios
    // Navio horizontal em linha 2, coluna 4
    int linhaHorizontal = 2;
    int colunaHorizontal = 4;

    // Navio vertical em linha 5, coluna 7
    int linhaVertical = 5;
    int colunaVertical = 7;

    // 4. Posicionar navio horizontal no tabuleiro
    for (int k = 0; k < 3; k++) {
        tabuleiro[linhaHorizontal][colunaHorizontal + k] = navioHorizontal[k];
    }

    // 5. Posicionar navio vertical no tabuleiro
    for (int k = 0; k < 3; k++) {
        tabuleiro[linhaVertical + k][colunaVertical] = navioVertical[k];
    }

    // 6. Imprimir o tabuleiro
    printf("\n=== Tabuleiro Batalha Naval ===\n\n");

    // Cabeçalho com letras das colunas
    printf("   ");
    for (int j = 0; j < 10; j++) {
        printf(" %c ", colunas[j]);
    }
    printf("\n");

    // Impressão do tabuleiro com números nas linhas
    for (int i = 0; i < 10; i++) {
        printf("%2d ", i); // número da linha
        for (int j = 0; j < 10; j++) {
            printf(" %d ", tabuleiro[i][j]);
        }
        printf("\n");
    }

    return 0;
}