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

struct arvore*search(struct arvore*no, int busca){
	
	if(no==NULL){
		return(NULL);
	}
	if(busca == no->key){
		return(no);
	}
	if(busca>no->key){
		return(search(no->dir,busca));
	}
	if(busca<no->key){
		return(search(no->esq,busca));
	}
}

void emordem(struct arvore*no){					// em ordem é uma função que imprime os valores da arvore de maneira ordenada
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

int menu(){
	
		printf("\nDigite o n%cmero da op%c%co que deseja realizar com sua %crvore:",163,135,198,160);
		printf("\nOp%c%co 1: Inser%c%co",135,198,135,198);
		printf("\nOp%c%co 2: Remo%c%co",135,198,135,198);
		printf("\nOp%c%co 3: Busca",135,198);
		printf("\nOp%c%co 4: Impress%co Pr%c Ordem",135,198,198,130);
		printf("\nOp%c%co 5: Impress%co Em Ordem",135,198,198);
		printf("\nOp%c%co 6: Impress%co P%cs Ordem",135,198,198,162);
		printf("\nOp%c%co 7: Impress%co Labelled Bracketing",135,198,198);
		
		printf("\nOp%c%co escolhida: ",135,198);
		int opcao;
		scanf("%d",&opcao);
		printf("\n");
		
		return(opcao);
	
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
		
		int j=1;	
		while(j==1){
			
			int opcao;
			opcao=menu();
			
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
				struct arvore *encontrado = search(raiz,chave);
				if(encontrado!=NULL){
					if(encontrado->key==chave){
						printf("\nO valor %d exite nessa %crvore\n",chave,160);
					}
				}
				else{
					printf("\nO valor buscado n%co existe nessa %crvore\n",198,160);
				}
			}
			
			if (opcao == 4){
				preordem(raiz);
				printf("\n");
			}
			
			if (opcao == 5){
				emordem(raiz);
				printf("\n");
			}
			
			if (opcao == 6){
				posordem(raiz);
				printf("\n");
			}
			
			if (opcao == 7){
				labelledbracketing(raiz);
				printf("\n");
			}
			
			printf("\n\nDeseja continuar no programa %c    1-SIM  2-N%cO\n",63,199);
			scanf("%d",&j);
		}
	printf("\nPROGRAMA ENCERRADO");
	}
getch();	
}


