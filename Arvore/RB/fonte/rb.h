#ifndef RB_H
#define RB_H

enum cor {VERMELHO, PRETO, DUPLO_PRETO};

typedef  int  tipo_dado;

typedef struct no{
    enum cor cor;
    tipo_dado dado;
    struct no *esq, *dir, *pai;
}no;

typedef no * arvore;

void inicializar(arvore *raiz);
void inserir (tipo_dado dado, arvore *raiz);
void ajustar(arvore *raiz, arvore dado);

enum cor cor(arvore n);
int eh_esquerdo(arvore n);
int eh_direito(arvore n);
int eh_raiz(arvore n);
int eh_nulo(arvore dado);
arvore tio (arvore n);
arvore Avo(arvore n);
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

////////////////////casos/////////////////////////////////
void caso2(arvore *raiz, arvore n);
void caso2_simetrico(arvore *raiz, arvore n);

void caso3(arvore *raiz, arvore n);
void caso3_simetrico(arvore *raiz, arvore n);

void caso4(arvore *raiz, arvore n);
void caso4_simetrico(arvore *raiz, arvore n);

void caso5(arvore *raiz, arvore n);
void caso5_simetrico(arvore *raiz, arvore n);

void caso6(arvore *raiz, arvore n);
void caso6_simetrico(arvore *raiz, arvore n);

////////////////////////////////////////////////////////

int altura(arvore raiz);
int maior(int a, int b);

#endif
