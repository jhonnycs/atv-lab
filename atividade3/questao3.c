#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/*
    Reaproveitei as funções de preencher o array, ordenar e
    mostrar na tela.

    Implementei a função de busca binária. Ela vai basicamente
    procurar no array um dado valor. Para isso, ela divide o array
    em dois e olha para o valor do meio do array. Se o valor do meio
    for o que buscamos, retorna o índice dele. Se o valor em busca
    for menor que o valor do meio, olha-se para a parte esquerda dos
    dois arrays, sendo esse agora o array completo para a busca.
    Se o valor em busca for maior que o valor do meior, agora olhamos
    para o array da direita, sendo esse agora o novo array para realizar
    a busca. Fazemos isso até encontrar o valor ou até se esgorarem os
    valores do array, sendo o retorno nesse caso, o -1, um índice inválido.    
*/

void preencherArray(int *array, int tamanhoArray, int min, int max);
void insertionSort(int *array, int tamanhoArray);
void printArray(int *array, int tamanhoArray);
int gerarNumeroAleatorio(int min, int max);
int buscaBinaria(int *array, int tamanhoArray, int valorABuscar);

#define VALOR_MINIMO_ARRAY 0
#define VALOR_MAXIMO_ARRAY 99

#define VALOR_MINIMO_BUSCA 50
#define VALOR_MAXIMO_BUSCA 150

#define QUANT_REPETICOES_BUSCA 10

int main() {
    srand(time(NULL));
    int array[101];
    int tamanhoArray = sizeof(array) / sizeof(array[0]);

    preencherArray(array, tamanhoArray, VALOR_MINIMO_ARRAY, VALOR_MAXIMO_ARRAY);
    insertionSort(array, tamanhoArray);
    printf("\nArray já ordenado:\n\n");
    printArray(array, tamanhoArray);
    printf("\n");

    for (int i = 0; i < QUANT_REPETICOES_BUSCA; i++) {
        int numRandom = gerarNumeroAleatorio(VALOR_MINIMO_BUSCA, VALOR_MAXIMO_BUSCA);
        int indexAchado = buscaBinaria(array, tamanhoArray, numRandom);

        // verifica se achou ou não o valor no array
        if (indexAchado >= 0) {
            printf("\nO valor %d foi encontrado no index %d\n", numRandom, indexAchado);
        } else {
            printf("\nO valor %d não foi encontrado no array\n", numRandom);
        }
    }

    return 0;
}

void preencherArray(int *array, int tamanhoArray, int min, int max) {
    for (int i = 0; i < tamanhoArray; i++) {
        int numero = (rand() % (max - min + 1)) + min;
        array[i] = numero;
    }
}


void insertionSort(int *array, int tamanhoArray) {
    for (int i = 1; i < tamanhoArray; i++) {
        if (array[i - 1] > array[i]) {
            int aux = array[i];
            int j = i;
            while (j > 0 && array[j - 1] > array[j]) {
                array[j] = array[j - 1];
                array[j - 1] = aux;
                j--;
            }
        }
    }
}

void printArray(int *array, int tamanhoArray) {
    for (int i = 0; i < tamanhoArray; i++) {
        printf("%d  %s", array[i], i > 0 && ((i + 1) % 20 == 0) ? "\n" : "");
    }
}

int gerarNumeroAleatorio(int min, int max) {
    return (rand() % (max - min + 1)) + min;
}

int buscaBinaria(int *array, int tamanhoArray, int valorABuscar) {
    int indexLeft = 0;
    int indexRight = tamanhoArray-1;
    int indexMeio = (indexLeft + indexRight) / 2;

    while (indexLeft <= indexMeio) {
        if (valorABuscar == array[indexMeio]) {
            return indexMeio;
        }

        if (valorABuscar > array[indexMeio]) {
            indexLeft = indexMeio + 1;
        } else {
            indexRight = indexMeio - 1;
        }

        indexMeio = (indexLeft + indexRight) / 2;
    }
    return -1;
}