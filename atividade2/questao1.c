#include <stdio.h>
/*
    Implementar uma função recursiva que retorne o n-ésimo termo
    da sequência de fibonacci
*/

int fibonacci(int n);

int main() {

    int n;

    printf("Digite o índice do termo que você quer:\n> ");
    scanf("%d", &n);

    while (n < 1) {
        printf("Digite um índice positivo:\n> ");
        scanf("%d", &n);
    }
    
    int termoN = fibonacci(n);

    printf("\n%dº termo da sequência de fibonacci: %d\n\n", n, termoN);

    return 0;
}

int fibonacci(int n) {
    // os dois primeiros termos são 1
    if (n == 1 || n == 2) return 1;

    /*
        Aqui, inicializo o n-ésimo termo, o índice da iteração atual,
        o termo anterior ao n-ésimo termo e o termo anterior ao anterior.
        foi usado o static aqui pra que o valor não precise ser repassado pra
        função a cada novo cálculo
    */

    static int termoN = 0;
    static int i = 1;
    static int termoAnt = 1;
    static int termoAnt2 = 1;
    
    // a cada vez que a função se chama, o i incrementa
    // caso ele chegue a n-1, a função retornará o n-ésimo termo
    if (i == n-1) return termoN;
    
    termoN = termoAnt + termoAnt2;
    termoAnt2 = termoAnt;
    termoAnt = termoN;
    i++;
    fibonacci(n);
}