#ifndef AVL_H
#define AVL_H

typedef int tipo_dado;

typedef struct no_avl {
	tipo_dado dado;
	int fb;
	struct no_avl *esq, *dir;
} no_avl;

typedef no_avl *arvore;

void inicializar(arvore *raiz);
arvore adicionar (int valor, arvore raiz, int *cresceu);

arvore rotacionar(arvore raiz);
arvore rotacao_simples_dir(arvore raiz);
arvore rotacao_simples_esq(arvore raiz);
arvore rotacao_simples_esq_caso_remocao(arvore raiz);
arvore rotacao_simples_dir_caso_remocao(arvore raiz);
arvore rotacao_dupla_dir(arvore raiz);
arvore rotacao_dupla_esq(arvore raiz);

arvore remover(arvore raiz, int valor);
void imprimir(arvore raiz);
void imprimir_elemento(arvore raiz);
int altura(arvore raiz);
int maior(int a, int b);
int maior_elemento(arvore raiz) ;
int menor_elemento(arvore raiz);
void pre_order(arvore raiz);
void pos_order(arvore raiz);
void in_order(arvore raiz);

#endif
