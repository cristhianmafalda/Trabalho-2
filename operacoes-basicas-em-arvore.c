#include<stdio.h>
#include<stdlib.h>

	struct arvore								//definindo a estrutura da arvore
	{
		int key;								//key é o valor associado a cada nó
		struct arvore * esq;					//ponteiros para os filhos de cada nó
		struct arvore * dir;
	};

void add(struct arvore*no, int chave){			//add é a função que adiciona um valor na arvore

	struct arvore *novo = no;					//nó é o filho que está sendo insrido na arvore
	struct arvore *origin = NULL; 				//pai será o nó oque vai apontar para esse filho

	while (novo!=NULL){							//quando novo for NULL, será encontrada sua posição
		origin=novo;							//enquanto não encontramos, vamos buscando ordenadamente pelos ponteiros
		if(chave>=novo->key){
			novo = novo->dir;
		}
		else {
			novo = novo->esq;
		}
	}
	
	struct arvore *valor = (struct arvore*)malloc(sizeof(struct arvore));  // alocamos criamos a estrutura para esse novo valor	
	valor->key = chave;
	valor->dir = NULL;
	valor->esq = NULL;
	
	if (origin->key>chave){						//vamos fazer o pai apontar para o filho comparando suas chaves
		origin->esq=valor;
	}
	else {
		origin->dir=valor;
	}
	
		

}

void emordem(struct arvore*no){					// em ordem é uma função que imprime os valores da arvore de maneira ordenada
	if(no!=NULL){
		emordem(no->esq);						//busca os menores para imprimir
		printf("%d ",no->key);					//imprime o valor
		emordem(no->dir);						//segue para os maiores
	}
}

void main () {
	
	int n,i,chave;
	scanf("%d",&n);
	
	if(n>0){
		
		printf("Digite a quantidade inicial de valores a ser digitado.Em seguida, insira os valores.\n");
		
		struct arvore*raiz = (struct arvore*) malloc(sizeof(struct arvore));
		scanf("%d",&chave);
		raiz->key = chave;
		raiz->dir = NULL;
		raiz->esq = NULL;
		
		for(i=1;i<n;i++){
			scanf("%d",&chave);
			add(raiz,chave);
		}
		
		printf("\nDigite o n%cmero da op%c%co que deseja realizar com sua %crvore:",163,135,198,160);
		printf("\nOp%c%co 1: Inser%c%co",135,198,135,198);
		printf("\nOp%c%co 2: Remo%c%co",135,198,135,198);
		printf("\nOp%c%co 3: Busca",135,198);
		printf("\nOp%c%co 4: Impress%co em 'Pr%c Ordem'",135,198,198,130);
		printf("\nOp%c%co 5: Impress%co em 'Em Ordem'",135,198,198);
		printf("\nOp%c%co 6: Impress%co em 'P%cs Ordem'",135,198,198,162);
		printf("\nOp%c%co 7: Impress%co em 'Labelled Bracketing'",135,198,198);
		printf("\nOp%c%co 0: Sair",135,198);
		
		
		emordem(raiz);
	}
	

	
	
getch();	
}


