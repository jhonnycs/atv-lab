#include <stdio.h>

/*
    Implementar uma função que recebe um número inteiro e imprime
    ou retorna 1 se for primo, imprime ou retorna 0 caso contrário.
*/

int isPrime(int num);

int main() {

    int num;

    printf("Digite um número para saber se é primo:\n> ");
    scanf("%d", &num);

    while (num < 1) {
        printf("Digite um número positivo:\n> ");
        scanf("%d", &num);
    }

    int numIsPrime = isPrime(num);

    printf("\nResultado: %d\n", numIsPrime);
    printf("O número %d%sé primo.\n\n", num, numIsPrime ? " " : " não ");
    
    return 0;
}

int isPrime(int num) {
    if (num == 1) return 0;
    
    for (int i = 2; i < num / 2; i++) {
        if (num % i == 0) return 0;
    }

    return 1;
}