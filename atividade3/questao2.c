#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void preencherArray(int min, int max, int *array, int tamanhoArray);
void printArray(int *array, int tamanhoArray);
void copiarArray(int *arrayOrig, int *arrayCopy, int tamanhoArray);
void bubbleSort(int *array, int tamanhoArray);
void selectionSort(int *array, int tamanhoArray);
void insertionSort(int *array, int tamanhoArray);

int main() {
    srand(time(NULL));

    int array[200];
    const int tamanhoArray = sizeof(array) / sizeof(array[0]);
    preencherArray(0, 99, array, tamanhoArray);

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

void preencherArray(int min, int max, int *array, int tamanhoArray) {
    for (int i = 0; i < tamanhoArray; i++) {
        int numero = (rand() % (max - min + 1)) + min;
        array[i] = numero;
    }
}

void printArray(int *array, int tamanhoArray) {
    for (int i = 0; i < tamanhoArray; i++) {
        printf("%d %s", array[i], i > 0 && ((i + 1) % 25 == 0) ? "\n" : "");
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