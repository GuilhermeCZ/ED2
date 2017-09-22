#include <stdlib.h>
#include <stdio.h>


struct node{
	int key;   //chave de identificação do nodo
	node *left, *right, *pai;		//ponteiros para os filhos
	node *raiz;
};


void transplant (node *r, node *x, node *i) {
	if (x->pai == NULL) {
		r->raiz == i;
	} else if (x == x->pai->left) {
		x->pai->left = i;
	} else {
		x->pai->right = i;
	}
	if (i != NULL) {
		i->pai = x->pai;
	}
}

node *min(node *r) {

	if(r->left != NULL) min(r->left);

	return r;
}


//busca por uma chave k na árvore com raiz r
//caso a chave não estiver na árvore retorna NULL

node * search (node * r, int key){
	if(!r || r->key == key ) return r;				//n encontrou a chave

	if(key <= r->key) return search (r->left, key);

	return search (r->right, key);
}

//mostra todas as chaves da árvore

void * print (node * r);

//insere um nodo com chave key na árvore com raiz r
//retorna um ponteiro para a raiz da árvore

node * insert (node * r, int key){
	node * n = (node *)malloc(sizeof(node));		//cria um novo nodo
	n->left = n->right = NULL;
	n->key = key;

	if(!r) return n;			// se a arvore estiver vazia

	node * it = r;	// it é o pai de N

	while(1){
		if(key < it->key){
			if(!it->left){
				it->left = n; 		//atualiza o filho da esquerda de r
        n->pai = it;
				break;
			}
			it = it->left;
		}else{
			if(!it->right){
				it->right = n;
        n->pai = it;
				break;
			}
			it = it->right;
		}
	}

	return r;
}

//remove o nodo da árvore com raiz r que possui chave igual a key
//(lembra que tem que dar free no nodo)
void remove (node * t, int key) {
  node * it = t, *y;
	it = search(t, key);
  do {
    if(it){
			if (it->left == NULL) {
				transplant(t, it, it->right);
			}
			else if (it->right == NULL) {
				transplant(t, it, it->left);
			}
			else {
				y = min(it->right);
				if (y != it->right) {
					transplant(t, y, y->right);
					y->right = it->right;
					y->right->pai = y;
					transplant(t, it, y);
					y->left = it->left;
					y->left->pai = y;
				}
			}
			free(it);
      it == NULL;
    }
  } while(it->left == NULL && it->right == NULL);

}

void printtree(node *t) {
	if (t == NULL)	return;
		printtree(t->left);
		printf("%d\n", t->key);
		printtree(t->right);
}

void printtreepos(node *t) {
	if (t == NULL)	return;
		printtree(t->left);
		printtree(t->right);
		printf("%d\n", t->key);
}

void printtreepre(node *t) {
	if (t == NULL)	return;
		printf("%d\n", t->key);
		printtree(t->left);
		printtree(t->right);
}

int main ( void ){

	int n, i=0, op=0;

	node * root = NULL;
	root->raiz->pai == NULL;

	do {
		printf("1. Add node\n");
		printf("2. Remove\n");
		printf("3. Search\n");
		printf("4. In order\n");
		printf("5. Pre-order\n");
		printf("6. Post-order\n");
		printf("7. Exit\n");
		scanf("%d", &op);

		switch (op) {
			case 1:
				printf("Add to node\nValue: ");
				scanf("%d", &n);
				root = insert(root, n);
				printf("\n");
			break;
			case 2:
				printf("Remove node\nValue: ");
				scanf("%d", &n);
				remove(root, n);
				printf("\n");
			break;
			case 3:
				printf("Search for node\nValue: ");
				scanf("%d", &n);
				(search(root, n)) ? (printf("Achou %d\n", n)) : (printf("Não Achou :(\n"));
				printf("\n");
			break;
			case 4:
				printf("In order\n");
				printtree(root);
				printf("\n");
			break;
			case 5:
				printf("Pre-order\n");
				printtreepre(root);
				printf("\n");
			break;
			case 6:
				printf("Post-order\n");
				printtreepos(root);
				printf("\n");
			break;
			case 7:
			break;
		}
	} while(op != 7);

	return 0;
}
