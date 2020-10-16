#include <stdio.h>
#include <stdlib.h>
#include "avl.h"

int main(int argc, char * argv[]) {
	arvore a;
	int opcao;
    int controleFB;
	inicializar(&a);

    printf(" 1 - ADICIONAR \n 2 - PRE-ORDER \n 3 - IN-ORDER \n 4 - POS-ORDER \n 5 - SALVAR-ARQUIVO \n 6 - CARREGAR ARQUIVO \n 99 - SAIR \n");

	while(1) {
		scanf("%d", &opcao);

		switch(opcao) {
				int valor;

				case 1:
						a = adicionar(ler_dados(), a, &controleFB);
						break;
				case 2:
						pre_order(a);
						printf("\n");
						break;
				case 3:
						in_order(a);
						printf("\n");
						break;
				case 4:
						pos_order(a);
						printf("\n");
						break;
				case 5:
						salvar_arquivo("dados.dat", a);
						break;

				case 6:
						a = carregar_arquivo("dados.dat", a, &controleFB);
						break;
				case 99:
						exit(0);
		}
	}
}
