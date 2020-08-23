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
        switch(opcao){
            int chave;
            case 1:
                scanf("%d", &chave);
                raiz = inserir(raiz, chave);
                break;

            case 2:
                //printf("\nPre order: \n");
                preOrder(raiz);
                break;

            case 3:
                //printf("\nIn order: \n");
                inOrder(raiz);
                break;

            case 4:
                //printf("\nPos order: \n");
                posOrder(raiz);
                break;

            default:
                ;
        }
    } while(opcao != 99);

    printf("\n");
}
