#include <stdio.h>
#include <stdlib.h>

typedef struct _nodo{
	int chave, nivel, cor;
	struct _nodo *left;
	struct _nodo *right;
	struct _nodo *dad;
} TpNodo;

typedef struct _arvore{
	TpNodo *raiz;
	TpNodo *sentinela;
} TpArvore;

TpArvore* inicializa(){
	TpArvore *arvore = (TpArvore*)malloc(sizeof(TpArvore));
	TpNodo *sentinela = (TpNodo*)malloc(sizeof(TpNodo));
	arvore->raiz = NULL;
	arvore->sentinela = sentinela;
	arvore->sentinela->nivel = 1;
	arvore->sentinela->chave = -1;
	arvore->sentinela->cor = 1;
	arvore->sentinela->dad = NULL;
	arvore->sentinela->left = NULL;
	arvore->sentinela->right = NULL;
	return arvore;
}

bool verificaKey(TpNodo *nodo, int key){
	TpNodo *t = nodo;
	while(t != NULL){
		if(key == t->chave) return true;
		else if(key > t->chave) t = t->right;
		else if(key < t->chave) t = t->left;
	}
	return false;
}

TpNodo* rightRotation(TpNodo *nodo){
	TpNodo *aux = nodo->left;
	aux->dad = nodo->dad;
	nodo->dad = aux;
	nodo->left = aux->right;
	if(aux->right != NULL) aux->right->dad = nodo;
	aux->right = nodo;
	if(aux->dad != NULL){
		aux = aux->dad;
		aux->left = nodo->dad;
	}	
	return aux;
}

TpNodo* leftRotation(TpNodo *nodo){
	TpNodo *aux = nodo->right;
	aux->dad = nodo->dad;
	nodo->dad = aux;
	nodo->right = aux->left;
	if(aux->left != NULL) aux->left->dad = nodo;
    aux->left = nodo;
    if(aux->dad != NULL){
    	aux = aux->dad;
		aux->right = nodo->dad;
    }
    return aux;
}

TpArvore* verificaRubroNegra(TpArvore *arvore, TpNodo *nodo, int key){
	if(key == arvore->sentinela->chave) return arvore;
	else if(arvore->sentinela->left != NULL && key == arvore->sentinela->left->chave) return arvore;
	else if(arvore->sentinela->right != NULL && key == arvore->sentinela->right->chave) return arvore;

	TpNodo *t = nodo;
	TpNodo *tDad = t->dad;
	TpNodo *tAvo = tDad->dad;
	TpNodo *aux;

	if(tDad->chave < tAvo->chave){ //pai eh filho a esquerda
		if(t->chave < tDad->chave){ //nodo eh filho a esquerda
			if(tDad->cor == 0){//se o pai do nodo eh vermelho
				if(tAvo->right == NULL || tAvo->right->cor == 1){//se o tio eh nulo ou preto
					if(tAvo->chave == arvore->sentinela->chave){//se o avo eh a raiz
						arvore->sentinela = tDad;
						arvore->raiz = arvore->sentinela;
						if(tDad->cor == 0) tDad->cor = 1;
						else tDad->cor = 0;
						if(tAvo->cor == 0) tAvo->cor = 1;
						else tAvo->cor = 0;
						aux = rightRotation(tAvo);
						arvore = verificaRubroNegra(arvore, aux, aux->chave);
						if(arvore->raiz->cor == 0) arvore->raiz->cor = 1;
						return arvore;
					}else{
						if(tDad->cor == 0) tDad->cor = 1;
						else tDad->cor = 0;
						if(tAvo->cor == 0) tAvo->cor = 1;
						else tAvo->cor = 0;
						aux = rightRotation(tAvo);
						arvore = verificaRubroNegra(arvore, aux, aux->chave);
						if(arvore->raiz->cor == 0) arvore->raiz->cor = 1;
						return arvore;
					}
				}else if(tAvo->right->cor == 0){//se o tio eh vermelho
					if(tDad->cor == 0) tDad->cor = 1;
					else tDad->cor = 0;
					if(tAvo->cor == 0) tAvo->cor = 1;
					else tAvo->cor = 0;
					tAvo->right->cor = 1;
					arvore = verificaRubroNegra(arvore, tAvo, tAvo->chave);
					if(arvore->raiz->cor == 0) arvore->raiz->cor = 1;
					return arvore;
				}
			}else return arvore;
		}else if(t->chave > tDad->chave){//nodo eh filho a direita
			if(tDad->cor == 0){
				t->dad = tAvo;
				tDad->dad = t;
				tAvo->left = t;
				tDad->right = NULL;
				t->left = tDad;
				arvore = verificaRubroNegra(arvore, tDad, tDad->chave);
				return arvore;
			}else return arvore;
		}
	}else if(tDad->chave > tAvo->chave){//pai eh filho a direita
		if(t->chave > tDad->chave){//nodo eh filho e direita
			if(tDad->cor == 0){//se o pai eh vermelho
				if(tAvo->left == NULL || tAvo->left->cor == 1){//se o tio eh nulo ou preto
					if(tAvo->chave == arvore->sentinela->chave){//se o avo eh a raiz
						arvore->sentinela = tDad;
						arvore->raiz = arvore->sentinela;
						if(tDad->cor == 0) tDad->cor = 1;
						else tDad->cor = 0;
						if(tAvo->cor == 0) tAvo->cor = 1;
						else tAvo->cor = 0;
						aux = leftRotation(tAvo);
						arvore = verificaRubroNegra(arvore, aux, aux->chave);
						if(arvore->raiz->cor == 0) arvore->raiz->cor = 1;
						return arvore;
					}else{
						if(tDad->cor == 0) tDad->cor = 1;
						else tDad->cor = 0;
						if(tAvo->cor == 0) tAvo->cor = 1;
						else tAvo->cor = 0;
						aux = leftRotation(tAvo);
						arvore = verificaRubroNegra(arvore, aux, aux->chave);
						if(arvore->raiz->cor == 0) arvore->raiz->cor = 1;
						return arvore;
					}
				}else if(tAvo->left->cor == 0){//se o tio eh vermelho
					if(tDad->cor == 0) tDad->cor = 1;
					else tDad->cor = 0;
					if(tAvo->cor == 0) tAvo->cor = 1;
					else tAvo->cor = 0;
					tAvo->left->cor = 1;
					arvore = verificaRubroNegra(arvore, tAvo, tAvo->chave);
					if(arvore->raiz->cor == 0) arvore->raiz->cor = 1;
					return arvore;
				}
			}else return arvore;
		}else if(t->chave < tDad->chave){//nodo eh filho a esquerda
			if(tDad->cor == 0){
				t->dad = tAvo;
				tDad->dad = t;
				tAvo->right = t;
				tDad->left = NULL;
				t->right = tDad;
				arvore = verificaRubroNegra(arvore, tDad, tDad->chave);
				return arvore;
			}else return arvore;
		}
	}
}

TpArvore* inserir(TpArvore *arvore, TpNodo *nodo, int key){
	TpArvore *a = arvore;
	TpNodo *t = nodo;

	if(a->raiz == NULL){
		a->raiz = a->sentinela;
		a->sentinela->chave = key;
		return a;
	}
	if(!verificaKey(t, key)){
		if(key < t->chave){
			if(t->left != NULL) a = inserir(a, t->left, key);
			else{
				TpNodo *novo = (TpNodo*)malloc(sizeof(TpNodo));
				t->left = novo;
				novo->nivel = 1;
				novo->chave = key;
				novo->cor = 0;
				novo->dad = t;
				novo->left = NULL;
				novo->right = NULL;
				a = verificaRubroNegra(a, novo, novo->chave);
				return a;
			}
		}
		else if(key > t->chave){
			if(t->right != NULL) a = inserir(a, t->right, key);
			else{
				TpNodo *novo = (TpNodo*)malloc(sizeof(TpNodo));
				t->right = novo;
				novo->nivel = 1;
				novo->chave = key;
				novo->cor = 0;
				novo->dad = t;
				novo->left = NULL;
				novo->right = NULL;
				a = verificaRubroNegra(a, novo, novo->chave);
				return a;
			}
		}
	}else{
		printf("<<Esta chave ja foi inserida!>>\n\n");
		return a;
	}
}

char obterCor(TpNodo *nodo){
	if(nodo->cor == 1) return 'P';
	else if(nodo->cor == 0) return 'V';
}

int obterPai(TpNodo *nodo){
	if(nodo->dad == NULL) return 0; //caso nao tenha pai - (raiz)
	else if(nodo->dad != NULL) return nodo->dad->chave;
}

void listaDados(TpNodo *nodo){
	printf("-> %d Nivel[%d] Dad[%d] %c\n", nodo->chave, nodo->nivel, obterPai(nodo), obterCor(nodo));
	if(nodo->left != NULL) listaDados(nodo->left);
	if(nodo->right != NULL) listaDados(nodo->right);
}

void destroiArvore(TpNodo *nodo){
	TpNodo *t = nodo;
	if(t->left != NULL) destroiArvore(t->left);
	if(t->right != NULL) destroiArvore(t->right);
	free(t);
}

void atualizaNivel(TpNodo *nodo, int level){
	TpNodo *t = nodo;
	t->nivel = level;
	if(t->left != NULL) atualizaNivel(t->left, level + 1);
	if(t->right != NULL) atualizaNivel(t->right, level + 1);
}

int menu(){
	int op;
	printf("1-Inserir valor;\n2-Listar elementos;\n0-Sair\n");
	scanf("%d", &op);
	return op;
}