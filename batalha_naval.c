#include <stdio.h>
#include <stdlib.h>

// ============================================================
// Funções para navios
// ============================================================

int podePosicionar(int tabuleiro[10][10], int linha, int coluna, int tamanho, int direcao) {
    // direcao: 0 = horizontal, 1 = vertical, 2 = diagonal principal (↘), 3 = diagonal secundária (↙)
    for (int k = 0; k < tamanho; k++) {
        int i = linha, j = coluna;
        if (direcao == 0) j += k;
        else if (direcao == 1) i += k;
        else if (direcao == 2) { i += k; j += k; }
        else if (direcao == 3) { i += k; j -= k; }

        if (i < 0 || i >= 10 || j < 0 || j >= 10) return 0;
        if (tabuleiro[i][j] != 0) return 0;
    }
    return 1;
}

void posicionarNavio(int tabuleiro[10][10], int linha, int coluna, int tamanho, int direcao) {
    for (int k = 0; k < tamanho; k++) {
        if (direcao == 0) tabuleiro[linha][coluna + k] = 3;
        else if (direcao == 1) tabuleiro[linha + k][coluna] = 3;
        else if (direcao == 2) tabuleiro[linha + k][coluna + k] = 3;
        else if (direcao == 3) tabuleiro[linha + k][coluna - k] = 3;
    }
}

// ============================================================
// Habilidades (matrizes 5x5 com 0/1)
// ============================================================

// Cone apontando para baixo: 3 linhas ativas (topo até o centro), como no exemplo.
// 0 0 1 0 0
// 0 1 1 1 0
// 1 1 1 1 1
// 0 0 0 0 0
// 0 0 0 0 0
void construirCone(int tamanho, int matriz[tamanho][tamanho]) {
    int centro = tamanho / 2; // para 5, centro = 2
    for (int i = 0; i < tamanho; i++) {
        for (int j = 0; j < tamanho; j++) {
            if (i <= centro && abs(j - centro) <= i) matriz[i][j] = 1;
            else matriz[i][j] = 0;
        }
    }
}

// Cruz: linha central e coluna central
void construirCruz(int tamanho, int matriz[tamanho][tamanho]) {
    int centro = tamanho / 2;
    for (int i = 0; i < tamanho; i++) {
        for (int j = 0; j < tamanho; j++) {
            if (i == centro || j == centro) matriz[i][j] = 1;
            else matriz[i][j] = 0;
        }
    }
}

// Octaedro (losango) com distância de Manhattan, raio = 2 para 5x5
void construirOctaedro(int tamanho, int matriz[tamanho][tamanho]) {
    int centro = tamanho / 2;
    int raio = tamanho / 2; // para 5, raio = 2
    for (int i = 0; i < tamanho; i++) {
        for (int j = 0; j < tamanho; j++) {
            int dist = abs(i - centro) + abs(j - centro);
            if (dist <= raio) matriz[i][j] = 1;
            else matriz[i][j] = 0;
        }
    }
}

// ============================================================
// Aplicar habilidades no tabuleiro (marca 5 sem sobrescrever navios)
// ============================================================

void aplicarHabilidadeNoTabuleiro(
    int tabuleiro[10][10],
    int tamanho,
    int matriz[tamanho][tamanho],
    int origI,
    int origJ
) {
    int centro = tamanho / 2; // índice do centro da forma
    for (int i = 0; i < tamanho; i++) {
        for (int j = 0; j < tamanho; j++) {
            if (matriz[i][j] == 1) {
                int bi = origI + (i - centro); // traduz a forma para o tabuleiro
                int bj = origJ + (j - centro);
                if (bi >= 0 && bi < 10 && bj >= 0 && bj < 10) {
                    if (tabuleiro[bi][bj] == 0) tabuleiro[bi][bj] = 5; // não sobrescreve navio (3)
                }
            }
        }
    }
}

// ============================================================
// Impressões
// ============================================================

void imprimirTabuleiro(int tabuleiro[10][10]) {
    char colunas[10] = {'A','B','C','D','E','F','G','H','I','J'};
    printf("\n=== Tabuleiro Batalha Naval (0=água, 3=navio, 5=habilidade) ===\n\n");
    printf("   ");
    for (int j = 0; j < 10; j++) printf(" %c ", colunas[j]);
    printf("\n");
    for (int i = 0; i < 10; i++) {
        printf("%2d ", i);
        for (int j = 0; j < 10; j++) printf(" %d ", tabuleiro[i][j]);
        printf("\n");
    }
}

void imprimirMatriz(int tamanho, int matriz[tamanho][tamanho], const char *nome) {
    printf("\nMatriz %s (%dx%d):\n", nome, tamanho, tamanho);
    for (int i = 0; i < tamanho; i++) {
        for (int j = 0; j < tamanho; j++) printf("%d ", matriz[i][j]);
        printf("\n");
    }
}

// ============================================================
// Programa principal
// ============================================================

int main() {
    int tabuleiro[10][10];
    for (int i = 0; i < 10; i++)
        for (int j = 0; j < 10; j++)
            tabuleiro[i][j] = 0;

    // Navios (tamanho 3) — colocados para minimizar conflito com habilidades
    int TN = 3;
    // horizontal no rodapé
    if (podePosicionar(tabuleiro, 9, 1, TN, 0)) posicionarNavio(tabuleiro, 9, 1, TN, 0);
    // vertical no topo direito
    if (podePosicionar(tabuleiro, 0, 8, TN, 1)) posicionarNavio(tabuleiro, 0, 8, TN, 1);
    // diagonal principal no canto inferior-esquerdo
    if (podePosicionar(tabuleiro, 6, 0, TN, 2)) posicionarNavio(tabuleiro, 6, 0, TN, 2);
    // diagonal secundária no canto inferior-direito
    if (podePosicionar(tabuleiro, 6, 9, TN, 3)) posicionarNavio(tabuleiro, 6, 9, TN, 3);

    // Matrizes de habilidade (5x5)
    const int T = 5;
    int cone[T][T], cruz[T][T], octaedro[T][T];
    construirCone(T, cone);
    construirCruz(T, cruz);
    construirOctaedro(T, octaedro);

    // Valide as formas isoladas
    imprimirMatriz(T, cone, "Cone");
    imprimirMatriz(T, cruz, "Cruz");
    imprimirMatriz(T, octaedro, "Octaedro");

    // Aplicar habilidades em pontos com espaço livre, centradas
    aplicarHabilidadeNoTabuleiro(tabuleiro, T, cone, 2, 2);    // cone no quadrante superior-esquerdo
    aplicarHabilidadeNoTabuleiro(tabuleiro, T, cruz, 2, 7);    // cruz no quadrante superior-direito
    aplicarHabilidadeNoTabuleiro(tabuleiro, T, octaedro, 6, 5);// losango na metade inferior

    // Tabuleiro final
    imprimirTabuleiro(tabuleiro);

    return 0;
}