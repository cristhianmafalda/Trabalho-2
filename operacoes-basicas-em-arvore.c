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
			novo = novo->dir;                   //valores maiores serão inseridos a direita
		}
		else {
			novo = novo->esq;                    //valores menores serão inseridos a direita
		}
	}

	struct arvore *valor = (struct arvore*)malloc(sizeof(struct arvore));  // alocamos a estrutura para esse novo valor
	valor->key = chave;                                                    //recebe o valor novo e NULL para os ponteiros
	valor->dir = NULL;
	valor->esq = NULL;

	if (origin->key>chave){						//compara valor com o pai para saber se valor é inserido no ponteiro da direita ou esquerda
		origin->esq=valor;
	}
	else {
		origin->dir=valor;
	}
}

struct arvore*search(struct arvore*no, int busca){      //funcao que recebe um valor e busca na arvore

	if(no==NULL){                                       //quando no for NULL, o valor não esta na arvore
		return(NULL);
	}
	if(busca == no->key){                               //quando o valor encontrado for a chave buscada, retorna a mesma
		return(no);
	}
	if(busca>no->key){                                  //se o valor buscado for maior que o no, procura-se na sua direita
		return(search(no->dir,busca));
	}
	if(busca<no->key){                                  //se o valor for menor, busca-se na esquerda
		return(search(no->esq,busca));
	}
}

void removechave(struct arvore*no, int chave){          //funcao que recebe um valor para ser removido da arvore

	struct arvore *p1 = no;     //precisamos das posicoes p1 e p2 para encontrar a chave e seu antecessor
	struct arvore *p2 = NULL;

	while(p1!=NULL && p1->key!=chave){
		p2=p1;                  //enquanto p1 não for a chave, p2 recebe p1
		if(chave>=p1->key){
			p1=p1->dir;         //p1 vai para a direita se fro maior
		}
		else {
			p1=p1->esq;         //p1 vai para a esquerda se for menor
		}
	}

	if(p1==NULL) {              //caso em que o valor nao esta na arvore
		return;
	}

	struct arvore*menormaior = p1->dir;                  //temos que encontrar o menor valor da arvore que seja maior que o que sera removido
	while(menormaior!=NULL && menormaior->esq!=NULL){    //esse valor será o ultimo ponteiro a esquerda do ponteiro da direita da chave
			menormaior = menormaior->esq;
	}

	struct arvore *temp;
    if(menormaior!=NULL){
        menormaior->esq = p1->esq;      //menormaior aponta para p1 da esquerda
        temp = p1->dir;                 //temp aponta para o p1 da direita
	}
	else {
        temp = p1->esq;                 //se maior menor não existir, temp aponta para o p1 da esquerda
    }
    if(chave>=p2->key) {                //se o pai da chave a ser removida for menor que a chave removida
        p2->dir = temp;                 //a direita dele aponta para temp
    }
	else {
        p2->esq = temp;                 //senão quem aponta é sua esquerda
    }
    free(p1); //agora que outros valores ja apontam corretamente para quem p1 apontava, e p2 não aponta mais para ela, podemos apagá-la
}

void removeraiz(struct arvore*raiz){                    //quando o valor removido for a raiz,precisamos de uma função diferente

	struct arvore*menormaior = raiz->dir;               //maiormenor encontrado do mesmo jeito da funcao removechave
	while(menormaior!=NULL && menormaior->esq!=NULL){
			menormaior = menormaior->esq;
	}

	struct arvore *novaraiz;                            //novaraiz é alocada
    if(menormaior!=NULL){
        menormaior->esq = raiz->esq;                    //menor maior aponta para a esquerda da raiz
        novaraiz = raiz->dir;                           //novaraiz
	}
	else {                                              //se for NULL, o maior menor, o primeiro valor a esquerda da raiz sera a novaraiz
        novaraiz = raiz->esq;
    }

    raiz->key = novaraiz->key;                          //mudamos as variaveis de raiz para ela receber a novaraiz e retornar para a arvore
    raiz->dir = novaraiz->dir;
    raiz->esq = novaraiz->esq;
}

void emordem(struct arvore*no){					// em ordem é uma função que imprime os valores da arvore de maneira ordenada
	if(no!=NULL){
		emordem(no->esq);						//busca os menores para imprimir
		printf("%d ",no->key);					//imprime o valor
		emordem(no->dir);						//segue para os maiores
	}
}

void preordem(struct arvore*no){				//função que imprime as chaves antes de visitar os filhos
	if(no!=NULL){
		printf("%d ",no->key);                  //imprime a chave
		preordem(no->esq);                      //busca nos valores menores
		preordem(no->dir);						//busca nos valores maiores
	}
}

void posordem(struct arvore*no){			    //função que imprime as chaves antes de visitar os filhos
	if(no!=NULL){
		posordem(no->esq);                      //busca nos valores menores
		posordem(no->dir);                      //busca nos valores maiores
		printf("%d ",no->key);					//imprime a chave
	}
}

void labelledbracketing(struct arvore*no){	    //função que imprime a arvore em labelled bracketing
	printf("[");                                //abre o no
	if(no!=NULL){                               //confere se o nó possui chave
		printf("%d",no->key);                   //imprime a chave
		labelledbracketing(no->esq);            //recursivo para os menores
		labelledbracketing(no->dir);		    //recursivo para os maiores
	}
	printf("]");                                //fecha o no
}

void apagatudo(struct arvore*no){               //funcao que libera toda a memoria alocada no programa
	if(no!=NULL){
		apagatudo(no->esq);                     //apaga os menores, se existirem
		apagatudo(no->dir);                     //apaga os maiores, se existirem
		free(no);								//apaga o no
	}
}

int menu(){ //funcao que abre o menu de opções e retorna a desejada

        //imprime todas as opções na tela
		printf("\nDigite o n%cmero da op%c%co que deseja realizar com sua %crvore:",163,135,198,160);
		printf("\nOp%c%co 1: Inser%c%co",135,198,135,198);
		printf("\nOp%c%co 2: Remo%c%co",135,198,135,198);
		printf("\nOp%c%co 3: Busca",135,198);
		printf("\nOp%c%co 4: Impress%co Pr%c Ordem",135,198,198,130);
		printf("\nOp%c%co 5: Impress%co Em Ordem",135,198,198);
		printf("\nOp%c%co 6: Impress%co P%cs Ordem",135,198,198,162);
		printf("\nOp%c%co 7: Impress%co Labelled Bracketing",135,198,198);
		printf("\nOp%c%co 8: Encerrar o Programa",135,198);
		printf("\n\nOp%c%co escolhida: ",135,198);

		int opcao;
		scanf("%d",&opcao); //le a opcao escolhida
		while(opcao<1||opcao>8){ //confere a coerencia e refaz se necessario
            printf("\n\nEscolha uma op%c%co existente",135,198);
            printf("\n\nOp%c%co escolhida: ",135,198);
            scanf("%d",&opcao);
		}
		printf("\n");
		return(opcao);    //retorna a opcao
}

void main () {

	printf("Digite a quantidade inicial de valores a ser digitado.\nEm seguida, insira os valores.\n\n");
	int n,i,chave;
	scanf("%d",&n); //le a quantidade inicial de valores da arvore

	while(n<=0){//confere a coerencia e refaz se necessario
        printf("\nA quantidade inicial deve ser um inteiro maior que zero\n\n");
        printf("Digite a quantidade inicial de valores a ser digitado.\nEm seguida, insira os valores.\n\n");
        scanf("%d",&n);
	}

	if(n>0){        //confere se o valor escolhido é coerente com o esperado
		struct arvore*raiz = (struct arvore*) malloc(sizeof(struct arvore)); //aloca a raiz
		scanf("%d",&chave); //o primeiro valor sera colocado como chave da raiz
		raiz->key = chave;
		raiz->dir = NULL;
		raiz->esq = NULL;

		for(i=1;i<n;i++){
			scanf("%d",&chave);     //os valores seguintes serão passados um a um para a funcao add, onde serão inseridos na arvore
			add(raiz,chave);
		}

		int j=1;
		while(j==1){        //j é a variavel que indica se o programa deve encerrar

			int opcao;
			opcao=menu();       //acha a opcao que a pessoa deseja

			if (opcao == 1){ //opção de inserção
				printf("Digite a quantidade de valores a ser inserido.\nEm seguida, insira os valores.\n\n");
				scanf("%d",&n); //le a quantidade de novos valores
				while(n<=0){
                    printf("\nA quantidade inicial deve ser um inteiro maior que zero\n\n");
                    printf("Digite a quantidade inicial de valores a ser digitado.\nEm seguida, insira os valores.\n\n");
                    scanf("%d",&n); //le a quantidade inicial de valores da arvore

                }
				if(n>0){ //verifica coerencia
					for(i=0;i<n;i++){
						scanf("%d",&chave);
						add(raiz,chave); //envia os novos valores para a add
					}
				}
				printf ("\n\nValor(es) inserido(s)\n");
			}

			if (opcao == 2){ //opção de remoção
				printf("\nDigite o valor a ser removido: ");
				scanf("%d",&chave); // le o valor a ser removido
				if(chave!=raiz->key){ //se o valor não e a raiz, envia ele para a removechave
					removechave(raiz,chave);
					printf ("\n\nValor removido\n");
				}
				else if (raiz->dir == NULL && raiz->esq == NULL){ //se o valor for a raiz, mas a arvore so possuir ela
					printf("\nTodos os valores foram removidos\nO programa deve ser reiniciado para continuar\n");
					j=2;
				}
				else{ //em ultimo caso, removeraiz é chamada para retirar a raiz da arvore
					removeraiz(raiz);
					printf ("\n\nValor removido\n");
				}
			}

			if (opcao == 3){ //opção de busca
				printf("\nDigite o valor buscado: ");
				scanf("%d",&chave); //le o valor buscado
				struct arvore *encontrado = search(raiz,chave); //recebe a funcao  de busca pelo valor
				if(encontrado!=NULL){ //se o valor retornado não for NULL
					if(encontrado->key==chave){ //confere se ele é a chave buscada
						printf("\nO valor %d existe nessa %crvore\n",chave,160);
					}
				}
				else{ // se a funcao retorna NULL, o valor nao esta na arvore
					printf("\nO valor buscado n%co existe nessa %crvore\n",198,160);
				}
			}

			if (opcao == 4){ //opção de impressão em preordem
				printf("\nImpress%co Pr%c Ordem: ",198,130);
				preordem(raiz); //chama a funcao de impressao
				printf("\n");
			}

			if (opcao == 5){ //opção de impressão emordem
				printf("\nImpress%co Em Ordem: ",198);
				emordem(raiz); //chama a funcao de impressao
				printf("\n");
			}

			if (opcao == 6){ //opção de impressão em posordem
				printf("\nImpress%co P%cs Ordem: ",198,162);
				posordem(raiz); //chama a funcao de impressao
				printf("\n");
			}

			if (opcao == 7){ //opção de impressão em labelled bracketing
				printf("\nImpress%co Labelled Bracketing: ",198);
				labelledbracketing(raiz); //chama a funcao de impressao
				printf("\n");
			}

			if (opcao == 8){ //opcao para sair do programa
				j=2;
			}

		printf("\n");
		}
		apagatudo(raiz);    //antes do programa acabar, apaga a arvore
	}
    printf("\nPROGRAMA ENCERRADO");
    getch();	            //pausa para leitura da tela
}
