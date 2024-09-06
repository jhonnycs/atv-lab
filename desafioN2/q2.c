#include <stdio.h>

int count(int *array, int (*condition)(int), int size);

int condition(int value);

int main() {
    int array[] = {1, -2, 3, 5, 6};

    int (*pCondition)(int) = condition;

    int result = count(array, pCondition, sizeof(array) / sizeof(array[0]));

    printf("O resultado da contagem é %d par%s.", result, result > 1 ? "es" : "");

    return 0;
}

int condition(int value) { // verifica se é par
    return value % 2 == 0 ? 1 : 0;
}

int count(int *array, int (*condition)(int), int size) {
    int count = 0;
    for (int i = 0; i < size; i++) {
        if (condition(array[i])) {
            count++;
        }
    }
    return count;
}