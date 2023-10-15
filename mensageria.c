#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct fila{ // (fila individual)
	int idEmissor;
	char mensagem[50];
	struct fila *proxM;
};
typedef struct fila Fila;

struct emissor{ // (lista de emissores de mensagem)
	int id;
	char nome[20];
	struct emissor *proxE, *antE;
	
};
typedef struct emissor Emissor;

struct receptor{ // (lista dos receptores de mensagem {cada receptor contem uma fila de mensagens} - é a fila de mensagens)
	int id;
	char nome[20];
	struct receptor *proxR, *antR;
	struct fila *inicioFila;
};
typedef struct receptor Receptor;

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

void incluirReceptor(int id, char nome[], Receptor **inicioR){
	Receptor *novoR;
    novoR = (Receptor*)malloc(sizeof(Receptor));
    novoR->id = id;
    strcpy(novoR->nome, nome);
    novoR->proxR = NULL;
    novoR->antR = NULL;
    
    //novoR->inicioFila = (Fila*)malloc(sizeof(Fila));
    novoR->inicioFila = NULL;

    if (*inicioR == NULL || id < (*inicioR)->id) { // insere no inicio
        novoR->proxR = *inicioR;
        if (*inicioR != NULL) {
            (*inicioR)->antR = novoR;
        }
        *inicioR = novoR;
        return;
    }

    Receptor *aux = *inicioR;
    while (aux->proxR != NULL && aux->proxR->id <= id) {
        if (aux->proxR->id == id) { // se o id ja existir n insere
            free(novoR);
            return;
        }
        aux = aux->proxR;
    }
	// insere no 'meio'
    novoR->proxR = aux->proxR;
    novoR->antR = aux;
    if (aux->proxR != NULL) {
        aux->proxR->antR = novoR;
    }
    aux->proxR = novoR;
}

void removeReceptor(int id, Receptor **inicioR){
	Receptor *aux = *inicioR;
	
    while (aux != NULL) {
        if (aux->id == id) {
            if (aux->antR != NULL) {
                (aux->antR)->proxR = aux->proxR;
                if (aux->proxR != NULL) {
                    (aux->proxR)->antR = aux->antR;
                }
            } else {
                *inicioR = aux->proxR; // se for o primeiro da lista sendo removido
                if(*inicioR != NULL){ // se for o unico sendo removido
                	(*inicioR)->antR = NULL;
				}
                
            }
            free(aux);
            return;
        }
        aux = aux->proxR;
    }
}

void consultaReceptores(Receptor **inicioR){
	Receptor *aux = *inicioR;

	printf("\nReceptores: ");

	while(aux != NULL){
		printf("\nid: %d -> %s", aux->id, aux->nome);
		aux = aux->proxR;
	}
	printf("\n");
}

void enviarMensagem(int idEmissor, int idReceptor, char mensagem[], Receptor **inicioR) {
    Receptor *aux = *inicioR;

    while (aux != NULL) {
        if (aux->id == idReceptor) {
            Fila *novaMensagem = (Fila*)malloc(sizeof(Fila));
            novaMensagem->idEmissor = idEmissor;
            strcpy(novaMensagem->mensagem, mensagem);
            novaMensagem->proxM = NULL;

            if (aux->inicioFila == NULL) {
                aux->inicioFila = novaMensagem;
            } else {
                Fila *temp = aux->inicioFila;
                while (temp->proxM != NULL) {
                    temp = temp->proxM;
                }
                temp->proxM = novaMensagem;
            }
            printf("Mensagem enviada com sucesso para o receptor %d.\n", idReceptor);
            return;
        }
        aux = aux->proxR;
    }
    printf("Erro: Receptor não encontrado.\n");
}


void retirarMensagem(int idReceptor, Receptor **inicioR) {
    Receptor *aux = *inicioR;

    while (aux != NULL) {
        if (aux->id == idReceptor) {
            if (aux->inicioFila == NULL) {
                printf("Erro: Fila de mensagens está vazia para o receptor %d.\n", idReceptor);
            } else {
                Fila *mensagemRetirada = aux->inicioFila;
                aux->inicioFila = mensagemRetirada->proxM;
                printf("Mensagem retirada: %s\n", mensagemRetirada->mensagem);
                free(mensagemRetirada);
            }
            return;
        }
        aux = aux->proxR;
    }
    printf("Erro: Receptor não encontrado.\n");
}

void consultarFilaMensagens(int idReceptor, Receptor **inicioR) {
    Receptor *aux = *inicioR;

    while (aux != NULL) {
        if (aux->id == idReceptor) {
            Fila *mensagemAtual = aux->inicioFila;
            
            printf("Fila de mensagens para o receptor %d:\n", idReceptor);
            while (mensagemAtual != NULL) {
                printf("Emissor %d: %s\n", mensagemAtual->idEmissor, mensagemAtual->mensagem);
                mensagemAtual = mensagemAtual->proxM;
            }
            return;
        }
        aux = aux->proxR;
    }
    printf("Erro: Receptor não encontrado.\n");
}



int main(){
	Emissor *inicioEmissores;
	inicioEmissores = NULL;	
	
	Receptor *inicioReceptores;
	inicioReceptores = NULL;
	
	int opc = 0;
	
	do{
		printMenu();
		scanf("%d", &opc);
		
		switch (opc){
			case 1: ;
				int idIE;
				char nomeE[20];
				printf("id: ");
				scanf("%d", &idIE);
				getchar();
				printf("nome: ");
				gets(nomeE);
				incluirEmissor(idIE, nomeE, &inicioEmissores);
				break;
			case 2: ;
				int idDE;
				printf("id: ");
				scanf("%d", &idDE);
				removeEmissor(idDE, &inicioEmissores);
				break;
			case 3: ;
				consultarEmissores(&inicioEmissores);
				break;
			case 4: ;
				int idIR;
				char nomeR[20];
				printf("id: ");
				scanf("%d", &idIR);
				getchar();
				printf("nome: ");
				gets(nomeR);
				incluirReceptor(idIR, nomeR, &inicioReceptores);
				break;
			case 5: ;
				int idDR;
				printf("id: ");
				scanf("%d", &idDR);
				removeReceptor(idDR, &inicioReceptores);
				break;
			case 6: ;
				consultaReceptores(&inicioReceptores);
				break;
			case 7: ;
			    int idEmissor, idReceptor;
			    char mensagem[50];
			    printf("ID do emissor: ");
			    scanf("%d", &idEmissor);
			    printf("ID do receptor: ");
			    scanf("%d", &idReceptor);
			    getchar();
			    printf("Mensagem: ");
			    fgets(mensagem, sizeof(mensagem), stdin);
			    enviarMensagem(idEmissor, idReceptor, mensagem, &inicioReceptores);
			    break;
			case 8: ;
			    //int idReceptor;
			    printf("ID do receptor: ");
			    scanf("%d", &idReceptor);
			    retirarMensagem(idReceptor, &inicioReceptores);
			    break;
			case 9: ;
			    int idConsulta;
			    printf("ID do receptor para consultar a fila de mensagens: ");
			    scanf("%d", &idConsulta);
			    consultarFilaMensagens(idConsulta, &inicioReceptores);
			    break;

		}
		
	}while(opc != 0);
}
