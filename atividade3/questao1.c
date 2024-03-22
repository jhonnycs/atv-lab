#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/*
    Aqui, a função preencherArray vai receber um array, seu tamanho, valor
    mínimo e valor máximo aleatório, e irá iterar de 0 até < tamanho,
    atribuindo a cada posição do array um número aleatório que irá variar do
    valor mínimo até o máximo.

    A função printArray mostrará na tela cada valor do array um após o outro,
    separados por dois espaços.
*/

void preencherArray(int *array, int tamanhoArray, int min, int max);
void printArray(int *array, int tamanhoArray);

#define VALOR_MINIMO 50
#define VALOR_MAXIMO 295


int main() {
    srand(time(NULL));

    int array[100];
    int tamanhoArray = sizeof(array) / sizeof(array[0]);

    preencherArray(array, tamanhoArray, VALOR_MINIMO, VALOR_MAXIMO);

    printArray(array, tamanhoArray);

    return 0;
}

void preencherArray(int *array, int tamanhoArray, int min, int max) {
    for (int i = 0; i < tamanhoArray; i++) {
        int numero = (rand() % (max - min + 1)) + min;
        array[i] = numero;
    }
}

void printArray(int *array, int tamanhoArray) {
    for (int i = 0; i < tamanhoArray; i++) {
        printf("%d  %s", array[i], i > 0 && ((i + 1) % 10 == 0) ? "\n" : "");
    }
    // cada vez que o i iterar 10 vezes, irá quebrar a linha para facilitar
    // a visualização
}