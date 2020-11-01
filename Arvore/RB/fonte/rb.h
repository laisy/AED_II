#ifndef RB_H
#define RB_H

enum cor {VERMELHO, PRETO, DUPLO_PRETO};

typedef  int  tipo_dado;

typedef struct no_bst{
    tipo_dado dado;
    enum cor cor;
    struct no_bst *esq, *dir, *pai;
} no_bst;

typedef no_bst *arvore;

void inicializar(arvore *raiz);
void inserir(tipo_dado dado, arvore *raiz);
void ajustar(arvore *raiz, arvore dado);

enum cor cor(arvore n);
int eh_raiz(arvore n);
int eh_filho_esquerdo(arvore dado);
arvore irmao(arvore dado);
arvore tio (arvore n);
void recolorir(arvore n);

//////////// impressões ////////////////////////////
void pre_order(arvore raiz);
void pos_order(arvore raiz);
void in_order(arvore raiz);

void imprimir_elemento(arvore raiz);
void imprimir(arvore raiz);
////////////////////////////////////////////////

int maior_elemento(arvore raiz);
int menor_elemento(arvore raiz);

void remover(int elemento, arvore *raiz);
void reajustar(arvore *raiz, arvore n);
void retira_duplo_preto(arvore *raiz, arvore dado);

////////////////////casos/////////////////////////////////
void rotacao_simples_direita(arvore *raiz, arvore pivo);
void rotacao_simples_esquerda(arvore *raiz, arvore pivo);
void rotacao_dupla_direita(arvore *raiz, arvore pivo);
void rotacao_dupla_esquerda(arvore *raiz, arvore pivo);

////////////////////////////////////////////////////////

int altura(arvore raiz);
int maior(int a, int b);

#endif
