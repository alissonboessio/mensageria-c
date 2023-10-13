#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct emissor{
	int id;
	char nome[20];
	struct emissor *proxE, *antE;
	
};
typedef struct emissor Emissor;


void printMenu(){
	printf("\n1 -> Incluir Emissor\n");
	printf("2 -> Remover Emissor\n");
	printf("3 -> Consultar Emissores\n");
	printf("4 -> Incluir Receptor\n");
	printf("5 -> Remover Receptor\n");
	printf("6 -> Consultar Receptores\n");
	printf("7 -> Enviar Mensagem\n");
	printf("8 -> Retirar Mensagem\n");
	printf("9 -> Consultar Fila de Mensagens\n");
	printf("0 -> Sair\n\n");
	printf("Escolha: ");
}
void incluirEmissor(int id, char nome[], Emissor **inicioE) {
    Emissor *novoE;
    novoE = (Emissor*)malloc(sizeof(Emissor));
    novoE->id = id;
    strcpy(novoE->nome, nome);
    novoE->proxE = NULL;
    novoE->antE = NULL;

    if (*inicioE == NULL || id < (*inicioE)->id) { // insere no inicio
        novoE->proxE = *inicioE;
        if (*inicioE != NULL) {
            (*inicioE)->antE = novoE;
        }
        *inicioE = novoE;
        return;
    }

    Emissor *aux = *inicioE;
    while (aux->proxE != NULL && aux->proxE->id <= id) {
        if (aux->proxE->id == id) { // se o id ja existir n insere
            free(novoE);
            return;
        }
        aux = aux->proxE;
    }
	// insere no 'meio'
    novoE->proxE = aux->proxE;
    novoE->antE = aux;
    if (aux->proxE != NULL) {
        aux->proxE->antE = novoE;
    }
    aux->proxE = novoE;
}

void removeEmissor(int id, Emissor **inicioE) {
    Emissor *aux = *inicioE;

    while (aux != NULL) {
        if (aux->id == id) {
            if (aux->antE != NULL) {
                (aux->antE)->proxE = aux->proxE;
                if (aux->proxE != NULL) {
                    (aux->proxE)->antE = aux->antE;
                }
            } else {
                *inicioE = aux->proxE; // se for o primeiro da lista sendo removido
                if(*inicioE != NULL){ // se for o unico sendo remo
                	(*inicioE)->antE = NULL;
				}
                
            }
            free(aux);
            return;
        }
        aux = aux->proxE;
    }
}

void consultarEmissores(Emissor **inicioE){
	Emissor *aux = *inicioE;

	printf("\nEmissores: ");

	while(aux != NULL){
		printf("\nid: %d -> %s", aux->id, aux->nome);
		aux = aux->proxE;
	}
	printf("\n");
}

int main(){
	Emissor *inicioEmissores;
	inicioEmissores = NULL;	
	
	int opc = 0;
	
	do{
		printMenu();
		scanf("%d", &opc);
		
		switch (opc){
			case 1:
				int idI;
				char nome[20];
				printf("id: ");
				scanf("%d", &idI);
				getchar();
				printf("nome: ");
				gets(nome);
				incluirEmissor(idI, nome, &inicioEmissores);
				break;
			case 2:
				int idE;
				printf("id: ");
				scanf("%d", &idE);
				removeEmissor(idE, &inicioEmissores);
				break;
			case 3:
				consultarEmissores(&inicioEmissores);
				break;
				
			
		}
		
	}while(opc != 0);
}


