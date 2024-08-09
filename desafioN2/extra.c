#include <stdio.h>

int filter(int *array, int (*condition)(int), int size, int (*not_repeated)(int));
int condition(int value);
int not_repeated(int value);
void printArray(int array[], int size);

#define MAX_SIZE 1000
int seen[MAX_SIZE];
int seen_size = 0;

int main() {
    int array[] = {8, -2, 3, 5, 6, 8, -2, 6};

    int (*pCondition)(int) = condition;
    int (*pNotRepeated)(int) = not_repeated;

    int result = filter(array, condition, sizeof(array) / sizeof(array[0]), not_repeated);

    printf("Novo tamanho do array: %d\n", result);

    printArray(array, result);

    return 0;
}

int condition(int value) { // verifica se é par
    return value % 2 == 0 ? 1 : 0;
}

int not_repeated(int value) {
    for (int i = 0; i < seen_size; i++) {
        if (seen[i] == value) {
            return 0;
        }
    }
    seen[seen_size++] = value;
    return 1;
}

int filter(int *array, int (*condition)(int), int size, int (*not_repeated)(int)) {
    int newSize = 0;
    
    for (int i = 0; i < size; i++) {
        if (condition(array[i]) && not_repeated(array[i])) {
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