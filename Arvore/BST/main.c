#include <stdio.h>
#include <stdlib.h>
#include "BST.h"    //procura no mesmo diretorio

void main(){

	NO* arvore;
    // inicialização da arvore
	arvore = NULL;

    int opcao;
    do {
        scanf("%d", &opcao);
        int chave;
        switch(opcao){
            case 1:
                scanf("%d", &chave);
                arvore = inserir(arvore, chave);
                break;

            case 2:
                printf("\nPre order: \n");
                preOrder(arvore);
                printf("\n");
                break;

            case 3:
                printf("\nIn order: \n");
                inOrder(arvore);
                printf("\n");
                break;

            case 4:
                printf("\nPos order: \n");
                posOrder(arvore);
                printf("\n");
                break;

            case 5:
                scanf("%d", &chave);
                remover(arvore, chave);
                break;

            case 6:
                printf("\nMaior elemento: \n");
                printf("%d", maior(arvore));
                printf("\n");
                break;

            case 7:
                printf("\nMenor elemento: \n");
                printf("%d", menor(arvore));
                printf("\n");
                break;

            case 8:
                printf("\nAltura: \n");
                printf("%d", altura(arvore));
                printf("\n");
                break;

            case 9:
                printf("\nQuantidade de elementos \n");
                printf("%d", quantidade_elementos(arvore));
                printf("\n");
                break;

            case 10:
                scanf("%d", &chave);
                printf("\nExiste \n");
                printf("%d", existe(arvore, chave));
                printf("\n");
                break;

            case 11:
                scanf("%d", &chave);
                printf("\nPredecessor: \n");
                printf("%d", predecessor(arvore, chave));
                printf("\n");
                break;

            case 12:
                scanf("%d", &chave);
                printf("\nSucessor: \n");
                printf("%d", sucessor(arvore, chave));
                printf("\n");
                break;

            default:
                ;
        }
    } while(opcao != 99);

    printf("\n");
}
