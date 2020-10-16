#include <stdio.h>
#include <stdlib.h>
#include "avl.h"
#include <string.h>

void inicializar(arvore *raiz) {
	*raiz = NULL;
}

arvore adicionar (tipo_dado *valor, arvore raiz, int *cresceu) {
	if(raiz == NULL) {
		arvore novo = (arvore) malloc(sizeof(struct no_avl));
		novo->dado = valor;
		novo->esq = NULL;
		novo->dir = NULL;
        novo->fb = 0;

        *cresceu = 1;
		return novo;
	}

	if(valor->codigo > raiz->dado->codigo) {
		raiz->dir = adicionar(valor, raiz->dir, cresceu);
	}
	if(*cresceu){
        switch(raiz->fb){
            case 0:
                raiz->fb = 1;
                *cresceu = 1;
                break;

            case -1:
                raiz->fb = 0;
                *cresceu = 0;
                break;

            case 1:
                raiz->fb = 0;
                *cresceu = 0;
                return rotacionar(raiz);
        }

    }

	else {
		raiz->esq = adicionar(valor, raiz->esq, cresceu);

        if(*cresceu){
        switch(raiz->fb){
            case 0:
                raiz->fb = -1;
                *cresceu = 1;
                break;

            case -1:
                raiz->fb = -2;
                *cresceu = 0;
                return rotacionar(raiz);

            case 1:
                raiz->fb = 0;
                *cresceu = 0;
            }

        }
	}
	return raiz;
}

//-------------------ROTAÇÕES----------------------------------
arvore rotacionar(arvore raiz) {
    //fb maior que zero => rotação esquerda
    if(raiz->fb >= 0){
        switch(raiz->dir->fb) {
            case 0:
                return rotacao_simples_esq_caso_remocao(raiz);
			case 1:
                //raiz->dir->fb == 1
				return rotacao_simples_esq(raiz);
			case -1:
                //raiz->dir->fb == -1
				return rotacao_dupla_esq(raiz);
        }
    } else{
        switch(raiz->esq->fb) {
            case 0:
               return rotacao_simples_dir_caso_remocao(raiz);
			case 1:
                //raiz->esq->fb == 1
				return rotacao_dupla_dir(raiz);
			case -1:
                //raiz->esq->fb == -1
				return rotacao_simples_dir(raiz);
        }
    }
}

arvore rotacao_simples_dir(arvore raiz) {

    arvore r = raiz->esq;

    r->fb = 0;
    raiz->fb = 0;
    raiz->esq = r->dir;
    r->dir = raiz;

    return r;
}
arvore rotacao_simples_esq(arvore raiz){

    arvore r = raiz->dir;

    r->fb = 0;
    raiz->fb = 0;
    raiz->dir = r->esq;
    r->esq = raiz;

    return r;
}

arvore rotacao_simples_esq_caso_remocao(arvore raiz){

    arvore r = raiz->dir;

    r->fb = -1;
    raiz->fb = 1;
    raiz->dir = r->esq;
    r->esq = r;
    return r;
}

arvore rotacao_simples_dir_caso_remocao(arvore raiz){

    arvore r = raiz->esq;

    r->fb = 1;
    raiz->fb = -1;
    raiz->esq = r->dir;
    r->dir = raiz;
    return r;
}

arvore rotacao_dupla_dir(arvore raiz){

    arvore r = raiz->esq;
    arvore s = r->dir;

    // Rotação à esquerda

    r->dir = s->esq;
    s->esq = r;
    raiz->esq = s;

    //Rotação á direita

    raiz->esq = s->dir;
    s->dir = raiz;

    //Atualizando os fatores de balanço
    if(s->fb == 0){
        r->fb = 0;
        raiz->fb=0;
        s->fb=0;
    }
    else if(s->fb==-1){

        r->fb = 0;
        s->fb = 0;
        raiz->fb=1;
    }
    else {
        r->fb = -1;
        s->fb = 0;
        raiz->fb=0;
    }
     return s;
}

arvore rotacao_dupla_esq(arvore raiz){

    arvore r = raiz->dir;
    arvore s = r->esq;

    //Rotação Direita
    r->esq = s->dir;
    s->dir = r;
    raiz->dir = s;

    //Rotação esquerda
    raiz->dir = s->esq;
    s->esq = raiz;

    //Atualizando os fatores de balanço
    if(s->fb == 0){
        r->fb = 0;
        s->fb = 0;
        raiz->fb = 0;

    }
    else if(s->fb == -1){

        r->fb = 1;
        s->fb = 0;
        raiz->fb = 0;
    }
     else{
        r->fb = 0;
        s->fb = 0;
        raiz->fb =-1;
    }
        return s;
}

///////////// IMPRESSÕES ///////////////////////////////////
void pre_order(arvore raiz) {
	if(raiz != NULL) {
		imprimir_elemento(raiz);
		pre_order(raiz->esq);
		pre_order(raiz->dir);
	}
}

void pos_order(arvore raiz) {
	if(raiz != NULL) {
		pos_order(raiz->esq);
		pos_order(raiz->dir);
		imprimir_elemento(raiz);
	}
}

void in_order(arvore raiz) {
	if(raiz != NULL) {
		in_order(raiz->esq);
		imprimir_elemento(raiz);
		in_order(raiz->dir);
	}
}

void imprimir_elemento(arvore raiz) {
	printf("[%d - %s] ", raiz->dado->codigo, raiz->dado->titulo);
}

///////////////////////////////////////////////////////////////

tipo_dado * ler_dados() {
	tipo_dado *novo = (tipo_dado *) malloc(sizeof(tipo_dado));
	getchar() ;
	printf("Titulo: ");
	fgets(novo->titulo, 80,  stdin);
	tirar_enter(novo->titulo);
	printf("Autor: ");
	fgets(novo->autor, 50,  stdin);
	printf("Ano: ");
	fgets(novo->ano, 20,  stdin);
	printf("Codigo: ");
	scanf("%d", &novo->codigo);
	return novo;
}

void tirar_enter(char *string) {
	string[strlen(string) -1] = '\0';
}

void salvar_arquivo(char *nome, arvore a) {
	FILE *arq;
	arq = fopen(nome, "wb");
	if(arq != NULL) {
		salvar_auxiliar(a, arq);
		fclose(arq);
	}
}

void salvar_auxiliar(arvore raiz, FILE *arq){
	if(raiz != NULL) {
		fwrite(raiz->dado, sizeof(tipo_dado), 1, arq);
		salvar_auxiliar(raiz->esq, arq);
		salvar_auxiliar(raiz->dir, arq);
	}

}

arvore carregar_arquivo(char *nome, arvore a, int *cresceu) {
	FILE *arq;
	arq = fopen(nome, "rb");
	tipo_dado * temp;
	if(arq != NULL) {
		temp = (tipo_dado *) malloc(sizeof(tipo_dado));
		while(fread(temp, sizeof(tipo_dado), 1, arq)) {

			a = adicionar(temp, a, cresceu);
			temp = (tipo_dado *) malloc(sizeof(tipo_dado));

		}
		fclose(arq);

	}
	return a;
}
