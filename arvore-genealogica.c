#include<stdio.h>
#include<stdlib.h>
#include <string.h>

struct pessoa
{
	int chave;
	int geracao;
	struct pessoa * esq;
	struct pessoa * dir;
};

struct pessoa*buscado;

int maxgen;

void localiza(struct pessoa*no, int chave){

    if(no!=NULL){
		localiza(no->esq,chave);
		localiza(no->dir,chave);
		if(chave==no->chave){
            buscado=no;
		}
	}

};

void labelledbracketing(struct pessoa*arvore,char nome[][50]){
	if(arvore!=NULL){
        printf("[");
	}
	if(arvore!=NULL){
		printf("%s",nome[arvore->chave]);
		labelledbracketing(arvore->esq,nome);
		labelledbracketing(arvore->dir,nome);
	}
	if(arvore!=NULL){
        printf("]");
	}
}

void preenchergeracao(struct pessoa*no,int geracao){

    if(no!=NULL){
        no->geracao=geracao;
        if(geracao>maxgen){
            maxgen = geracao;
        }
        preenchergeracao(no->esq,geracao+1);
        preenchergeracao(no->dir,geracao+1);
    }

}

void imprimegen(struct pessoa*no, int gen,char nome[][50]){

    if(no!=NULL){
        imprimegen(no->esq,gen,nome);
        if(no->geracao==gen){
            printf("%s ",nome[no->chave]);
        }
        imprimegen(no->dir,gen,nome);
    }

}

void main () {

	printf("Digite a quantidade inicial de valores a ser digitado.\nEm seguida, insira os valores.\n\n");
	int n,i,k=-1,j=-1;

	scanf("%d",&n);

    char nome[3*n][50];

	for (i=0; i<3*n; i++) {
		scanf("%s",nome[i]);
	}

	struct pessoa *raiz = (struct pessoa*)malloc(sizeof(struct pessoa));
	raiz->chave = 0;
	raiz->dir = NULL;
	raiz->esq = NULL;

    for(i=0;i<3*n;i=i+3){

        k=-1;
        for (j=0;j<3*n;j++){

            if(strcmp(nome[i],nome[j])==0){
                k=j;
                j=3*n;
            }
        }

            buscado = NULL;
            struct pessoa *novo = (struct pessoa*)malloc(sizeof(struct pessoa));
            localiza(raiz,k);
            novo = buscado;
            struct pessoa *pai = (struct pessoa*)malloc(sizeof(struct pessoa));
            struct pessoa *mae = (struct pessoa*)malloc(sizeof(struct pessoa));
            novo->esq = pai;
            novo->dir = mae;
            pai->chave = i+1;
            pai->dir = NULL;
            pai->esq = NULL;
            mae->chave = i+2;
            mae->esq = NULL;
            mae->dir = NULL;

    }

    maxgen = 0;
    preenchergeracao(raiz,0);

    for(i=0;i<=maxgen;i++){
        printf("\n\nGen %d: ",i);
        imprimegen(raiz,i,nome);
    }

    printf("\n\nLabelled Bracketing:  ");
    labelledbracketing(raiz,nome);


    getch();

}
