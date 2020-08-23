#include <stdio.h>
#include <stdlib.h>
#include "BST.h"    //procura no mesmo diretorio

//int main(int argc, char *argv[]){}
void main(){

	NO* raiz;
    // inicialização da arvore
	raiz = NULL;

    int opcao;
    do {
        scanf("%d", &opcao);
        int chave;
        switch(opcao){
            case 1:
                scanf("%d", &chave);
                raiz = inserir(raiz, chave);
                break;

            case 2:
                printf("\nPre order: \n");
                preOrder(raiz);
                printf("\n");
                break;

            case 3:
                printf("\nIn order: \n");
                inOrder(raiz);
                printf("\n");
                break;

            case 4:
                printf("\nPos order: \n");
                posOrder(raiz);
                printf("\n");
                break;

            case 5:
                scanf("%d", &chave);
                raiz = remover(raiz, chave);
                break;

            case 6:
                printf("\nMaior elemento: \n");
                printf("%d", maior(raiz));
                printf("\n");
                break;

            case 7:
                printf("\nMenor elemento: \n");
                printf("%d\n",menor(raiz));
                printf("\n");
                break;

            default:
                ;
        }
    } while(opcao != 99);

    printf("\n");
}
