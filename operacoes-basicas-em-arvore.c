#include<stdio.h>
#include<stdlib.h>

	struct arvore								//definindo a estrutura da arvore
	{
		int key;								//key � o valor associado a cada n�
		struct arvore * esq;					//ponteiros para os filhos de cada n�
		struct arvore * dir;
	};

void add(struct arvore*no, int chave){			//add � a fun��o que adiciona um valor na arvore

	struct arvore *novo = no;					//n� � o filho que est� sendo insrido na arvore
	struct arvore *origin = NULL; 				//pai ser� o n� oque vai apontar para esse filho

	while (novo!=NULL){							//quando novo for NULL, ser� encontrada sua posi��o
		origin=novo;							//enquanto n�o encontramos, vamos buscando ordenadamente pelos ponteiros
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

void localiza(struct arvore*no, int busca){
	
	int i=0;
	while(no!=NULL){
		if (no->key==busca){
			i=1;
		}
		else if (busca>no->key){
			localiza(no->dir,busca);
		}
		else localiza(no->esq,busca);
	}
	if(i==0){
		printf("\nO valor buscado n%co existe\n",198);
	}
	else {
		printf("\nO valor buscado existe\n");
	}
}

void emordem(struct arvore*no){					// em ordem � uma fun��o que imprime os valores da arvore de maneira ordenada
	if(no!=NULL){
		emordem(no->esq);						//busca os menores para imprimir
		printf("%d ",no->key);					//imprime o valor
		emordem(no->dir);						//segue para os maiores
	}
}

void preordem(struct arvore*no){					
	if(no!=NULL){
		printf("%d ",no->key);
		preordem(no->esq);
		preordem(no->dir);																
	}
}

void posordem(struct arvore*no){					
	if(no!=NULL){	
		posordem(no->esq);
		posordem(no->dir);
		printf("%d ",no->key);																
	}
}

void labelledbracketing(struct arvore*no){					
	printf("[");
	if(no!=NULL){
		printf("%d",no->key);
		labelledbracketing(no->esq);
		labelledbracketing(no->dir);																
	}
	printf("]");
}

void main () {
	
	printf("Digite a quantidade inicial de valores a ser digitado.\nEm seguida, insira os valores.\n\n");
	int n,i,chave;
	scanf("%d",&n);
	
	if(n>0){
		
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
		printf("\nOp%c%co 4: Impress%co Pr%c Ordem",135,198,198,130);
		printf("\nOp%c%co 5: Impress%co Em Ordem",135,198,198);
		printf("\nOp%c%co 6: Impress%co P%cs Ordem",135,198,198,162);
		printf("\nOp%c%co 7: Impress%co Labelled Bracketing",135,198,198);
		printf("\nOp%c%co 0: Sair\n",135,198);
		
		printf("\nOp%c%co escolhida: ",135,198);
		int opcao;
		scanf("%d",&opcao);
		printf("\n");
		
		if (opcao == 1){
			printf("Digite a quantidade de valores a ser inserido.\nEm seguida, insira os valores.\n\n");
			scanf("%d",&n);
			for(i=0;i<n;i++){
				scanf("%d",&chave);
				add(raiz,chave);
			}
		}
		
		if (opcao == 2){
			
		}
		
		if (opcao == 3){
			printf("\nDigite o valor buscado: ");
			scanf("%d",&chave);
			localiza(raiz,chave);
		}
		
		if (opcao == 4){
			preordem(raiz);
		}
		
		if (opcao == 5){
			emordem(raiz);
		}
		
		if (opcao == 6){
			posordem(raiz);
		}
		
		if (opcao == 7){
			labelledbracketing(raiz);
		}
		
		if (opcao == 0){
			
		}

	}
	
getch();	
}


