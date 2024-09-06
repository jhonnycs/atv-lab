#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/*
    Aqui, reaproveitei a função de preencher e printar o array na tela.
    Criei uma função que copia um dado array para outro array, para
    aplicar os algoritmos de ordenação com o mesmo array.
    Os algoritmos escolhidos, como o nome de cada função sugere, foram o bubble
    sort, o selection sort e o insertion sort.

    Bubble sort: percorrerá o array do índice 0
    até o penúltimo, comparando cada valor com o seu sucessor.
    Repetirá isso n-1 vezes, sendo n o tamanho do array

    Selection sort: itera por todo o array procurando o índice do menor
    elemento. Ao achá-lo, trocamos o elemento do array com esse índice com
    o elemento do primeiro índice do array, fazendo com que o menor elemento
    vá para a primeira posição do array. Depois disso, na próxima iteração,
    procuraremos o índice do segundo menor elemento, para trocá-lo com a segunda
    posição. Repetimos isso por n-1 vezes, sendo n o tamanho do array.

    Insertion sort: percorre o array começando da segunda posição até a última,
    comparando o elemento anterior ao atual na iteração. Se o elemento anterior for
    maior que o atual, volta pra trás em outro loop, trazendo pra trás esse
    elemento que é maior que o anterior. Fazemos isso até o anterior não for menor
    que o atual.
*/

void preencherArray(int *array, int tamanhoArray, int min, int max);
void printArray(int *array, int tamanhoArray);
void copiarArray(int *arrayOrig, int *arrayCopy, int tamanhoArray);
void bubbleSort(int *array, int tamanhoArray);
void selectionSort(int *array, int tamanhoArray);
void insertionSort(int *array, int tamanhoArray);

#define VALOR_MINIMO 100
#define VALOR_MAXIMO 999

int main() {
    srand(time(NULL));

    int array[200];
    const int tamanhoArray = sizeof(array) / sizeof(array[0]);
    preencherArray(array, tamanhoArray, VALOR_MINIMO, VALOR_MAXIMO);

    int array2[tamanhoArray];
    int array3[tamanhoArray];

    copiarArray(array, array2, tamanhoArray);
    copiarArray(array, array3, tamanhoArray);

    printf("\nArray antes de ser ordenado:\n\n");
    printArray(array, tamanhoArray);

    printf("\n\n\nArray ordenado com o bubble sort:\n\n");
    bubbleSort(array, tamanhoArray);
    printArray(array, tamanhoArray);
    
    printf("\n\n\nArray ordenado com o selection sort:\n\n");
    selectionSort(array2, tamanhoArray);
    printArray(array2, tamanhoArray);

    printf("\n\n\nArray ordenado com o insertion sort:\n\n");
    insertionSort(array3, tamanhoArray);
    printArray(array3, tamanhoArray);
    
    printf("\n\n");

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
        printf("%d  %s", array[i], i > 0 && ((i + 1) % 20 == 0) ? "\n" : "");
        // aumentei pra 20 a quantidade de valores
    }
}

void copiarArray(int *arrayOrig, int *arrayCopy, int tamanhoArray) {
    for (int i = 0; i < tamanhoArray; i++) {
        arrayCopy[i] = arrayOrig[i];
    }
}

void bubbleSort(int *array, int tamanhoArray) {
    for (int i = 0; i < tamanhoArray-1; i++) {
        for (int j = 0; j < tamanhoArray-1; j++) {
            if (array[j] > array[j+1]) {
                int temp = array[j];
                array[j] = array[j+1];
                array[j+1] = temp;
            }
        }
    }
}

void selectionSort(int *array, int tamanhoArray) {
    for (int i = 0; i < tamanhoArray-1; i++) {
        int indexMenorValor = i;

        for (int j = i; j < tamanhoArray; j++) {
            if (array[j] < array[indexMenorValor]) {
                indexMenorValor = j;
            }
        }

        if (array[i] > array[indexMenorValor]) {
            int temp = array[i];
            array[i] = array[indexMenorValor];
            array[indexMenorValor] = temp;
        }
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