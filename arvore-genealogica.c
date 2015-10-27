#include<stdio.h>
#include<stdlib.h>
#include <string.h>

struct pessoa
{
	char*nome;
	struct pessoa * esq;
	struct pessoa * dir;
};

struct pessoa*raiz;

struct pessoa*novo;

void busca(struct pessoa*no, char*nomefilho){

	if(no!=NULL && novo==NULL){

		if(strcmp(nomefilho,no->nome)==0){
			novo = no;
		}
		busca(no->esq,nomefilho);
		busca(no->esq,nomefilho);
	}

}


void add(struct pessoa*no,char*nomefilho,char*nomepai,char*nomemae,int n){

    struct pessoa *pai = (struct pessoa*)malloc(sizeof(struct pessoa));
	struct pessoa *mae = (struct pessoa*)malloc(sizeof(struct pessoa));
	pai->nome = nomepai;
	pai->dir = NULL;
	pai->esq = NULL;
	mae->nome = nomemae;
	mae->dir = NULL;
	mae->esq = NULL;
	no->esq = pai;
	no->dir = mae;

	n=n--;

	if(n>0){

        char novofilho[50],novopai[50],novomae[50];
        novo=NULL;
        scanf("%s %s %s",novofilho,novopai,novomae);
        busca(raiz,novofilho);
        add(novo,novofilho,novopai,novomae,n);


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

		struct pessoa*raiz = (struct pessoa*) malloc(sizeof(struct pessoa));
		scanf("%s %s %s",nomefilho,nomepai,nomemae);
		raiz->nome = nomefilho;
		raiz->esq = NULL;
		raiz->dir = NULL;

		add(raiz,nomefilho,nomepai,nomemae,n);

		labelledbracketing(raiz);

	}
}
