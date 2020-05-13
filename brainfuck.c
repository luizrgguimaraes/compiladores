#include <stdio.h>
#include <stdlib.h>

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

int main(){
	
	//char *entrada = "marrocos";
	char *entrada = "nada";
	char *e = entrada;
	
	//char *programa = "+[>,]<-[+.<-]";
	char *programa = "++++++++++[>+++++++>++++++++++>+++>+<<<<-]>++.>+.+++++++..+++.>++.<<+++++++++++++++.>.+++.------.--------.>+.>.";
	char *p = programa;	
	char vetor[3000];
	for(int i=0;i<3000;i++)vetor[i]=0;
	//print(vetor);
	int i=0;
	int pos=0;
	while(*p!='\0'){
		//printf("main->programa=%c\n",*p);
		codigo(&e,&p,vetor,&pos);
		//print(vetor);
		i++;
		//if(i>=8)break;
	}

return 0;
}


