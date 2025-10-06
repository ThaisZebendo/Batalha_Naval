#include <stdio.h>

// ===== NOVAS FUNÇÕES =====

// Função auxiliar para verificar se é possível posicionar um navio
int podePosicionar(int tabuleiro[10][10], int linha, int coluna, int tamanho, int direcao) {
    // direcao: 0 = horizontal, 1 = vertical, 2 = diagonal principal, 3 = diagonal secundária
    for (int k = 0; k < tamanho; k++) {
        int i = linha, j = coluna;
        if (direcao == 0) j += k;           // horizontal
        else if (direcao == 1) i += k;      // vertical
        else if (direcao == 2) { i += k; j += k; }   // diagonal principal
        else if (direcao == 3) { i += k; j -= k; }   // diagonal secundária

        // Verifica limites
        if (i < 0 || i >= 10 || j < 0 || j >= 10) return 0;
        // Verifica sobreposição
        if (tabuleiro[i][j] != 0) return 0;
    }
    return 1;
}

// Função para posicionar o navio no tabuleiro
void posicionarNavio(int tabuleiro[10][10], int linha, int coluna, int tamanho, int direcao) {
    for (int k = 0; k < tamanho; k++) {
        if (direcao == 0) tabuleiro[linha][coluna + k] = 3;          // horizontal
        else if (direcao == 1) tabuleiro[linha + k][coluna] = 3;     // vertical
        else if (direcao == 2) tabuleiro[linha + k][coluna + k] = 3; // diagonal principal
        else if (direcao == 3) tabuleiro[linha + k][coluna - k] = 3; // diagonal secundária
    }
}

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

    // ===== CÓDIGO ANTIGO (comentado) =====
    // int navioHorizontal[3] = {3, 3, 3};
    // int navioVertical[3]   = {3, 3, 3};
    // int linhaHorizontal = 2;
    // int colunaHorizontal = 4;
    // int linhaVertical = 5;
    // int colunaVertical = 7;
    // for (int k = 0; k < 3; k++) {
    //     tabuleiro[linhaHorizontal][colunaHorizontal + k] = navioHorizontal[k];
    // }
    // for (int k = 0; k < 3; k++) {
    //     tabuleiro[linhaVertical + k][colunaVertical] = navioVertical[k];
    // }

    // ===== NOVO POSICIONAMENTO =====
    int tamanho = 3;

    // Navio horizontal
    if (podePosicionar(tabuleiro, 2, 4, tamanho, 0))
        posicionarNavio(tabuleiro, 2, 4, tamanho, 0);

    // Navio vertical
    if (podePosicionar(tabuleiro, 5, 7, tamanho, 1))
        posicionarNavio(tabuleiro, 5, 7, tamanho, 1);

    // Navio diagonal principal (↘)
    if (podePosicionar(tabuleiro, 0, 0, tamanho, 2))
        posicionarNavio(tabuleiro, 0, 0, tamanho, 2);

    // Navio diagonal secundária (↙)
    if (podePosicionar(tabuleiro, 0, 9, tamanho, 3))
        posicionarNavio(tabuleiro, 0, 9, tamanho, 3);

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
