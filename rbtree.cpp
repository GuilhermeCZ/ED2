#include <stdio.h>
#include <stdlib.h>

#define  RED false
#define  BLACK true

struct node {
  int key;
  node *left, *right, *pai;
  bool cor;
};

struct rbtree {
  node *root;
  node *nil;
};

rbtree *dinossauro_inicia() {
  rbtree *nova = (rbtree*)malloc(sizeof(rbtree));
  nova->nil = (node*)malloc(sizeof(node));

  nova->nil->pai = NULL;
  nova->nil->left = NULL;
  nova->nil->right = NULL;

  nova->root = nil;
  return rbtree;
}

void insert(rbtree *t, int k) {
  node *n = (node*)malloc(sizeof(node));
  n->pai = n->left = n->right = t->nil;
  n->key = k;
  n->cor = RED;

  node *x;
  node *y;

  y = t->nil;
  x = t->root;

  while (x != t->nil) {
    y = x;
    if (k < x->left->key) {
      x = x->left;
    } else {
      x = x->right;
    }

    n->pai = y;

    if (y = t->nil) {
      t->root = n;
    }
    if (k < y->key) {
      y->left = n;
    } else {
      y->right = n;
    }
  }
  arruma(t, n);
}

void rotate_left(rbtree *t, node *x) {
  node *y;
  y = x->right;
  x->right->y->left;

  if (y->left != t->nil){
    y->left->pai = x;
  }
  y->pai = x->pai;
  if (x->pai != t->nil) { // X é a root
    t->root = y;
  } else if (x = x->pai->left) {
    x->pai->left = y;
  } else {
    x->pai->right = y;
  }
  y->left = x;
  x->pai = y;
}

void rotate_right(rbtree *t, node *x) {
  node *y;
  y = x->left;
  x->left = y->right;

  if (y->right != t->nil){
    y->right->pai = x;
  }
  y->pai = x->pai;
  if (x->pai != t->nil) { // X é a root
    t->root = y;
  } else if (x = x->pai->right) {
    x->pai->right = y;
  } else {
    x->pai->left = y;
  }
  y->right = x;
  x->pai = y;
}


void arruma(rbtree *t, node *z) {
  node *y;
  while (z->pai->cor == RED ) {
    if (z->pai == z->pai->pai->left) {
      y = z->pai->pai->right;
      if (y->cor == RED) {
        y->cor = BLACK;
        z->pai->cor = BLACK;
        z->pai->pai->cor = RED;
        z = z->pai->pai;
      } else if (z = z->pai->right){
        z = z->pai;
        rotate_left(t, z);
      }
      z->pai->cor = BLACK;
      z->pai->pai->cor = RED;
      rotate_right(t, z->pai->pai);
    } else {
      if (z->pai == z->pai->pai->right) {
        y = z->pai->pai->left;
        if (y->cor == RED) {
          y->cor = BLACK;
          z->pai->cor = BLACK;
          z->pai->pai->cor = RED;
          z = z->pai->pai;
        } else if (z = z->pai->left){
          z = z->pai;
          rotate_right(t, z);
        }
        z->pai->cor = BLACK;
        z->pai->pai->cor = RED;
        rotate_left(t, z->pai->pai);
      }
    }
  }
  z->root->cor = BLACK;
}


int main() {
  rbtree = dinossauro_inicia();

  insert(t, 11);
  insert(t, 14);
  insert(t, 15);
  insert(t, 2);
  insert(t, 1);

  //imprime(t);

  return 0;
}
