#include<stdio.h>
#include<stdlib.h>

struct simbolo				
	{
		char caractere;								
		struct simbolo * prox;				
	};
	
struct arvore				
	{
		char caractere;								
		struct arvore * dir;
		struct arvore * esq;				
	};
		
void addsimbolo(struct simbolo*inicial, char caractere){
	
	if(inicial->prox==NULL){
		struct simbolo*novo = (struct simbolo*)malloc(sizeof(struct simbolo));
		novo->caractere = caractere;
		novo->prox = NULL;
		inicial->prox = novo;
		printf("\n\n\n\n\n\n\n\n%c\n\n\n\n\n\n",caractere);
	}
	
	else{
		addsimbolo(inicial->prox, caractere);
	}
	
}

struct simbolo * addnumero(struct simbolo*seguinte, char valor){
		
	struct simbolo*novo = (struct simbolo*)malloc(sizeof(struct simbolo));
	novo->caractere = valor;
	novo->prox = seguinte;
	return(novo);
		
}
	
void fazerarvore(struct arvore*raiz, struct simbolo*operador, struct simbolo*numero){
	
	if(operador!=NULL && numero!=NULL){
		return;
	}
	
	struct arvore*esquerda = (struct arvore*)malloc(sizeof(struct arvore));
	esquerda->caractere = operador->caractere;
	esquerda->dir = NULL;
	esquerda->esq = NULL;
	struct arvore*direita = (struct arvore*)malloc(sizeof(struct arvore));
	direita->caractere = numero->caractere;
	direita->dir = NULL;
	esquerda->esq = NULL;
	
	raiz->esq = esquerda;
	raiz->dir = direita;
	
	fazerarvore(direita,operador->prox,numero->prox);
	
}
	
void rpn(struct arvore*no){					
	if(no!=NULL){
		rpn(no->dir);						
		printf("%c ",no->caractere);					
		rpn(no->esq);						
	}
}	

void imprime(struct arvore*no){
	printf("%c",no->caractere);
}

void infixa(struct arvore*no){					
	if(no->dir!=NULL){
		printf("(");
		infixa(no->dir);
		imprime(no->dir);	
		imprime(no->esq);
		imprime(no);															
		printf(")");
	}
}
	
void imprimelista(struct simbolo*no){
	
	while(no!=NULL){
		printf(" %c",no->caractere);
		imprimelista(no->prox);
	}
	
}	
	
void main () {
	
	printf("Digite a equacao\n\n");
	
	char c;
	int i=0,j=1;
	
	scanf("%c",&c);
	
	struct simbolo*firstc = (struct simbolo*)malloc(sizeof(struct simbolo));
	firstc->caractere = c;
	firstc->prox = NULL;
	
	while(i=0){
		
		scanf("%c",&c);
		
		if(c=='+'||c=='-'||c=='/'||c=='*'||c==10||c==' '){
			if(c=='+'||c=='-'||c=='/'||c=='*'){
				addsimbolo(firstc,c);
				j++;
			}
		}
		else{
			i=1;
		}

	}
	
	struct simbolo*firstn = (struct simbolo*)malloc(sizeof(struct simbolo));
	firstn->caractere = c;
	firstn->prox = NULL;

	
	for (i=0;i<j;i++){
		scanf("%c",&c);
		firstn = addnumero(firstn,c);
	}
	
	printf("\n\nCaracteres: ");
	imprimelista(firstc);
	printf("\n\nNumeros: ");
	imprimelista(firstn);
	
	struct arvore*raiz = (struct arvore*)malloc(sizeof(struct arvore));
	raiz->caractere = firstn->caractere;
	raiz->esq = NULL;
	raiz->dir = NULL;
	
	fazerarvore(raiz,firstc,firstn->prox);
	
	printf("\n\nRPN: ");
	rpn(raiz);
	
	printf("\n\nINFIXA: ");
	infixa(raiz);

	
	
}
