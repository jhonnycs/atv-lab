#include <stdio.h>

int filter(int *array, int (*condition)(int), int size);

int condition(int value);

void printArray(int array[], int size);

int main() {
    int array[] = {8, -2, 3, 5, 6};

    int (*pCondition)(int) = condition;

    int result = filter(array, pCondition, sizeof(array) / sizeof(array[0]));

    printf("Novo tamanho do array: %d\n", result);

    printArray(array, result);

    return 0;
}

int condition(int value) { // verifica se é par
    return value % 2 == 0 ? 1 : 0;
}

int filter(int *array, int (*condition)(int), int size) {
    int newSize = 0;
    
    for (int i = 0; i < size; i++) {
        if (condition(array[i])) {
            array[newSize++] = array[i];
        }
    }
    return newSize;
}

void printArray(int array[], int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", array[i]);
    }
}