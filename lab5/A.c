#include <stdio.h>
#include <stdlib.h>

void calcInvIPCA( int numMeses) {
    float *ipca = (float*) malloc(numMeses * sizeof(float));

    if (ipca == NULL) {
        printf("Erro na alocação de memória!\n");
        return;
    }

    for (int i = 0; i < numMeses; i++) {
        ipca[i] = ((float)rand() / RAND_MAX) * 0.10;
        printf("%f, ", ipca[i]);
    }

    free(ipca);
}

int main() {

    calcInvIPCA(250);

    return 0;
}