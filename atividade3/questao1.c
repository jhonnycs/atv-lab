#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void preencherArray(int min, int max, int *array, int tamanhoArray);
void printArray(int *array, int tamanhoArray);

int main() {
    srand(time(NULL));

    int array[100];
    int tamanhoArray = sizeof(array) / sizeof(array[0]);

    preencherArray(50, 295, array, tamanhoArray);

    printArray(array, tamanhoArray);

    return 0;
}

void preencherArray(int min, int max, int *array, int tamanhoArray) {

    for (int i = 0; i < tamanhoArray; i++) {
        int numero = (rand() % (max - min + 1)) + min;
        array[i] = numero;
    }
}

void printArray(int *array, int tamanhoArray) {
    for (int i = 0; i < tamanhoArray; i++) {
        printf("%d %s", array[i], i > 0 && ((i + 1) % 10 == 0) ? "\n" : "");
    }
    // cada vez que o i iterar 10 vezes, irá quebrar a linha para facilitar
    // a visualização
}