#include<stdio.h>
#include<stdlib.h>
#include <string.h>

struct pessoa						
{
	char *nome;								
	struct pessoa * esq;					
	struct pessoa * dir;
};

struct pessoa*search(struct pessoa*no, char*nomefilho){
	
	if(no==NULL){
		return(NULL);
	}
	if(strcmp(nomefilho,no->nome)==0){
		return(no);
	}
	if((search(no->esq,nomefilho))!=NULL){
		return (search(no->esq,nomefilho));
	}
	if((search(no->dir,nomefilho))!=NULL){
		return (search(no->dir,nomefilho));
	}
}	

void add(struct pessoa*arvore,char*nomefilho,char*nomepai,char*nomemae){			

	struct pessoa *pai = (struct pessoa*)malloc(sizeof(struct pessoa));					
	struct pessoa *mae = (struct pessoa*)malloc(sizeof(struct pessoa));	
	struct pessoa *busca = (struct pessoa*)malloc(sizeof(struct pessoa));
	busca = search(arvore,nomefilho);
	if(busca!=NULL){
		busca->esq = pai;
		busca->dir = mae;	
		pai->nome = nomepai;
		pai->dir = NULL;
		pai->esq = NULL;
		mae->nome = nomemae;
		mae->dir = NULL;
		mae->esq = NULL;
	}
}

void labelledbracketing(struct pessoa*arvore){					
	printf("[");
	if(arvore!=NULL){
		printf("%s",arvore->nome);
		labelledbracketing(arvore->esq);
		labelledbracketing(arvore->dir);																
	}
	printf("]");
}

void main () {
	
	printf("Digite a quantidade inicial de valores a ser digitado.\nEm seguida, insira os valores.\n\n");
	int n,i;
	char nomefilho[50],nomepai[50],nomemae[50];
	 
	scanf("%d",&n);
	
	if(n>0){
		
		struct pessoa*armazenaraiz = (struct pessoa*) malloc(sizeof(struct pessoa));
		struct pessoa*raiz = (struct pessoa*) malloc(sizeof(struct pessoa));
		scanf("%s %s %s",nomefilho,nomepai,nomemae);
		raiz->nome = nomefilho;
		raiz->esq = NULL;
		raiz->dir = NULL;
		add(raiz,nomefilho,nomepai,nomemae);
		
		armazenaraiz = raiz;
		
		for(i=1;i<n;i++){
			scanf("%s %s %s",nomefilho,nomepai,nomemae);
			add(raiz,nomefilho,nomepai,nomemae);
		}
		
		printf("\n%s\n",armazenaraiz->nome);
		labelledbracketing(armazenaraiz);
			
	}
}
