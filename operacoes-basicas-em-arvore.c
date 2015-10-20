#include<stdio.h>

void add(struct arvore*no, int chave){

	while (no!=NULL){
		if(chave>=no->chave){
			add(no->dir,chave);
		}
		else add(no->esq,chave);
		}
		
	if(no==NULL){
		no->chave=chave;
	}	
		

}

void emordem(struct arvore*no){
	if(no!=NULL){
		emordem(no->esq);
		printf("%d",no->chave);
		emordem(no->dir);
	}
}

void main () {
	
	struct arvore
	{
		int chave;
		struct arvore * esq;
		struct arvore * dir;
	};
	
	int n,i;
	scanf("%d",&n);
	
	if(n>0){
		
		struct arvore raiz
		scanf("%d",&raiz.chave);
		raiz.dir = NULL;
		raiz.esq = NULL;
		
		struct arvore novo;
	
		for(i=1;i<n;i++){
		novo = (struct arvore*)malloc(sizeof(struct arvore));
		scanf("%d",&novo.chave);
		novo.dir = NULL;
		novo.esq = NULL;
		add(*raiz,novo.chave);
		}
	
	}
	
	emordem(raiz);
	
	
getch();	
}


