#include <stdio.h>
#include <stdlib.h>
#include "BST.h"

NO* inserir(NO* r, int valor){
    //Caso base
	if(r == NULL){
    //1. alocar memoria
	NO* novo = (NO*) malloc(sizeof(NO));
    //2. inicializar valores
    novo->valor = valor;
	novo->esq = NULL;
	novo->dir = NULL;
    //3. retornar o ponteiro para o nó que foi criado
	return novo;
	}

	//Verificar se o valor deve ser inserido na esquerda(<) ou direita(>)
	if(valor > r->valor){
		r->dir = inserir(r->dir, valor);
	}else{
		r->esq = inserir(r->esq, valor);
	}

	return r;
}

void preOrder(NO* r){
    //raiz - esquerda - direita
	if(r != NULL){
	printf("[%d]", r->valor);
	preOrder(r->esq);
	preOrder(r->dir);
	}
}

void inOrder(NO* r){
    //esquerda - raiz - direita
	if(r != NULL){
	inOrder(r->esq);
    printf("[%d]", r->valor);
	inOrder(r->dir);
    }
}

void posOrder(NO* r){
    //esquerda - direita - raiz
	if(r != NULL){
	posOrder(r->esq);
	posOrder(r->dir);
    printf("[%d]", r->valor);
    }
}

NO* remover(NO* r, int valor){
    if(r==NULL)
        return NULL;
    if(valor == r->valor){
        if(r->dir == NULL){
            return r->esq;
        }
        if(r->esq==NULL){
            return r->dir;
        }
        r->valor = maior(r->esq); //funçao maior elemento
        r->esq = remover(r->esq, r->valor);
        return r;
    }

    if(valor > r->valor){
        r->dir = remover(r->dir,valor);

    }else{
        r->esq = remover(r->esq,valor);
    }
}

int maior(NO *r){
    if(r != NULL){
        if(r->dir == NULL){
            return r->valor;
        }else{
            maior(r->dir);
        }
    }
}

int menor(NO *r){
    if(r != NULL){
        if(r->esq == NULL){
            return r->valor;
        }else{
            menor(r->esq);
        }
    }
}
