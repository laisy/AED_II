#include <stdio.h>
#include <stdlib.h>
#include "AVL.h"

void inicializar(arvore *raiz) {
	*raiz = NULL;
}

arvore adicionar (int valor, arvore raiz, int *cresceu) {

	if(raiz == NULL) {
		arvore novo = (arvore) malloc(sizeof(struct no_avl));
		novo->dado = valor;
		novo->esq = NULL;
		novo->dir = NULL;
		novo->fb = 0;
        * cresceu = 1;
		return novo;
	}

	if(valor > raiz->dado) {
        //Elemento maior => adicionar na direita
		raiz->dir = adicionar(valor, raiz->dir, cresceu);

        if(*cresceu) {
            //Chegando neste ponto, sabe se que:
            //a) O elemento foi inserido na sub-árvore direita; e
            //b) A sub-árvore a direita cresceu
			switch(raiz->fb) {
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

	} else {
        //Elemento menor < adicionar na esquerda
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
                    break;
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
    r->esq = s->dir;
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
    raiz->dir = r;

    //Rotação esquerda
    raiz->dir = s->esq;
    s->esq = raiz;

    //Atualizando os fatores de balanço
    if(s->fb==0){
        r->fb = 0;
        s->fb = 0;
        raiz->fb=0;

    }
    else if(s->fb==-1){

        r->fb = 1;
        s->fb = 0;
        raiz->fb= 0;
    }
     else{
        r->fb = 0;
        s->fb = 0;
        raiz->fb=-1;
    }
        return s;
}

//------------------REMOVER--------------------------------
arvore remover(arvore raiz, int valor) {

    int *diminuiu = 0;
    if(raiz == NULL){
		return NULL;

	}
    else if(valor < raiz->dado){

    	raiz->esq = remover(raiz->esq, valor);
        if(*diminuiu) {
            switch(raiz->fb) {
                case -1:
                    raiz->fb = 0;
                    *diminuiu = 1;
                    break;
                case 0:
                    raiz->fb = 1;
                    *diminuiu = 0;
                    break;
                case 1:
                    raiz->fb = 2;
                    if(raiz->dir->fb==0){
                        *diminuiu = 0;
                    }
                    else{
                        *diminuiu = 1;
                    }
                    return rotacionar(raiz);
                    break;
            }

        }

	}
    else if(valor > raiz->dado){

    	raiz->dir = remover(raiz->dir, valor);
        if(*diminuiu) {
            switch(raiz->fb) {
                case -1:
                    raiz->fb = -2;
                    if(raiz->esq->fb == 0){
                        *diminuiu = 0;
                    }
                    else{
                        *diminuiu = 1;
                    }
                    return rotacionar(raiz);

                case 0:
                    raiz->fb = -1;
                    *diminuiu = 0;
                    break;
                case 1:
                    raiz->fb = 0;
                    *diminuiu = 1;
                    break;
            }
        }
	}
    else{
		arvore aux = raiz;
        *diminuiu = 1;

		//Sem filhos
		if(raiz->esq == NULL && raiz->dir == NULL){
			free(aux);
			raiz = NULL;

		//Filhos a direita
		}
        else if(raiz->esq == NULL && raiz->dir != NULL){
			raiz = raiz->dir;
			free(aux);

		//Filhos a esquerda
		}
        else if(raiz->esq != NULL && raiz->dir == NULL){
		    raiz = raiz->esq;
		    free(aux);

        //Dois filhos
		}
        else{
			arvore novo = raiz->esq;
			while(novo->dir != NULL){
				novo = novo->dir;
			}
			raiz->dado = novo->dado;
			raiz->esq = remover(raiz->esq, novo->dado);
            if(*diminuiu) {
                switch(raiz->fb) {
                    case -1:
                        raiz->fb = 0;
                        *diminuiu = 1;
                        break;
                    case 0:
                        raiz->fb = 1;
                        *diminuiu = 0;
                        break;
                    case 1:
                        raiz->fb = 2;
                        if(raiz->dir->fb == 0){
                            *diminuiu = 0;
                        }
                        else{
                            *diminuiu = 1;
                        }
                        return rotacionar(raiz);
                        break;
                    }
            }

		}
	}
	return raiz;
}


void imprimir(arvore raiz) {
	printf("(");
	if(raiz != NULL) {
		imprimir_elemento(raiz);
		imprimir(raiz->esq);
		imprimir(raiz->dir);
	}
	printf(")");
}

/*---
Auxiliar de imprimir
---*/
void imprimir_elemento(arvore raiz) {
	printf("%d [%d]", raiz->dado, raiz->fb);
}


int altura(arvore raiz) {
	if(raiz == NULL) {
		return 0;
	}
	return 1 + maior(altura(raiz->dir), altura(raiz->esq));
}

int maior(int a, int b) {
	if(a > b)
		return a;
	else
		return b;
}

int maior_elemento(arvore raiz) {
	if(raiz == NULL)
			return -1;
	if(raiz->dir == NULL)
			return raiz->dado;
	else
			return maior_elemento(raiz->dir);
}

int menor_elemento(arvore raiz) {
	if(raiz == NULL)
			return -1;
	if(raiz->esq == NULL)
			return raiz->dado;
	else
			return maior_elemento(raiz->esq);
}

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

