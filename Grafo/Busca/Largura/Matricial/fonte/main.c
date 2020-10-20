//Busca em Largura no Grafo - Matricial
#include "grafoMatriz.h"
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char * argv[]) {
	grafo g;
	char arquivo[15] = "grafo.txt";
    int opcao;
    char nome;
    vertice* v;

    printf("\n1 - INICIALIZAR GRAFO \n2 - IMPRIMIR LISTA DE ADJACENCIAS \n3 - BUSCA EM LARGURA \n99 - SAIR\n");
    while(1){
        scanf("%d", &opcao);
        switch(opcao){
            case 1:
                //Inicializar o grafo a partir do arquivo
                inicializarGrafo(&g, arquivo);
                lerArquivo(&g);
                lerVertices(&g);
                lerArestas(&g);
                break;

            case 2:
                //Imprimir lista de Adjacencias
                imprimirListaAdj(&g);
                break;

            case 3:
                //Busca em Largura
                printf("\nVERTICE A SER BUSCADO:\n");
                scanf(" %c", &nome);
                v = buscarVertice(&g, nome);
                buscaLargura(&g, v);
                break;

            case 99:
                exit(0);
        }
    }
}
