#include <stdio.h>
#include <stdlib.h>

typedef struct {
	unsigned int Flag01:1;
	unsigned int Flag02:1;
	unsigned int Flag03:2;
	unsigned int Flag04:2;
}Flag;

typedef enum TokenType{
	TEXTO=1,
	INTEIRO=2,
	REAL=3,
} TokenType;

typedef union Value {//um valor de cada vez
	int i;
	double r;
	char *t;
} Value;

typedef struct Token{
	TokenType tt;
	Value v;
}Token;

typedef struct Node{
	struct Node *prox;
	Token t;
}Node;

Node *novoInteiro(int i){
	Node *p = (Node *)malloc(sizeof(Node));
	p->prox = NULL;
	p->t.tt = INTEIRO;
	p->t.v.i = i;
	return p;
}
Node *novoReal(double r){
	Node *p = malloc(sizeof(Node));
	p->prox = NULL;
	p->t.tt = REAL;
	p->t.v.r = r;
	return p;
}
Node *novoTexto(char  *t){
	Node *p = malloc(sizeof(Node));
	p->prox = NULL;
	p->t.tt = TEXTO;
	p->t.v.t = t;    
}    
