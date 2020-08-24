#ifndef BST_h   //corrigir erro de duplicata
#define BST_h

//só declarações
typedef struct NO{
	int valor;     //chave
	struct NO* esq;
	struct NO* dir;
}NO;

//case 1
NO* inserir(NO* r, int valor);
//case 2
void preOrder(NO* r);
//case 3
void inOrder(NO* r);
//case 4
void posOrder(NO* r);
//case 5
NO* remover(NO* r, int valor);
//case 6
int maior(NO *r);
//case 7
int menor(NO *r);
//case 8
int altura(NO *r);
//case 9
int quantidade_elementos(NO *r);
//case 10
int existe(NO *r, int valor);    //Retornar 1(existe) ou 0(nao exite);
//case 11
int predecessor(NO *r, int valor);    //(principio do inOrder)
NO* buscar(NO *r, int valor);
//case 12
int sucessor(NO *r, int valor);

#endif
