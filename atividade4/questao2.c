#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void mostrarArray(int *array, int tamanhoArray);
int gerarNumeroAleatorio(int min, int max);
void gerarSenhas();
void mostrarSenhas();

#define NUMERO_SENHAS 10

#define VALOR_MINIMO 0
#define VALOR_MAXIMO 99

int senhasNormais[NUMERO_SENHAS];
int senhasPrioridade[NUMERO_SENHAS];

int ultimaSenhaNormal = 0;
int ultimaSenhaPrioridade = 1000;

int quantSenhasNormais = 0;
int quantSenhasPrioridade = 0;

int main() {
    srand(time(NULL));

    gerarSenhas();
    mostrarSenhas();

    return 0;
}

int gerarNumeroAleatorio(int min, int max) {
    return (rand() % (max - min + 1)) + min;
}

void mostrarArray(int *array, int tamanhoArray) {
    for (int i = 0; i < tamanhoArray; i++) {
        printf("%d  %s", array[i], i > 0 && ((i + 1) % 20 == 0) ? "\n" : "");
    }
}

void gerarSenhas() {
    for (int i = 0; i < NUMERO_SENHAS; i++) {
        int tipoSenha = gerarNumeroAleatorio(VALOR_MINIMO, VALOR_MAXIMO);

        if (tipoSenha <= 66) {
            senhasNormais[quantSenhasNormais] = ++ultimaSenhaNormal;
            quantSenhasNormais++;
            
        } else {
            senhasPrioridade[quantSenhasPrioridade] = ++ultimaSenhaPrioridade;
            quantSenhasPrioridade++;
        }
    }
}

void mostrarSenhas() {
    printf("Senhas normais:\n ");
    mostrarArray(senhasNormais, quantSenhasNormais);

    printf("\n\nSenhas de prioridade:\n");
    mostrarArray(senhasPrioridade, quantSenhasPrioridade);
    printf("\n\n");
}