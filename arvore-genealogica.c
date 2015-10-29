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

int menu(){

		printf("\nDigite o n%cmero da op%c%co que deseja realizar com sua %crvore geneal%cgica:",163,135,198,160,162);
		printf("\nOp%c%co 1: Impress%co dos Membros por Gera%c%co",135,198,198,135,198);
		printf("\nOp%c%co 2: Impress%co dos Antepassados de uma Pessoa",135,198,198);
		printf("\nOp%c%co 3: Impress%co Labelled Bracketing",135,198,198);
        printf("\nOp%c%co 4: C%clculo do Grau de Parentesco",135,198,160);

		printf("\n\nOp%c%co escolhida: ",135,198);
		int opcao;
		scanf("%d",&opcao);
		printf("\n");

		return(opcao);

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

    int opcao,fim = 1;
    char antepassado[50];

    while(fim==1){

        opcao = menu();

        if(opcao==1){
            for(i=0;i<=maxgen;i++){
                printf("\n\nGen %d: ",i);
                imprimegen(raiz,i,nome);
            }
        }

        if(opcao==2){
            printf("\n\nDigite a pessoa de quem deseja ver os antepassados:  ");
            scanf("%s",antepassado);
            k=-1;
            for (j=0;j<3*n;j++){
                if(strcmp(antepassado,nome[j])==0){
                k=j;
                j=3*n;
                }
            }
            if(k!=-1){
                buscado = NULL;
                localiza(raiz,k);
                for(i=buscado->geracao;i<=maxgen;i++){
                    printf("\n\nGen %d: ",i);
                    imprimegen(buscado,i,nome);
                }
            }


        }

        if(opcao==3){
            printf("\n\nLabelled Bracketing:  ");
            labelledbracketing(raiz,nome);
        }

        if(opcao==4){

        }

        if(fim!=2){
				printf("\n\nDeseja continuar no programa %c    1-SIM  2-N%cO\n",63,199);
				scanf("%d",&fim);
			}

    }

    printf("\nPROGRAMA ENCERRADO");
    getch();

}
