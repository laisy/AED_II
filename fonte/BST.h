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

//FAZER
//case 5
NO* remover(NO* r, int valor);
//case 6
NO* maior(NO *raiz);
//case 7
NO* menor(NO *raiz);
//case 8
NO* altura(NO *raiz);
//case 9
NO* quantidade_elementos(NO *raiz);
//case 10
NO* existe(NO *raiz, int valor);    //Retornar 1(existe) ou 0(nao exite);

/*implementação iterativa, procurar o cara
 * temp = temp -> esq
 * temp = temp -> dir
 * if temp -> dir!= null
 * return menor(t->d)
 */
//case 11
NO* predecessor(NO *raiz, int valor);    //(inOrder)
//case 12
NO* sucessor(NO *raiz, int valor);  //(sempre a direta)

#endif
