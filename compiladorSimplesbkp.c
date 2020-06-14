#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define TAM 3000



typedef struct Variavel{
	char nome[10];
	int valor;
} Variavel;


typedef enum TokenType{
	VARIAVEL  = 1,
	INTEIRO = 2,
	ATRIBUICAO = 3,
	SOMA = 4
} TokenType;

typedef union Tipos{
	Variavel v;
	int i;
	char o;
} Tipos;

typedef struct Token{
	TokenType tt;
	Tipos tipo;
}Token;

typedef struct Registrador{
	int set;
	Token *token;
}Registrador;


Registrador registradores[10];



Token *novaVariavel(char *nome){
	Token *token = (Token *)malloc(sizeof(Token));
	token->tt = VARIAVEL;
	strcpy(token->tipo.v.nome,nome);
	token->tipo.v.valor = 0;
	return token;
}
	
Token *novoInteiro(char *inteiro){
	Token *token = (Token *)malloc(sizeof(Token));
	token->tt = INTEIRO;
	token->tipo.i = atoi(inteiro);
	return token;
}	

Token *novoOperador(char *operador){
	Token *token = (Token *)malloc(sizeof(Token));
	if(*operador == '='){
		token->tt = ATRIBUICAO;
	}else if(*operador == '+'){
		token->tt = SOMA;
	}
	token->tipo.i = 0;
	return token;
}	



void printToken(Token *token){
	if(token == NULL){
		printf("token NULL\n");
	}else if(token->tt == VARIAVEL){
		printf("token VARIAVEL %s = %d\n",token->tipo.v.nome,token->tipo.v.valor);
	}else if(token->tt == INTEIRO){
		printf("token INTEIRO = %d\n",token->tipo.i);

	}else if(token->tt == ATRIBUICAO){
		printf("token ATRIBUICAO = %d\n",token->tipo.i);

	}else if(token->tt == SOMA){
		printf("token SOMA = %d\n",token->tipo.i);

	}
}

Token *analisar(char *p){
	Token *token = NULL;
	if(*p >= 'a' && *p <= 'z'){
		for(int i=0;i<10;i++){
			printf("registradores[%d].set = %d\n",i,registradores[i].set);
			if(registradores[i].set != 0){
				printf("registradores[%d].token->tipo.v.nome = %s\n",i,registradores[i].token->tipo.v.nome);
				printf("registradores[%d].token->tipo.v.valor = %d\n",i,registradores[i].token->tipo.v.valor);
				if(strcmp(registradores[i].token->tipo.v.nome, p)==0){
					token = registradores[i].token;
					break;
				}
			}else{
				token =  novaVariavel(p);
				registradores[i].token = token;
				registradores[i].set = 1;
				printf("setou registradores[%d].token->tipo.v.nome = %s\n",i,registradores[i].token->tipo.v.nome);
				break;
			}
			
		}
	}else if(*p >= '0' && *p <= '9'){
		token = novoInteiro(p);
	
	}else if(*p == '=' || *p == '+'){
		token = novoOperador(p);
	}
	printToken(token);
	return token;
}	

Token *calcular(Token *token,Token *nextToken){
	printf("calcular 2 tokens\n");
	printToken(token);
	printToken(nextToken);


	if(nextToken == NULL)return token;
	if(token->tt == VARIAVEL){
		if(nextToken->tt == ATRIBUICAO){
			token->tipo.v.valor = nextToken->tipo.i; 
		}else if(nextToken->tt == SOMA){
			token->tipo.v.valor += nextToken->tipo.i;
		}
		//printf("VARIAVEL %s = %d\n",token->v.var.nome,token->v.var.valor);
		
	}else if(token->tt == INTEIRO){
		if(nextToken->tt == ATRIBUICAO){
			token->tipo.i = nextToken->tipo.i; 
		}else if(nextToken->tt == SOMA){
			token->tipo.i += nextToken->tipo.i;
		}
		//printf("INTEIRO = %d\n",token->v.inteiro);
	}else if(token->tt == ATRIBUICAO || token->tt == SOMA){
		if(nextToken->tt == VARIAVEL){
			token->tipo.i = nextToken->tipo.v.valor; 
		}else{
			token->tipo.i += nextToken->tipo.i;
		}
ntf("ATRIBUICAO TIPO%d = %d\n",token->tt,token->v.inteiro);

	}
	printf("calculou token\n");
	printToken(token);
	return token;
	//printf("resultado proximo = %d\n",resultado);
}


Token *nextToken(FILE *file){
	char vetor[3000];	
	char *p = vetor;
	char *head = p;
	Token *next;
	Token *token;
	*p = getc(file);

	if(*p == '\n'){//caso de sobras de Enter
		return NULL;
	}

	while(*p != EOF){
		if(*p == ' ' || *p == '\n'){
			if(*p == ' '){
				*p = '\0';
				printf("vai analisar %s\n",head);
				token = analisar(head);
				next = nextToken(file);
			}else{
				*p = '\0';
				printf("vai analisar %s\n",head);
				token = analisar(head);
				next = NULL;
			}

			return calcular(token,next);
		}
		p++;
		*p = getc(file);
	}

	return NULL;
}


int main(){
	FILE *file;
	file = fopen("entradaCompiladorSimples.txt","r");
	for(int i=0;i<10;i++){
		registradores[i].set = 0;
	}

	while(1){
		Token *token = nextToken(file);
		if(token==NULL)break;
		printf("%s = %d\n",token->tipo.v.nome,token->tipo.v.valor);
	}
	return 0;
}


