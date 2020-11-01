#include <stdio.h>
#include <stdlib.h>
#include "rb.h"

int main(int argc, char *argv[]) {

    arvore a;
    int opcao;
    inicializar(&a);

    while(1) {
        scanf("%d", &opcao);
        switch(opcao) {
            int n;
            case 1:
            	    //printf("\n ALTURA: \n");
                    printf("%d\n", altura(a));
                    break;
            case 2:
                    scanf("%d", &n);
                    inserir(n, &a);
                    break;
            case 3:
            	    //printf("\n MAIOR ELEMENTO: \n");
                    printf("%d\n", maior_elemento(a));
                    break;
            case 4:
            	    //printf("\n MENOR ELEMENTO: \n");
                    printf("%d\n", menor_elemento(a));
                    break;
            case 5:
            		//printf("\n PRE ORDER: \n");
                    pre_order(a);
                    printf("\n");
                    break;
            case 6:
            		//printf("\n IN ORDER: \n");
                    in_order(a);
                    printf("\n");
                    break;
            case 7:
            		//printf("\n POS ORDER: \n");
                    pos_order(a);
                    printf("\n");
                    break;
            case 8:
            		//printf("\n REMOVER: %d\n", n);
                    scanf("%d", &n);
                    remover(n, &a);
                    break;
            case 9:
            		//printf("\n IMPRIMIR: \n");
                    imprimir(a);
                    printf("\n");
                    break;

            case 99:
                    exit(0);

        }

    }

}
