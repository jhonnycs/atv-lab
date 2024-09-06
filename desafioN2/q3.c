#include <stdio.h>

int reduce(int *array, int (*combine)(int, int), int size);

int combine(int value1, int value2);

int main() {
    int array[] = {1, -2, 3, 5, 6};

    int (*pCombine)(int, int) = combine;

    int result = reduce(array, pCombine, sizeof(array) / sizeof(array[0]));

    printf("%d\n", result);
    return 0;
}

int combine(int value1, int value2) {
    return value1 * value2;
}

int reduce(int *array, int (*combine)(int, int), int size) {
    while (size > 1) {
        array[size-2] = combine(array[size-1], array[size-2]);
        size--;
    }
    return array[0];
}