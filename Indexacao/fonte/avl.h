#ifndef AVL_H
#define AVL_H

typedef struct livro {
	char titulo[81];
	char autor[51];
	char ano[5];
	int codigo;
} tipo_dado;


//typedef int tipo_dado;

typedef struct no_avl {
	tipo_dado *dado;
    int fb;
	struct no_avl *esq, *dir;
} no_avl;

typedef no_avl * arvore;

void inicializar(arvore *raiz);
arvore adicionar(tipo_dado *valor, arvore raiz, int *cresceu);

arvore rotacionar(arvore raiz);
arvore rotacao_simples_dir(arvore raiz);
arvore rotacao_simples_esq(arvore raiz);
arvore rotacao_simples_esq_caso_remocao(arvore raiz);
arvore rotacao_simples_dir_caso_remocao(arvore raiz);
arvore rotacao_dupla_dir(arvore raiz);
arvore rotacao_dupla_esq(arvore raiz);

void pre_order(arvore raiz);
void pos_order(arvore raiz);
void in_order(arvore raiz);

void imprimir_elemento(arvore raiz);
tipo_dado * ler_dados();
void tirar_enter(char *string);

void salvar_arquivo(char *nome, arvore a);
void salvar_auxiliar(arvore raiz, FILE *arq);
arvore carregar_arquivo(char *nome, arvore a, int *cresceu);

void buscarCodigo(char *nome, arvore raiz, int codigo);

#endif
