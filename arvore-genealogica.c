#include<stdio.h>
#include<stdlib.h>
#include <string.h>

struct pessoa  //definindo a estrutura da arvore
{
	int chave; //chave será o valor associado a cada membro da arvore
	int geracao; //geracao é o inteiro que conta geracões de maneira crescente a partir do primeiro nome
	struct pessoa * esq;
	struct pessoa * dir;
};

struct pessoa*buscado; //buscado é uma variavel global para localizar nomes

struct pessoa*buscado2; //buscado2 é uma variavel global para localizar nomes

int maxgen; //maxgen é a maior geração existente nessa arvore

void localiza(struct pessoa*no, int chave){ //função que coloca o nome desejado na variavel buscado

    if(no!=NULL){
		localiza(no->esq,chave); //como nao temos ordem, devemos buscar em toda a arvore
		localiza(no->dir,chave);
		if(chave==no->chave){
            buscado=no;          //faz buscado receber o nome desejado
		}
	}
}

void localiza2(struct pessoa*no, int chave){ //totalmente analoga a função localiza, porém para a variavel buscado2

    if(no!=NULL){
		localiza2(no->esq,chave);
		localiza2(no->dir,chave);
		if(chave==no->chave){
            buscado2=no;
		}
	}
}

void labelledbracketing(struct pessoa*arvore,char nome[][50]){ //função que imprime a arvore em labelled bracketing
	if(arvore!=NULL){ // as chaves só aparecem quando o nó não for nulo
        printf("[");
	}
	if(arvore!=NULL){
		printf("%s",nome[arvore->chave]);       //imprime o nome
		labelledbracketing(arvore->esq,nome);   //confere a esquerda
		labelledbracketing(arvore->dir,nome);   //confere a direita
	}
	if(arvore!=NULL){
        printf("]");
	}
}

void preenchergeracao(struct pessoa*no,int geracao){ //funcao que coloca geração em todos as pessoas

    if(no!=NULL){
        no->geracao=geracao;
        if(geracao>maxgen){     //localiza o maxgen
            maxgen = geracao;
        }
        preenchergeracao(no->esq,geracao+1); //cada vez que  mudamos de geração, aumenta-se 1 na geração de maneira recursiva
        preenchergeracao(no->dir,geracao+1);
    }
}

void imprimegen(struct pessoa*no, int gen,char nome[][50]){ //função que imprime todos os membros por geração que recebe

    if(no!=NULL){
        imprimegen(no->esq,gen,nome);                       //a recursão propaga a função para os pais das pessoas
        if(no->geracao==gen){                               //quando o nome tiver geração igual a esperada, ele é impressso
            printf("%s ",nome[no->chave]);
        }
        imprimegen(no->dir,gen,nome);
    }
}

int menu(){ //funcao que abre o menu de opções e retorna a desejada

        //imprime todas as opções na tela
		printf("\nDigite o n%cmero da op%c%co que deseja realizar com sua %crvore geneal%cgica:",163,135,198,160,162);
		printf("\nOp%c%co 1: Impress%co dos Membros por Gera%c%co",135,198,198,135,198);
		printf("\nOp%c%co 2: Impress%co dos Antepassados de uma Pessoa",135,198,198);
		printf("\nOp%c%co 3: Impress%co Labelled Bracketing",135,198,198);
        printf("\nOp%c%co 4: C%clculo do Grau de Parentesco",135,198,160);
        printf("\nOp%c%co 5: Encerrar o Programa",135,198);

		printf("\n\nOp%c%co escolhida: ",135,198);
		int opcao;
		scanf("%d",&opcao);
		while(opcao<1||opcao>5){ //confere a coerencia e refaz se necessario
            printf("\n\nEscolha uma op%c%co existente",135,198);
            printf("\n\nOp%c%co escolhida: ",135,198);
            scanf("%d",&opcao);
		}
		printf("\n"); //retorna a opcao
		return(opcao);
}

void apagatudo(struct pessoa*no){               //funcao que libera toda a memoria alocada no programa
	if(no!=NULL){
		apagatudo(no->esq);                     //apaga os menores, se existirem
		apagatudo(no->dir);                     //apaga os maiores, se existirem
		free(no);								//apaga o no
	}
}

void main () {

	printf("Digite a quantidade inicial de conjuntos(filho/pai/m%ce) a serem digitado\nEm seguida, digite os conjuntos\n\n",198);
	int n,i,k=-1,j=-1;

	scanf("%d",&n);                 //le a quantidade inicial de valores da arvore
	while(n<=0){                    //confere a coerencia e refaz se necessario
        printf("\nA quantidade inicial deve ser um inteiro maior que zero\n\n");
        printf("Digite a quantidade inicial de conjuntos(filho/pai/m%ce) a serem digitado\nEm seguida, digite os conjuntos\n\n",198);
        scanf("%d",&n);             //le a quantidade inicial de valores da arvore
	}

    char nome[3*n][50];             //nome é uma matriz composta pelos nomes das pessoas

	for (i=0; i<3*n; i++) {         //leitura dos nomes
		scanf("%s",nome[i]);
	}

	struct pessoa *raiz = (struct pessoa*)malloc(sizeof(struct pessoa));
	raiz->chave = 0;
	raiz->dir = NULL;               //declaracao da raiz
	raiz->esq = NULL;

    for(i=0;i<3*n;i=i+3){           //nessa parte, iremos pegar os nomes da lista e fazer uma arvore
                                    //a variação de i em 3 serve para pegar o primeiro de cada trio
        k=-1;
        for (j=0;j<3*n;j++){        //agora iremos localizar a chave dessa pessoa
            if(strcmp(nome[i],nome[j])==0){ //a comparaco é feita por essa função da biblioteca string
                k=j;
                j=3*n;
            }
        }

            buscado = NULL;         //reinicia buscado , aloca espaço para o novo nome na arvore
            struct pessoa *novo = (struct pessoa*)malloc(sizeof(struct pessoa));
            localiza(raiz,k);       //faz buscado receber o nome para adicionar
            novo = buscado;         //aloca espaço para o pai e a mãe
            struct pessoa *pai = (struct pessoa*)malloc(sizeof(struct pessoa));
            struct pessoa *mae = (struct pessoa*)malloc(sizeof(struct pessoa));
            novo->esq = pai;        //os ponteiros do filho recebem seus pais
            novo->dir = mae;
            pai->chave = i+1;       //pai é o segundo elemento do trio
            pai->dir = NULL;        //pais do novo apontam para NULL
            pai->esq = NULL;
            mae->chave = i+2;       //mãe é o terceiro elemento do trio
            mae->esq = NULL;        //pais do novo apontam para NULL
            mae->dir = NULL;

    }

    maxgen = 0;                     //inicializa maxgen com zero
    preenchergeracao(raiz,0);       //coma arvore feita, podemos preenche-la com as geraçãoes

    int opcao,pos1,pos2,grau=0,fim = 1; //variaveis utilizadas nas funões abaixo
    char antepassado[50],p1[50],p2[50];

    while(fim==1){                  //opcao para imprimir todas as gerações

        opcao = menu();             //chama o menu

        if(opcao==1){
            for(i=0;i<=maxgen;i++){
                printf("\n");       //pula linha por geração
                imprimegen(raiz,i,nome); //imprime todos da geração
            }
        }

        if(opcao==2){               //opção para imprimir antepassados de alguém
            printf("\nDigite a pessoa de quem deseja ver os antepassados:  ");
            scanf("%s",antepassado);    //antepassado é o nome de quem se deseja imprimir os antepassados
            printf("\n");
            k=-1;                   //k é um contador usado para verificar se houve alterações nas variaveis de varias opções
            for (j=0;j<3*n;j++){    //localiza a chave de antepassado
                if(strcmp(antepassado,nome[j])==0){
                k=j;
                j=3*n;
                }
            }
            if(k!=-1){
                buscado = NULL;     //reinicia buscado
                localiza(raiz,k);   //faz buscado receber quem se procura
                for(i=buscado->geracao+1;i<=maxgen;i++){ //o acrescimo de 1 evita imprimir o nome da pessoa buscada
                    imprimegen(buscado,i,nome);          //imprime os antepassados do antepassado
                }
            }
            printf("\n");
        }

        if(opcao==3){               //opção para imprimir em labelled bracketing
            printf("\nLabelled Bracketing:  ");
            labelledbracketing(raiz,nome);
        }

        if(opcao==4){               //opção para verificar grau de parentesco
            grau=0;
            printf("\n\nDigite as pessoas para analisar o grau de parentesco:  ");
            scanf("%s %s",p1,p2);   //p1 e p2 são as 2 pessoas comparadas
            pos1=1;
            for (j=0;j<3*n;j++){    //localiza a chave de p1
                if(strcmp(p1,nome[j])==0){
                pos1=j;
                j=3*n;
                }
            }
            pos2=-1;
            for (j=0;j<3*n;j++){    //localiza a chave de p2
                if(strcmp(p2,nome[j])==0){
                pos2=j;
                j=3*n;
                }
            }
            buscado = NULL;         //reinicia buscado e buscado2
            buscado2 = NULL;
            localiza(raiz,pos1);    //localiza-se p1 na arvore desde a raiz
            localiza2(buscado,pos2);    //tenta-se localizar p2 dentro da arvore com raiz p1
            if(buscado2!=NULL){     //se p2 for localizado dentro da arvore de p1, a dirfença entre as gerações será o grau
                grau = buscado2->geracao - buscado->geracao;
            }
            else{                   //se p1 não for encontrado na arvore de p1, tentamos encontrar p1 na arvore de p2
                buscado = NULL;     //reinicia buscado e buscado2
                buscado2 = NULL;
                localiza(raiz,pos2);    //localiza-se p2 em relação a raiz
                localiza2(buscado,pos1);    //tenta localizar p1 na arvore de p2
                if(buscado2!=NULL){     //não sendo NULL, o graa é a diferença de gerações
                    grau = buscado2->geracao - buscado->geracao;
                }
            }
            printf("\n\nentre %s e %s grau de parentesco %d",p1,p2,grau);  //imprime o grau de parentesco
        }

        if(opcao==5){               //opção para encerrar o programa
				fim=2;
			}

        printf("\n");
    }

    apagatudo(raiz);                //chama a função que limpa a arvore
    printf("\nPROGRAMA ENCERRADO");
    getch();                        //encerra o programa e aguarda por um caractere

}
