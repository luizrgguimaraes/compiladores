#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define TAM 3000


void loop(char **e, char **p,char *vetor,int *pos);
void codigo(char **e, char **p,char *vetor,int *pos);


void loop(char **e,char **p,char *vetor,int *pos){
	int i = 0;
	char *inicioloop = *p;
	char *fimloop;
	while(1){
		if(**p=='['){
			if(*(vetor+*pos)==0){
				*p=fimloop;
				break;
			}else{
				(*p)++;
			}
		}
		if(**p==']'){
			//printf("fim do loop\n");
			fimloop = *p;
			*p = inicioloop;
		}else{
			//printf("loop->codigo %c\n",**p);
			codigo(e,p,vetor,pos);
		}
		i++;
	}
	(*p)++;	
}

void codigo(char **e,char **p,char *vetor,int *pos){
	int c;
		//printf("codigo:%c\n",**p);
		switch(**p){
			case '>':
				(*pos)++;
				//printf("pos++=%d\n",*pos);
				(*p)++;
				break;
			case '<':
				(*pos)--;
				//printf("pos--=%d\n",*pos);
				(*p)++;
				break;
			case '+':
				//printf("soma byte antes %c\n",*(vetor+*pos));
				c = (int)*(vetor+*pos);
				c++;
				*(vetor+*pos)=(char)c;
				//printf("soma byte depois %c\n",*(vetor+*pos));
				(*p)++;
				break;
			case '-':
				c = (int)*(vetor+*pos);
				c--;
				*(vetor+*pos)=(char)c;
				//printf("subtrai byte %c\n",*(vetor+*pos));
				(*p)++;
				break;
			case '.':
				printf("print:%c\n",*(vetor+*pos));
				(*p)++;
				break;
			case ',':
				if(*(*e)=='\0'){
					*(vetor+*pos)=0;
				}else{
					*(vetor+*pos) = **e;
				}
				(*e)++;
				//printf("ler %c\n",*(vetor+*pos));
				(*p)++;
				break;
			case '[':
				//printf("call loop\n");
				loop(e,p,vetor,pos);
				
		}
		
}

void print(char *vetor){
	printf("Vetor:");
	for(int i=0;i<TAM;i++){
		printf("%c",*(vetor+i));
	}
	printf("\n");
}

typedef struct Registrador{
	int valor;
	char *nome;

} Registrador;


typedef enum TokenType{
	VARIAVEL  = 1,
	INTEIRO = 2,
	ATRIBUICAO = 3,
	SOMA = 4
} TokenType;

typedef union Tipos{
	Registrador var;
	int inteiro;
	char operador;
} Tipos;

typedef struct Token{
	TokenType tt;
	Tipos v;
	int operacao;
}Token;




Token *novaVariavel(char *nome){
	Token *token = (Token *)malloc(sizeof(Token));
	token->tt = VARIAVEL;
	token->operacao = 0;
	token->v.var.valor = 0;	
	token->v.var.nome = nome;
//	variavel->v->var.valor = 0;
//	variavel->v->var.nome = nome;
	return token;
}
	
Token *novoInteiro(char *inteiro){
	Token *token = (Token *)malloc(sizeof(Token));
	token->tt = INTEIRO;
	token->operacao = 0;
	token->v.inteiro = atoi(inteiro);	
	return token;
}	
Token *novoOperador(char *operador){
	Token *token = (Token *)malloc(sizeof(Token));
	if(*operador == '='){
		token->tt = ATRIBUICAO;
	}else if(*operador == '+'){
		token->tt = SOMA;
	}
	token->v.inteiro = 0;
	return token;
}	


Token *analisar(char *p){
	Token *token = NULL;
	if(*p >= 'a' && *p <= 'z'){
		token = novaVariavel(p);
	}else if(*p >= '0' && *p <= '9'){
		token = novoInteiro(p);
	
	}else if(*p == '=' || *p == '+'){
		token = novoOperador(p);
	}
	return token;
}	

Token *calcular(Token *token,Token *nextToken){
	if(nextToken == NULL)return token;
	if(token->tt == VARIAVEL){
		
		if(nextToken->tt == ATRIBUICAO){
			token->v.var.valor = nextToken->v.inteiro; 
		}else if(nextToken->tt == SOMA){
			token->v.var.valor += nextToken->v.inteiro;
		}
		printf("VARIAVEL %s = %d\n",token->v.var.nome,token->v.var.valor);
		
	}else if(token->tt == INTEIRO){
		if(nextToken->tt == ATRIBUICAO){
			token->v.inteiro = nextToken->v.inteiro; 
		}else if(nextToken->tt == SOMA){
			token->v.inteiro += nextToken->v.inteiro;
		}
		printf("INTEIRO = %d\n",token->v.inteiro);
	}else if(token->tt == ATRIBUICAO || token->tt == SOMA){
		token->v.inteiro = nextToken->v.inteiro; 
		printf("ATRIBUICAO TIPO%d = %d\n",token->tt,token->v.inteiro);

	}
	return token;
	//printf("resultado proximo = %d\n",resultado);
}


Token *nextToken(FILE *file){
	char vetor[3000];	
	char *p = vetor;
	char *head = p;
	*p = getc(file);
	while(*p != EOF){
		//printf("caractere extraido = %c\n",*p);
		if(*p == ' ' || *p == '\n'){
			*p = '\0';
			//printf("Entrou no If\n");
			//printf("%s\n",head);
			//if(*p == '\n')break;
			Token *token = analisar(head);
			
			//resultado = nextToken(file);
			token = calcular(token,nextToken(file));
			return token;
			
			//if(token->tt == INTEIRO)return token->v.inteiro;			
			//if(token)
		}
		p++;
		*p = getc(file);
	}
	return NULL;
}


int main(){
	FILE *file;
	file = fopen("entradaCompiladorSimples.txt","r");

	Token *token = nextToken(file);
	printf("Resultado Final = %d\n",token->v.var.valor);

	return 0;
}


