#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define TAM 10
#define TAM_HAB 5

// Função para inicializar o tabuleiro
void inicializar_tabuleiro(int tab[TAM][TAM]) {
    for (int i = 0; i < TAM; i++)
        for (int j = 0; j < TAM; j++)
            tab[i][j] = 0;
}

// Função para exibir o tabuleiro com legenda
void exibir_tabuleiro(int tab[TAM][TAM]) {
    printf("\nLegenda: 0 = Água | 3 = Navio | 5 = Habilidade\n\n");
    for (int i = 0; i < TAM; i++) {
        for (int j = 0; j < TAM; j++) {
            printf("%2d ", tab[i][j]);
        }
        printf("\n");
    }
}

// Função para posicionar navio horizontal
void navio_horizontal(int tab[TAM][TAM], int lin, int col) {
    for (int i = 0; i < 3; i++)
        if (col + i < TAM)
            tab[lin][col + i] = 3;
}

// Função para posicionar navio vertical
void navio_vertical(int tab[TAM][TAM], int lin, int col) {
    for (int i = 0; i < 3; i++)
        if (lin + i < TAM)
            tab[lin + i][col] = 3;
}

// Função para sobrepor habilidade ao tabuleiro
void aplicar_habilidade(int tab[TAM][TAM], int habilidade[TAM_HAB][TAM_HAB], int origem_l, int origem_c) {
    int offset = TAM_HAB / 2;

    for (int i = 0; i < TAM_HAB; i++) {
        for (int j = 0; j < TAM_HAB; j++) {
            int x = origem_l - offset + i;
            int y = origem_c - offset + j;

            if (x >= 0 && x < TAM && y >= 0 && y < TAM) {
                if (habilidade[i][j] == 1 && tab[x][y] == 0)
                    tab[x][y] = 5;
            }
        }
    }
}

// Gera matriz de habilidade em cone (↓)
void gerar_cone(int hab[TAM_HAB][TAM_HAB]) {
    for (int i = 0; i < TAM_HAB; i++)
        for (int j = 0; j < TAM_HAB; j++)
            hab[i][j] = (j >= TAM_HAB / 2 - i && j <= TAM_HAB / 2 + i) ? 1 : 0;
}

// Gera matriz de habilidade em cruz
void gerar_cruz(int hab[TAM_HAB][TAM_HAB]) {
    for (int i = 0; i < TAM_HAB; i++)
        for (int j = 0; j < TAM_HAB; j++)
            hab[i][j] = (i == TAM_HAB / 2 || j == TAM_HAB / 2) ? 1 : 0;
}

// Gera matriz de habilidade em octaedro (losango)
void gerar_octaedro(int hab[TAM_HAB][TAM_HAB]) {
    for (int i = 0; i < TAM_HAB; i++)
        for (int j = 0; j < TAM_HAB; j++)
            hab[i][j] = (abs(i - TAM_HAB / 2) + abs(j - TAM_HAB / 2) <= TAM_HAB / 2) ? 1 : 0;
}

int main() {
    int tabuleiro[TAM][TAM];
    inicializar_tabuleiro(tabuleiro);

    // Posicionamento fixo dos navios
    navio_horizontal(tabuleiro, 2, 3);  // Navio 1
    navio_vertical(tabuleiro, 6, 1);    // Navio 2

    // Matrizes de habilidades
    int cone[TAM_HAB][TAM_HAB], cruz[TAM_HAB][TAM_HAB], octaedro[TAM_HAB][TAM_HAB];

    gerar_cone(cone);
    gerar_cruz(cruz);
    gerar_octaedro(octaedro);

    // Aplicar habilidades
    aplicar_habilidade(tabuleiro, cone, 1, 5);      // Cone no topo central
    aplicar_habilidade(tabuleiro, cruz, 5, 5);      // Cruz no meio
    aplicar_habilidade(tabuleiro, octaedro, 8, 8);  // Octaedro canto inferior direito

    // Exibir resultado final
    exibir_tabuleiro(tabuleiro);

    return 0;
}
