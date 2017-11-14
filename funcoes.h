#include "funcoes.cpp"

TpArvore* inicializa();
TpArvore* inserir(TpArvore *arvore, TpNodo *nodo, int key);
void listaDados(TpNodo *nodo);
void destroiArvore(TpNodo *nodo);
void atualizaNivel(TpNodo *nodo, int level);
int menu();