#include <stdio.h>
#include <stdlib.h>

#define TAM 3000


char *loop(char **e, char *p,char vetor[TAM],int pos);
char *codigo(char **e, char *p,char vetor[TAM],int pos);


void loop(char **e,char *p,char vetor[TAM],int pos){
	int i = 0;
	char *inicioloop = p;
	while(*p!=0&&i<10){
		if(*p==']'){
			printf("fim do loop\n");
			p = inicioloop;
		}else if(*p==0){
			printf("loop encontrou 0 - return\n");
			return p;
		}else{
			printf("loop->codigo %c\n",*p);
			p = codigo(e,p,vetor,pos);
		}
		i++;
	}	
	return p;
		
	//}
}

void codigo(char **e,char *p,char vetor[TAM],int pos){
	int c;
	int i=0;
		switch(*p){
			case '>':
				pos++;
				printf("pos++\n");
				break;
			case '<':
				pos--;
				printf("pos--\n");
				break;
			case '+':
				c = (int)vetor[pos];
				c++;
				vetor[pos]=(char)c;
				printf("soma byte %c\n",vetor[pos]);
				break;
			case '-':
				c = (int)*p;
				c--;
				*p=(char)c;
				printf("subtrai byte %c\n",*p);
				break;
			case '.':
				printf("printf\n");
				printf("%c",*p);
				break;
			case ',':
				if(*(*e)=='\0'){
					*p=0;
				}else{
					*p = *(*e);
				}
				printf("ler %c\n",*p);
				p++;
				break;
			case '[':
				printf("call loop\n");
				p = loop(e,++p,vetor,pos);
		}
		i++;
		return p;
}

int main(){
	
	char *entrada = "marrocos";
	char *e = entrada;

	char *programa = "+[>,]<-[+,<-]";

	char vetor[TAM];
	for(int i=0;i<3000;i++)vetor[i]=0;
	int i=0;
	//while(*programa!='\0'){
	//	vetor[i] = *programa;
	//	programa++;	
	//	i++;
	//}
	i=0;
	char *p = programa;
	int pos=0;
	while(*p!=0){
		printf("main->codigo %c\n",*p);
		codigo(&e,p,vetor,pos);
		p++;
		i++;
		if(i>=1)break;
	}

return 0;
}


