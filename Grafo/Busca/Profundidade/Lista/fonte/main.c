//Busca em Profundidade no Grafo - Lista
#include <stdio.h>
#include <stdlib.h>
#include "grafoLista.h"

int main(int argc, char * argv[]){
	grafo g;
	char arquivo[15] = "grafo.txt";
    char nome;
    int opcao;
    vertice* v;

     printf("\n1 - INICIALIZAR GRAFO \n2 - IMPRIMIR LISTA DE ADJACENCIAS \n3 - BUSCA EM PROFUNDIDADE \n99 - SAIR\n");
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
                //Busca em profundidade
                scanf(" %c", &nome);
                v = procurarVertice(&g, nome);
                DSF(&g, v);
                break;

            case 99:
                exit(0);
        }
    }
}
