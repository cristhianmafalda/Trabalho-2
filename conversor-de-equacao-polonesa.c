#include<stdio.h>
#include<stdlib.h>

struct simbolo                      //simbolo é uma estrutura para as duas listas encadeadas do programa
	{
		char caractere;             // caractere armazena a info de cada um da lista
		struct simbolo * prox;      //prox é o endereço para o proximo da lista
	};

struct arvore                       //arvore é a estrutura para formar a arvore unindo as listas encadeadas
	{
		char caractere;
		struct arvore * dir;
		struct arvore * esq;
	};

void addsimbolo(struct simbolo*inicial, char caractere){    //addsimbolo adiciona operadores na lista de operadores

	if(inicial->prox==NULL){                                //condicao para posicionar o operador
		struct simbolo*novo = (struct simbolo*)malloc(sizeof(struct simbolo));
		novo->caractere = caractere;                        //aloca memoria, coloca a info dele e aterra o ponteiro para o prox
		novo->prox = NULL;
		inicial->prox = novo;                               //faz o ponteiro do anterior apontar para o novo operador
	}

	else{
		addsimbolo(inicial->prox, caractere);
	}

}

struct simbolo * addnumero(struct simbolo*seguinte, char valor){    //addnuumero forma uma lista encadeada de inteiros revertendo sua ordem

	struct simbolo*novo = (struct simbolo*)malloc(sizeof(struct simbolo));
	novo->caractere = valor;                                        //aloca memoria, e recebe a info
	novo->prox = seguinte;                                          //o novo aponta para o anterior
	return(novo);

}

void fazerarvore(struct arvore*raiz, struct simbolo*operador, struct simbolo*numero){
                                            //aqui reunimos as listas formando uma arvore
	if(operador==NULL || numero==NULL){     //quando as listas encerram essa condição impede a recursão
		return;
	}
                                            //tomando o ultimo inteiro como referencia, o operador fica a esquerda e o numero a direita
    struct arvore*esquerda = (struct arvore*)malloc(sizeof(struct arvore));
	esquerda->caractere = operador->caractere;
	esquerda->dir = NULL;                   //memoria alocada, info colocada, o operador sempre ficará com os ponteiros aterrados
	esquerda->esq = NULL;
	struct arvore*direita = (struct arvore*)malloc(sizeof(struct arvore));
	direita->caractere = numero->caractere;
	direita->dir = NULL;                    //memoria alocada, info colocada, o valor aterra inicialmente seus ponteiros
	direita->esq = NULL;

	raiz->esq = esquerda;                   //aqui a raiz atual aponta para o novo operador e o novo numero
	raiz->dir = direita;

	fazerarvore(direita,operador->prox,numero->prox);     //o novo numero se torna a raiz que ira receber o prox operador e numero
}

void rpn(struct arvore*no){ //função que imprime a equação em RPN
	if(no!=NULL){
		rpn(no->dir);       //percorre os numeros
		printf(" %c",no->caractere); //imprime a raiz
		rpn(no->esq);       //imprime o operador entre o numero e a raiz
	}
}

void imprime(struct arvore*no){ //imprime é uma função que recebe um endereço e imprime seu caractere
	printf(" %c",no->caractere);
}

void infixa(struct arvore*no){      //infixa imprime a equação em notação infixa
    if(no->dir==NULL &&no->esq==NULL){
        imprime(no);                //essa condição existe para que o primeiro valor da infixa não suma
    }
	if(no->dir!=NULL){              //condição para os demais valores
		printf(" (");               //abre o parenteses
		infixa(no->dir);            //percorre os numeros
		imprime(no->esq);           //imprime o operador
		imprime(no);                //imprime a raiz atual
		printf(" )");               //fecha parentes e retorna de maneira recursiva
	}
}

void apagatudo(struct arvore*no){               //funcao que libera toda a memoria alocada no programa
	if(no!=NULL){
		apagatudo(no->esq);                     //apaga os operadores
		apagatudo(no->dir);                     //apaga os numeros
		free(no);								//apaga o no
	}
}

void apagalista(struct simbolo*no){             //funcao que libera o espaço alocado para listas
    if(no!=NULL){
		apagalista(no->prox);                   //apaga os seguintes
		free(no);								//apaga o no
	}
}

void main () {

	printf("Digite a equacao\n\n");

	char c;
	int i=0,j=1;

	scanf("%c",&c); //le o caractere inicial

	struct simbolo*firstc = (struct simbolo*)malloc(sizeof(struct simbolo));    //aloca espaço para o primeiro da lista
	firstc->caractere = c;
	firstc->prox = NULL;

	while(i==0){

		scanf("%c",&c); //le os operadores seguintes

		if(c=='+'||c=='-'||c=='/'||c=='*'||c==' '){ //condição para ser operador
			if(c=='+'||c=='-'||c=='/'||c=='*'){
				addsimbolo(firstc,c);               //adiciona o operador na lista
				j++;
			}
		}
		else{
			i=1;
		}

	}

	struct simbolo*firstn = (struct simbolo*)malloc(sizeof(struct simbolo));    //aloca espaço para o primeiro da lista de numeros
	firstn->caractere = c;
	firstn->prox = NULL;


	for (i=0;i<j;i++){
		scanf("%c",&c);     //le os numeros como char, logo eles estão presos ao intervalo 0-9
		if(c!=' '){
            firstn = addnumero(firstn,c); //coloca eles na lista encadeada invertendo a ordem
		}
		else {
            i--;
		}
	}

	struct arvore*raiz = (struct arvore*)malloc(sizeof(struct arvore));         //aloca espaço para a raiz da arvore
	raiz->caractere = firstn->caractere;                                        //o ultimo numero fica na raiz
	raiz->esq = NULL;
	raiz->dir = NULL;

	fazerarvore(raiz,firstc,firstn->prox);                                      //fazemos a arvore unindo as listas

    printf("\n\nRPN:");                                                         //imprime na função rpn
    rpn(raiz);

    printf("\n\nInfixa:");                                                      //imprime em notação infixa
    infixa(raiz);

    apagalista(firstn);                                                         //libera a lista de numeros
    apagalista(firstc);                                                         //libera a lista de caracteres
    apagatudo(raiz);                                                            //libera o espaço da arvore

    printf("\n\n");
    getch();                                                                    //aguarda a leitura
}
