#include <stdio.h>

void apply(int *array, int (*applicable)(int), int size);

int applicable(int value);

void printArray(int array[], int size);

int main() {
    int array[] = {1, -2, 3, 5, 6};

    int (*pApplicable)(int) = applicable;

    apply(array, applicable, sizeof(array) / sizeof(array[0]));

    printArray(array, sizeof(array) / sizeof(array[0]));

    return 0;
}

int applicable(int value) {
    return value * value;
}

void apply(int *array, int (*applicable)(int), int size) {
    for (int i = 0; i < size; i++) {
        array[i] = applicable(array[i]);
    }
}

void printArray(int array[], int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", array[i]);
    }
}
