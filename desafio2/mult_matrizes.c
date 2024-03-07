#include <stdio.h>

/*
    Implementar a multiplicação de matrizes.
    O usuário deve escolher o tamanho das matrizes
    Matriz 1: m x n
    Matriz 2: n x z

    Para resolver esse desafio, fiz no papel a multiplicação de duas
    matrizes A(m x n), B(n x z) que resulta numa matriz R(m x z).
    Observei que o resultado de um elemento qualquer de R possui n somas.
    Observei que um elemento r(i, j) qualquer de Rs é o resultado do somatório:
    soma de p termos variando de 1 até n, a(i, p) * b(p, j).
    Sabendo disso, só implementar em código esse somatório, que gera 3 fors aninhados.
*/
void capturarMatriz(int linhas, int colunas, int matriz[linhas][colunas]);
void exibirMatriz(int linhas, int colunas, int matriz[linhas][colunas]);

int main() {
    int m, n, z;

    printf("Digite o número de linhas da matriz 1:\n> ");
    scanf("%d", &m);
    while (m < 1) {
        printf("Digite um número positivo de linhas:\n> ");
        scanf("%d", &m);
    }
    
    printf("Digite o número de colunas da matriz 1:\n> ");
    scanf("%d", &n);
    while (n < 1) {
        printf("Digite um número positivo de colunas:\n> ");
        scanf("%d", &n);
    }

    printf("Digite o número de colunas da matriz 2:\n> ");
    scanf("%d", &z);
    while (z < 1) {
        printf("Digite um número positivo de colunas:\n> ");
        scanf("%d", &z);
    }

    int matriz1[m][n]; // matriz que será multiplicada à esquerda
    int matriz2[n][z]; // matriz que será multiplicada à direita

    int matrizR[m][z]; // matriz resultado

    printf("******************************\n");
    printf("Digite os valores da matriz 1\n");
    capturarMatriz(m, n, matriz1);

    printf("\n******************************\n");
    printf("Digite os valores da matriz 2\n");
    capturarMatriz(n, z, matriz2);

    printf("\nMatriz 1:\n");
    exibirMatriz(m, n, matriz1);

    printf("\n\nMatriz 2:\n");
    exibirMatriz(n, z, matriz2);
    printf("\n");

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < z; j++) {
            matrizR[i][j] = 0; // inicio o elemento ij com 0
            for (int k = 0; k < n; k++) {
                // para cada valor ij, somo o valor ij com o resultado da multiplicação p do somatório
                // de 1 até n
                matrizR[i][j] += matriz1[i][k] * matriz2[k][j];
            }
        }
    }

    printf("Matriz resultante:\n");
    exibirMatriz(m, z, matrizR);
    return 0;
}

void capturarMatriz(int linhas, int colunas, int matriz[linhas][colunas]) {
    for (int i = 0; i < linhas; i++) {
        for (int j = 0; j < colunas; j++) {
            printf("valor [%d,%d] da matriz: ", i+1, j+1);
            scanf("%d", &matriz[i][j]);
        }
    }
}

void exibirMatriz(int linhas, int colunas, int matriz[linhas][colunas]) {
    for (int i = 0; i < linhas; i++) {
        for (int j = 0; j < colunas; j++) {
            printf("%d     ", matriz[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}
