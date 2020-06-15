typedef struct NO* ArvBin;

#include <stdio.h>
#include <stdlib.h>

struct NO{
	int info;
	struct NO *esq;
	struct NO *dir;
};

struct NO* remove_atual(struct NO* atual){
	struct NO *no1, *no2;
	if(atual->esq == NULL){ //Sem filho da esquerda. Apontar para o filho da direita
		no2 = atual->dir;   // (trata nó folha e nó com 1 filho)
		free(atual);
		return no2;
	}
	no1 = atual;			//Procura filho mais a direita na sub-arvore da esquerda
	no2 = atual->esq;
	while(no2->dir != NULL){
		no1 = no2;
		no2 = no2->dir;
	}
	if(no1 != atual){		// Copia o filho mais a direita na sub-arvore esquerda para o lugar
		no1->dir = no2->esq;// do no removido
		no2->esq = atual->esq;
	}
	no2->dir = atual->dir;
	free(atual);
	return no2;
}

ArvBin* cria_ArvBin();

void libera_ArvBin(ArvBin *raiz);
int estaVazia_ArvBin(ArvBin *raiz);
int altura_ArvBin(ArvBin *raiz);
void preOrdem_ArvBin(ArvBin *raiz);
int insere_ArvBin(ArvBin *raiz, int valor);
int remove_ArvBin(ArvBin *raiz, int valor);
int consulta_ArvBin(ArvBin *raiz, int valor);

ArvBin* cria_ArvBin(){
	ArvBin* raiz = (ArvBin*) malloc(sizeof(ArvBin));
	if(raiz != NULL)
		*raiz=NULL;
	return raiz;
}

void libera_NO(struct NO* no) {
	if(no==NULL)
		return;
	libera_NO(no->esq);
	libera_NO(no->dir);
	free(no);
	no = NULL;
}

void libera_ArvBin(ArvBin* raiz) {
	if(raiz == NULL)
		return;
	libera_NO(*raiz);
	free(raiz);
}

int estaVazia_ArvBin(ArvBin *raiz) {		//se retorna 1 esta vazia
	if(raiz == NULL)
		return 1;
	if(*raiz == NULL)
		return 1;
	return 0;
}

int altura_ArvBin(ArvBin *raiz) {		// a altura é calculada com basse no nó mais longe da raiz
	if(raiz == NULL);
		return 0;
	if(*raiz == NULL)
		return 0;
	int alt_esq = altura_ArvBin(&((*raiz)->esq));
	int alt_dir = altura_ArvBin(&((*raiz)->dir));
	if(alt_esq > alt_dir)
		return (alt_esq + 1);
	else
		return (alt_dir + 1);
}

void preOrdem_ArvBin(ArvBin *raiz){
	if (raiz == NULL)
		return;
	if(*raiz !=NULL){
		printf("%d", (*raiz)->info);
		printf("(");
		preOrdem_ArvBin(&((*raiz)->esq));
		preOrdem_ArvBin(&((*raiz)->dir));
		printf(")");
	}
}

int insere_ArvBin(ArvBin* raiz, int valor){
	if(raiz == NULL)
		return 0;
	struct NO* novo;
	novo = (struct NO*) malloc(sizeof(struct NO));
	if(novo == NULL)
		return 0;
	novo->info = valor;
	novo->dir = NULL;
	novo->esq = NULL;
	//procurar onde inserir
	if(*raiz == NULL)
		*raiz = novo;
	else{
		struct NO* atual = *raiz;
		struct NO* ant = NULL;
		while(atual != NULL){	//navegaçao pela arvore
			ant = atual;
			if(valor == atual->info){
				free(novo);
				return 0;
			}
			if(valor > atual->info)
				atual = atual->dir;
			else
				atual = atual->esq;
		}
		if(valor > ant->info) //processo de inserçao
			ant->dir = novo;
		else
			ant->esq = novo;
		}
		return 1;
}

int remove_ArvBin(ArvBin *raiz, int valor){
	if(raiz == NULL) return 0;
	struct NO* ant = NULL;
	struct NO* atual = *raiz;
	while(atual != NULL){
		if(valor == atual->info){  //achou o no a ser removido. tratar o lado da remoçao
			if(atual == *raiz)
				*raiz = remove_atual(atual);
			else{
				if(ant->dir == atual)
					ant->dir = remove_atual(atual);
				else
					ant->esq = remove_atual(atual);
			}
			return 1;
		}
		ant = atual; // continua andando na arvore a procura do no pra remover
		if(valor > atual->info)
			atual = atual->dir;
		else
			atual = atual->esq;
	}
	return 0;
}

int  consulta_ArvBin(ArvBin *raiz, int valor){ //se achar retorna 1
	if(raiz == NULL)
		return 0;
	struct NO* atual = *raiz;
	while(atual != NULL) {
		if(valor == atual->info) {
			return 1;
		}
		if(valor > atual->info)
			atual = atual->dir;
		else
			atual = atual->esq;
	}
	return 0;
}


int main(){
	int valor, resp, x;
	ArvBin* raiz = cria_ArvBin(); //montagem da arvore
	
	do{
		printf("\n-----Arvore Binaria------\n");
		printf("1) Inserir novo valor\n");
		printf("2) Remover valor\n");
		printf("3) Procurar valor\n");	
		printf("4) Mostrar arvore\n");
		printf("5) Mostrar altura da arvore\n");
		printf("6) Validar se a arvore esta vazia\n");
		printf("7) Excluir arvore inteira\n");
		printf("8) Sair do programa\n");
		scanf("%d", &resp);
	
		switch(resp){
			case 1:
				printf("Qual o valor a ser inserido?\n");
				scanf("%d", &valor);
				x = insere_ArvBin(raiz,valor); //inserir valor na arvore
				break;
			case 2:
				printf("Qual o valor a ser removido?\n");
				scanf("%d", &valor);
				x = remove_ArvBin(raiz, valor); //remover valor
				if(x=1)
					printf("Valor encontrado e removido\n");
				else
					printf("Valor nao encontrado\n");
				break;
			case 3:
				printf("Qual o valor a ser procurado?\n");
				scanf("%d", &valor);
				x = consulta_ArvBin(raiz, valor); //procurar valor
				if(x==1)
					printf("Valor encontrado\n");
				else
					printf("Valor nao encontrado\n");
				break;
			case 4:
				printf("Status atual da arvore:\n");
				preOrdem_ArvBin(raiz);
				break;
			case 5:
				printf("A altura da arvore e:\n");
				x = altura_ArvBin(raiz);
				printf("%d\n", x);
				break;
			case 6:
				if(estaVazia_ArvBin(raiz))
					printf("A arvore esta vazia\n");
				else
					printf("A arvore nao esta vazia\n");
				break;
			case 7:
				libera_ArvBin(raiz); //chamada da funçao p liberar arvore inteira
				printf("A arvore foi totalmente removida\n");
				break;
			default:
				printf("Opção Invalida\n");
		}
	}while(resp != 8);
	
	return 0;
}
