#include "rb.h"
#include <stdlib.h>
#include <stdio.h>

arvore no_null;

void inicializar(arvore *raiz) {
	*raiz = NULL;
	no_null = (arvore) malloc(sizeof(struct no));
	no_null->cor = DUPLO_PRETO;
	no_null->dado = 0;
}

void inserir(int dado, arvore *raiz){
    arvore temp, pai, novo;
    temp = *raiz;
    pai = NULL;

    while(temp != NULL){

        pai = temp;

        if(dado > temp->dado){
            temp = temp->dir;
        }
        else{
            temp = temp->esq;
        }
    }
    novo = (arvore)malloc(sizeof(struct no));
    novo->dado = dado;
    novo->esq = NULL;
    novo->dir = NULL;
    novo->pai = pai;
    novo->cor = VERMELHO;

    if(eh_raiz(novo))
        *raiz = novo;
	else {
		if(dado > pai->dado){
			pai->dir = novo;
        }
		else
			pai->esq = novo;
	}

    ajustar(raiz, novo);
}

int eh_raiz(arvore n){
    return(n->pai == NULL);
}

int eh_esquerdo(arvore n){
    return(n->pai != NULL && n == n->pai->esq);
}
int eh_direito(arvore n){
    return(n->pai !=NULL && n == n->pai->dir);
}

int eh_nulo(arvore dado){
	return (dado->pai != NULL && dado->dado == 0  && dado->esq == NULL && dado->dir == NULL && dado->cor == DUPLO_PRETO);
}

arvore tio(arvore n){
    if(eh_esquerdo(n->pai)){
        return n->pai->pai->dir;
    }
    else{
        return n->pai->pai->esq;
    }
}

arvore Avo(arvore n){
    if(n->pai!=NULL){
        return n->pai->pai;
    }else{
        return NULL;
    }
}

////////////// ROTAÇÕES //////////////////////
void rotacao_simples_direita(arvore *raiz, arvore n){
    arvore u, t2;
    u = n->esq;
    t2 = u->dir;

    //rotação
    n->esq = t2;
    u->dir = n;

    //colorir
    u->cor = PRETO;
    n->cor = VERMELHO;

    //atualizar pais
    if(t2!=NULL){
        t2->pai = n;
    }
    u->pai = n->pai;

    if(eh_raiz(n)){
        *raiz = u;
    }else{
        if(eh_direito(n)){
            n->pai->dir = u;
        }else{
            n->pai->esq = u;
        }
    }
    n->pai = u;

}

void rotacao_simples_esquerda(arvore *raiz, arvore n){

    arvore u, t2;
    u = n->dir;
    t2 = u->esq;

    n->dir = t2;

    if(t2!=NULL){
        t2->pai = n;
    }

    u->esq = n;
    u->pai = n->pai;

   if(eh_raiz(n)){
       *raiz = u;
    }else{
        if(eh_esquerdo(n)){
            n->pai->esq = u;
        }else{
            n->pai->dir = u;
        }
    }
     n->pai = u;
    //corrigindo cores
    u->cor=PRETO;
    n->cor = VERMELHO;

}
void rotacao_dupla_esquerda(arvore *raiz, arvore n){

    arvore u, v, t2, t3;
    u = n->dir;
    v = u->esq;
    t2 = v->esq;
    t3 = v->dir;

    //primeira rotaçao
    u->esq = t3;
    v->dir= u;
    n->dir= v;

    //segunda rotação
    n->dir = t2;
    v->esq = n;

    //atualizar cores
    v->cor = PRETO;
    n->cor = VERMELHO;

    //atualizar pais
    if(t2 != NULL){
        t2->pai = n;
    }
    if(t3 != NULL){
        t3->pai = u;
    }

    u->pai = v;
    v->pai = n->pai;

    if(eh_raiz(n)){
        *raiz = v;
    }else{
        if(eh_direito(n)){
            n->pai->dir = v;
        }else{
            n->pai->esq = v;
        }
    }
    n->pai = v;

}
void rotacao_dupla_direita(arvore *raiz, arvore n){

    arvore u, v, t2, t3;
    u = n->esq;
    v = u->dir;
    t2 = v->esq;
    t3 = v->dir;

    //primeira rotaçao
    u->dir = t2;
    v->esq = u;
    n->esq= v;

    //segunda rotação
    n->esq = t3;
    v->dir = n;

    //atualizar cores
    v->cor = PRETO;
    n->cor = VERMELHO;

    //atualizar pais
    if(t2!=NULL){
        t2->pai = u;
    }
    if(t3!=NULL){
        t3->pai = n;
    }
    u->pai = v;
    v->pai = n->pai;
    if(eh_raiz(n)){
        *raiz = v;
    }else{
        if(eh_direito(n)){
            n->pai->dir = v;
        }else{
            n->pai->esq = v;
        }
    }
    n->pai = v;
}
////////////////////////////////////////////////////

void recolorir(arvore n){
    arvore avo = Avo(n);
    if(eh_raiz(avo)){
         avo->esq->cor= PRETO;
         avo->dir->cor=PRETO;
    }else{
        avo->cor=VERMELHO;
        avo->esq->cor= PRETO;
        avo->dir->cor=PRETO;
    }
}

void ajustar(arvore *raiz, arvore n){
    if(n->pai == NULL){
        n->cor = PRETO;
        *raiz = n;
    }
    else if(cor(n->pai) == VERMELHO && cor(n) == VERMELHO){
        //caso 1: tio é vermelho
        if(tio != NULL && cor(tio(n)) == VERMELHO){
            recolorir(n);
            ajustar(raiz, n->pai->pai);
        }
        //caso 2: tio é preto e n é filho esquerdo e pai é esquerdo
        if(eh_esquerdo(n) && eh_esquerdo(n->pai)){
            rotacao_simples_direita(raiz, n->pai->pai);
        }
        //caso 3: tio é preto, n é filho esquerdo e pai de n é direito
        if(eh_direito(n) && eh_direito(n->pai)){
            rotacao_simples_esquerda(raiz, n->pai->pai);
        }
        //caso 2: tio é preto e n é filho esquerdo e pai é direito
        if(eh_esquerdo(n) && eh_direito(n->pai)){
            rotacao_dupla_esquerda(raiz, n->pai->pai);
        }
        //caso 3: tio é preto, n é filho esquerdo e pai de n é esquerdo
        if(eh_direito(n) && eh_esquerdo(n->pai)){
            rotacao_dupla_direita(raiz, n->pai->pai);
            }
        }
}

enum cor cor(arvore n){
    enum cor cor;
	if(n==NULL || n->cor == PRETO)
		return PRETO;
	else
		return VERMELHO;
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
	if(raiz == NULL){
		return -1;
	}
	if(raiz->dir == NULL){
		return raiz->dado;
	}
	else{
		return maior_elemento(raiz->dir);
	}
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

void imprimir_elemento(arvore raiz) {
	switch(raiz->cor){
		case PRETO:
			printf("\x1b[30m[%d]\x1b[0m", raiz->dado);
			break;
		case VERMELHO:
			printf("\x1b[31m[%d]\x1b[0m", raiz->dado);
			break;
		case DUPLO_PRETO:
			printf("\x1b[32m[%d]\x1b[0m", raiz->dado);
			break;
	}
}

void remover(int dado, arvore *raiz) {
	arvore temp, pai;
    temp = *raiz;
    pai = NULL;

	while(temp != NULL && temp->dado != dado) {
        pai = temp;
        if(dado > temp->dado) {
           	temp = temp->dir;
        }
		else {
        	temp = temp->esq;
        }
    }
    if(temp == NULL){
        return ;
	}

    if(temp->esq != NULL && temp->dir != NULL) {
        temp->dado = maior_elemento(temp->esq);
        remover(temp->dado, &temp->esq);
        return;
    }
    if(temp->esq != NULL && temp->dir == NULL) {
       	temp->dado = temp->esq->dado;
        temp->cor = PRETO;
		remover(temp->dado, &temp->esq);
		return;
    }
    if(temp->dir != NULL && temp->esq == NULL) {
       	temp->dado = temp->dir->dado;
        temp->cor = PRETO;
		remover(temp->dado, &temp->dir);
		return;
    }
	if(temp->cor == VERMELHO) {
        if(eh_esquerdo(temp)) {
            temp->pai->esq = NULL;
        }
		else {
            temp->pai->dir = NULL;
        }
        return ;
    }

	temp->dado = 0;
	temp->cor = DUPLO_PRETO;

	if(eh_esquerdo(temp)) {
        temp->pai->esq = NULL;
    }
	else {
        temp->pai->dir = NULL;
    }

	reajustar(raiz, temp);
}


void reajustar(arvore *raiz, arvore n) {
    //Caso 1 - duplo preto é raiz
    if(eh_raiz(n)) {
		*raiz = NULL;
	}
	else{
        n->cor = PRETO;
    }
    return;

    //Caso 2
    if(eh_esquerdo(n)){
		if(eh_nulo(n)){
			if(n->pai->cor == PRETO && n->pai->dir->cor == VERMELHO && n->pai->dir->dir->cor == PRETO && n->pai->dir->esq->cor == PRETO){
				 caso2(raiz, n);
			    }
		    }
	    return;
    }
	//Caso 2 simetrico
	if(eh_direito(n)){
		if(eh_nulo(n)){
			if(n->pai->cor == PRETO && n->pai->esq->cor == VERMELHO && n->pai->esq->esq->cor == PRETO && n->pai->esq->dir->cor == PRETO){
				caso2_simetrico(raiz, n);
			}
		}
		return;
	}

    //Caso 3
    if(eh_esquerdo(n)){
		if(eh_nulo(n)){
			if(n->pai->cor == PRETO && n->pai->dir->cor == PRETO && n->pai->dir->dir->cor == PRETO && n->pai->dir->esq->cor == PRETO){
				caso3(raiz,n);
			}
		}
		return;
    	}

	//Caso 3 simetrico
	if(eh_direito(n)){
		if(eh_nulo(n)){
			if(n->pai->cor == PRETO && n->pai->esq->cor == PRETO && n->pai->esq->esq->cor == PRETO && n->pai->esq->dir->cor == PRETO){
				caso3_simetrico(raiz, n);
			}
		}
		return;
    	}


    //Caso 4
    if(eh_esquerdo(n)){
		if(eh_nulo(n)){
			if(n->pai->cor == VERMELHO && n->pai->dir->cor == PRETO && n->pai->dir->dir->cor == PRETO && n->pai->dir->esq->cor == PRETO){
				caso4(raiz, n);
			}
		}
		return;
    }

	//Caso 4 simetrico
	if(eh_direito(n)){
		if(eh_nulo(n)){
			if(n->pai->cor == VERMELHO && n->pai->esq->cor == PRETO && n->pai->esq->esq->cor == PRETO && n->pai->esq->dir->cor == PRETO){
				caso4_simetrico(raiz, n);
			}
		}
		return;
    }

    //Caso 5
    if(eh_esquerdo(n)){
   		if(eh_nulo(n)){
			if(n->pai->dir->cor == PRETO && n->pai->dir->esq->cor == VERMELHO && n->pai->dir->dir->cor == PRETO){
				caso5(raiz, n);
			}
		}
		return;
    }

	//Caso 5 simetrico
    if(eh_direito(n)){
   		if(eh_nulo(n)){
			if(n->pai->esq->cor == PRETO && n->pai->esq->dir->cor == VERMELHO && n->pai->esq->esq->cor == PRETO){
				caso5_simetrico(raiz, n);
			}
		}
		return;
    }

    //Caso 6
    if(eh_esquerdo(n)){
		if(eh_nulo(n)){
			if(n->pai->dir->cor == PRETO && n->pai->dir->dir->cor == VERMELHO){
				caso6(raiz, n);
			}
		}
		return;
   	}

	//Caso 6 simetrico
    if(eh_direito(n)){
		if(eh_nulo(n)){
			if(n->pai->esq->cor == PRETO && n->pai->esq->esq->cor == VERMELHO){
				caso6_simetrico(raiz, n);
			}
		}
		return;
   	}
}

void caso2(arvore *raiz, arvore n){
	arvore p, aux;
	p = n->pai;
	aux = p->dir;

	int posicao_pivo_esq = eh_esquerdo(p);

	p->dir = aux->esq;
	aux->esq = p;

	aux->pai = p->pai;

	if(p->dir != NULL){
		p->dir->pai = p;
	}
	p->pai = aux;

	p->cor = VERMELHO;
	aux->cor = PRETO;

	if(eh_raiz(aux)){
		*raiz = aux;
	}
	else{
		if(posicao_pivo_esq){
			aux->pai->esq = aux;
		}
		else{
			aux->pai->dir = aux;
		}
	}
}

void caso2_simetrico(arvore *raiz, arvore n){
	arvore p, aux;
	p = n->pai;
	aux = p->esq;

	int posicao_pivo_esq = eh_direito(p);

	p->esq = aux->dir;
	aux->dir = p;

	aux->pai = p->pai;

	if(p->esq != NULL){
		p->esq->pai = p;
	}
		p->pai = aux;

	p->cor = VERMELHO;
	aux->cor = PRETO;

	if(eh_raiz(aux)){
		*raiz = aux;
	}
	else{
		if(posicao_pivo_esq){
			aux->pai->esq = aux;
		}
		else{
			aux->pai->dir = aux;
		}
	}
}

void caso3(arvore *raiz, arvore n){
	if(n->dir == NULL && n->esq == NULL){
		n->cor = VERMELHO;
	}
	else{
		n->cor = PRETO;
	}
	n->pai->cor = DUPLO_PRETO;
	n->pai->dir->cor = VERMELHO;
}

void caso3_simetrico(arvore *raiz, arvore n){
	if(n->dir == NULL && n->esq == NULL){
		n->cor = VERMELHO;
	}
	else{
		n->cor = PRETO;
	}
	n->pai->cor = DUPLO_PRETO;
	n->pai->esq->cor = VERMELHO;
}

void caso4(arvore *raiz, arvore n){
	if(n->dir == NULL && n->esq == NULL){
		n->cor = VERMELHO;
	}
	else{
		n->cor = PRETO;
	}
	n->pai->cor = PRETO;
	n->pai->dir->cor = VERMELHO;
}

void caso4_simetrico(arvore *raiz, arvore n){
	if(n->dir == NULL && n->esq == NULL){
		n->cor = VERMELHO;
	}
	else{
		n->cor = PRETO;
	}
	n->pai->cor = PRETO;
	n->pai->esq->cor = VERMELHO;
}

void caso5(arvore *raiz, arvore n){
	arvore p, aux;
	p = n->pai;
	aux = p->dir;

	p->dir = aux->esq;
	aux->esq =aux->esq->dir;
	p->dir->dir = aux;

	p->dir->pai = p;
	p->dir->dir->pai = p->dir;

	p->dir->cor = PRETO;
	p->dir->dir->cor = VERMELHO;
}

void caso5_simetrico(arvore *raiz, arvore n){
	arvore p, aux;
	p = n->pai;
	aux = p->esq;

	p->esq = aux->dir;
	aux->dir = aux->dir->esq;
	p->esq->esq = aux;

	p->esq->pai = p;
	p->esq->esq->pai = p->esq;

	p->esq->cor = PRETO;
	p->esq->esq->cor = VERMELHO;
}

void caso6(arvore *raiz, arvore n){
	arvore p, aux;
	p = n->pai;
	aux = p->dir;

	int posicao_pivo_esq = eh_esquerdo(p);

	p->dir = aux->esq;
	aux->esq = p;
	aux->pai = p->pai;

	if(p->dir!=NULL){
		p->dir->pai = p;
	}
	p->pai = aux;

	aux->cor = p->cor;
	p->cor = PRETO;
	aux->dir->cor = PRETO;
	if(n->dir == NULL && n->esq == NULL){
		p->esq->cor = VERMELHO;
	}
	else{
		p->esq->cor = PRETO;
	}


	if(eh_raiz(aux)){
		*raiz = aux;
	}
	else{
		if(posicao_pivo_esq){
			aux->pai->esq = aux;
		}
		else{
			aux->pai->dir = aux;
		}
	}
}

void caso6_simetrico(arvore *raiz, arvore n){
	arvore p, aux;
	p = n->pai;
	aux = p->esq;

	int posicao_pivo_esq = eh_esquerdo(p);

	p->esq = aux->dir;
	aux->dir = p;

	aux->pai = p->pai;

	if(p->esq!=NULL){
		p->esq->pai = p;
	}

	p->pai = aux;

	aux->cor = p->cor;
	p->cor = PRETO;
	aux->esq->cor = PRETO;

	if(n->dir == NULL && n->esq == NULL){
		p->dir->cor = VERMELHO;
	}
	else{
		p->dir->cor = PRETO;
	}
	if(eh_raiz(aux)){
		*raiz = aux;
	}
	else{
		if(posicao_pivo_esq){
			aux->pai->esq = aux;
		}
		else{
			aux->pai->dir = aux;
		}
	}

}
