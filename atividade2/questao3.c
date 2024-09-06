#include <stdio.h>

/*
    Implementar uma função que recebe dois números inteiros e
    imprime o primeiro elevado ao segundo
*/

float pot(int num1, int num2);

int main() {

    int num1, num2;

    printf("Digite o número 1:\n> ");
    scanf("%d", &num1);

    printf("Digite o número 2:\n> ");
    scanf("%d", &num2);

    while (num1 == 0 && num2 <= 0) {
        printf("\n0^0 é indeterminado. 1/0 também. Escolha novos valores.\n");
        printf("Digite o número 1:\n> ");
        scanf("%d", &num1);

        printf("Digite o número 2:\n> ");
        scanf("%d", &num2);
    }

    float resultPot = pot(num1, num2);

    printf("%d ^ %d = %f\n\n", num1, num2, resultPot);
    
    return 0;
}

float pot(int num1, int num2) {
    int multiplicador = num1;
    if (num2 > 0) {
        while (num2 > 1) {
            num1 = num1 * multiplicador;
            num2--;
        }
        return num1;
    } else if (num2 < 0) {
        float num1F = 1 / (float)num1;
        float multiplicador = num1F;
        while (num2 < -1) {
            num1F = num1F * multiplicador;
            num2++;
        }
        return num1F;
    } else {
        return 1;
    }
}