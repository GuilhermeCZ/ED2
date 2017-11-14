#include <stdio.h>
#include "funcoes.h"

int main(void){
	TpArvore *tree = inicializa();
	int valor, op = 1;

	while(op != 0){
		op = menu();
		switch(op){
			case 1:	printf("Digite a chave: ");
					scanf("%d", &valor);
					printf("\n");
					tree = inserir(tree, tree->sentinela, valor);
					atualizaNivel(tree->sentinela, 1); break;
			case 2: listaDados(tree->sentinela);
					printf("\n"); break;
			case 0: destroiArvore(tree->sentinela);
					free(tree); break;
			default : printf("Opcao invalida!\n"); break;
		}
	}
}
