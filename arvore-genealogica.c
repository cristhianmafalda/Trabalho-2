#include<stdio.h>
#include<stdlib.h>

struct pessoa						
{
	char *nome;								
	struct arvore * esq;					
	struct arvore * dir;
};

struct pessoa*search(struct pessoa*no, char*nomefilho){
	
	if(no==NULL){
		return(NULL);
	}
	if(nomefilho == no->nome){
		return(no);
	}
	if((search(no->esq,nomefilho))!=NULL){
		return (search(no->esq,nomefilho));
	}
	else{
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
		pai->dir = NULL;
		pai->esq = NULL;
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
	char*nomefilho,*nomepai,*nomemae;
	 
	scanf("%d",&n);
	
	if(n>0){
		
		struct pessoa*arvore = (struct pessoa*) malloc(sizeof(struct pessoa));
		scanf("%s%s%s",nomefilho,nomepai,nomemae);
		arvore->nome = nomefilho;
		arvore->esq = NULL;
		arvore->dir = NULL;
		add(arvore,nomefilho,nomepai,nomemae);
		
		for(i=1;i<n;i++){
			scanf("%s%s%s",nomefilho,nomepai,nomemae);
			add(arvore,nomefilho,nomepai,nomemae);
		}
		
		labelledbracketing(arvore);
			
	}
}
