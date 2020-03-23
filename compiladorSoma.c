#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX 15
#define DIGIT 1
#define ALPHA 2
#define ADD 3





int main(){
	char *p = (char *) malloc(MAX*sizeof(char));
	char *pHead = p;
	char *q;
	char c = 0;
	int n=0,m=0;
	int soma=0;
	int tipo=0;
	
	while(1){
		scanf("%c",&c);
		if(isdigit(c)){
			*p=c;
			p++;
			n++;
			tipo=DIGIT;			
		}else if(c=='+'){
			*p='\0';
			soma+=atoi(pHead+m);
			*p=c;
			p++;
			n++;
			m=n;
			tipo=ADD;
		}else{
			if(c!='\n')tipo=ALPHA;
			break;
		}
	}
	//*p='\0';
	if(tipo==DIGIT){
		soma+=atoi(pHead+m);	
		printf("%d\n",soma);
	}else{
		printf("ERROR\n");	
	}

}

// -S -masm=intel - gerar arquivo assembly	