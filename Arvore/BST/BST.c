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
    if(r==NULL){        //arvore vazia
		return NULL;

	}else if(valor < r->valor){    //valor tá na esquerda
		r->esq = remover(r->esq, valor);

	}else if(valor > r->valor){        //valor tá na direita
		r->dir = remover(r->dir, valor);

	}else{
		NO* temp = r;     //NO temporario
		if(r->esq == NULL && r->dir == NULL){    //Caso 1: sem filhos
			free(temp);
			r = NULL;
		}else if(r->esq == NULL && r->dir != NULL){       //Caso 2: 1 filho
			r = r->dir;
			free(temp);
		}else if(r->esq != NULL && r->dir == NULL){
			r = r->esq;
			free(temp);
		}else{        //Caso 3: 2 filhos
			NO* novo = r->esq;
			while(novo->dir != NULL){    //troca pelo menor da dir
				novo = novo->dir;
			}
			r->valor = novo->valor;      //troca
			r->esq = remover(r->esq, novo->valor);       //remove
		}
	}
	return r;
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

int altura(NO *r){
    if(r==NULL){
        return 0;
    }
    if (r->esq == NULL && r->dir == NULL){
        return 1;
    }else{
        int esq = altura(r->esq);
        int dir = altura(r->dir);
        if(esq<dir){
            return dir+1;
        }else{
            return esq+1;
        }
    }
}

NO* buscar(NO *r, int valor){
    if(r != NULL){
        if(r->valor == valor){
            return r;
        }else{
            if(valor>r->valor){
                return buscar(r->dir,valor);
            }else{
               return buscar(r->esq,valor);
            }
        }
    }

    return NULL;
}

int quantidade_elementos(NO *r){
    int quantidade, contadorEsq, contadorDir;
    if(r == NULL){
        return 0;
    }
    else{
        contadorEsq = quantidade_elementos(r->esq);
        contadorDir = quantidade_elementos(r->dir);
        quantidade = contadorEsq + contadorDir + 1;
    }
    return quantidade;
}

int existe(NO *r, int valor){
    if(buscar(r, valor) != NULL){
        return 1;
    }
    return 0;
}

//Elemento que viria antes se fosse uma lista ordenada
int predecessor(NO *r, int valor){
	if(r == NULL){
        return -1;
	}
	else if(valor == menor(r)){
        return 0;
    }else{
        NO *temp = buscar(r, valor);
        int menorValor = menor(r);
        if(temp != NULL && valor != menorValor  && r != NULL){
            if(temp->esq != NULL){
                return maior(temp->esq);
            }else{
                NO *cursor = r;
                NO *pred = NULL;
                while(temp != cursor && temp != NULL){
                    if(cursor->valor < temp->valor){
                        pred = cursor;
                        cursor = cursor->dir;
                }else{
                    cursor = cursor->esq;
                }
            }
            return pred->valor;
        }
    }else{
        return -1;
        }
    }
}

int sucessor(NO *r, int valor){
    NO *elemento = buscar(r, valor);
    int maiorElemento = maior(r);
    if(elemento != NULL && valor != maiorElemento && r != NULL){
        if(elemento->dir != NULL){
            return menor(elemento->dir);
        }else{
            NO *cursor = r;
            NO *sucessor = NULL;
            while(elemento != cursor && elemento != NULL){
                if(cursor->valor>elemento->valor){
                    sucessor = cursor;
                    cursor = cursor->esq;
                }else{
                    cursor = cursor->dir;
                }
            }
            return sucessor->valor;
        }
    }else{
        return -1;
    }
}
