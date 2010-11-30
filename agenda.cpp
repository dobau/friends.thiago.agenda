//---------------------------------------------------------------------------
#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#pragma hdrstop

//---------------------------------------------------------------------------
/* PARA A UTILIZAÇÃO DO PONTEIRO EU TENHO QUE INDICALO NO PARAMETRO DA FUNÇÃO */
typedef struct Agenda {
	char nome[50];
	char fone[17];
} T_agenda;

T_agenda agenda[50];

int total = 0;

bool jahExiste(char *nome) {
    for (int i= 0; i < total; i++) {
        if (strcmp(agenda[i].nome, nome) == 0) {
            return true;
        }
    }

    return false;
}

void inclusao(void) {
	getchar();
	char nomeTmp[50];
	printf("Nome: ");
	gets(nomeTmp);
	for (int j=0; j < strlen(nomeTmp); j++) {
		nomeTmp[j] = toupper(nomeTmp[j]);
	}

	if (jahExiste(nomeTmp)) {
		printf("CONTATO JA EXISTENTE!");
		getchar();
	} else {
		strcpy(agenda[total].nome, nomeTmp);
		printf("Telefone: ");
		gets(agenda[total].fone);
		total++;
	}
}

void ordenar(void) {
	T_agenda temp;
	for (int i=0; i < total; i++) {
		for (int j= (i + 1); j < total; j++){
			if (strcmp(agenda[i].nome, agenda[j].nome) > 0) {
				temp = agenda[j];
				agenda[j] = agenda[i];
				agenda[i] = temp;
			}
		}
	}
}

/**
 * Retorna a posição do contato na agenda, caso nada seja encontrado retorna -1;
 */
int pesquisar(void) {
	char pesq[20];
	getchar();
	system("cls");
	printf("Entre com o nome que deseja pesquisar: ");
	gets(pesq);
	for(int j=0;j<strlen(pesq);j++){
		pesq[j]=toupper(pesq[j]);
	}

	for (int i= 0; i < total; i++) {
		if (strcmp(agenda[i].nome, pesq) == 0) {
			printf("Fone: %s", agenda[i].fone);
			getch();
			return i;
		}
	}

	// Caso não tenha encontrado nenhum registro mostra a mensagem e retorna -1
	printf("\nNOME NAO CADASTRADO!");
	getch();
	return -1;
}


void alterar(void) {
    int index = pesquisar();
    if (index == -1) {
       return;
    }

    char op;
    do {
        system("cls");
        printf("Escolha o que deseja alterar:\n");
        printf("(1) Nome\n");
        printf("(2) Telefone\n");
        printf("(0) Voltar\n");
        scanf("%c", &op);
        switch(op) {
            case '1':
                getchar();
                char nomeTmp[50];
                printf("Nome: ");
                gets(nomeTmp);
                for (int j=0; j < strlen(nomeTmp); j++) {
					nomeTmp[j] = toupper(nomeTmp[j]);
                }
                 
                if (jahExiste(nomeTmp)) {
					printf("CONTATO JA EXISTENTE!");
					getchar();
                } else {
					strcpy(agenda[index].nome, nomeTmp);
                }
                 
                 break;
            case '2':
				getchar();
				printf("Telefone: ");
				gets(agenda[index].fone);
				break;
        }
    } while (op != '0');
}

/**
 * Lista todos os contatos da agenda.
 */
void listarTodos(void) {
	for (int i = 0; i < total; i++) {
		printf("%d)Nome:%s Fone:%s\n", i+1 , agenda[i].nome, agenda[i].fone);
    }
    getch();
}

void excluir() {
    int index = pesquisar();
    if (index == -1) {
		return;
    } else {
        char op;       
        do {
            system("cls");
            printf("Você tem certeza que deseja excluir (%s) ?\n", agenda[index].nome);
            printf("(1) Sim\n");
            printf("(2) Nao\n");
            scanf("%c", &op);
            switch(op) {
                case '1':
					for (int i = index; i < total;i++) {
						agenda[i] = agenda[i+1];
					}

					total--;
					break;
            }
        } while (op != '2' && op != '1');
    }
}

void menu(void) {
    char op;
    do {
        system("cls");
        printf("(1) Incluir\n");
        printf("(2) Consultar todos\n");
        printf("(3) Ordenar por nome\n");
        printf("(4) Pesquisar por nome\n");
        printf("(6) Alterar\n");
        printf("(7) Excluir\n");
        printf("(0) Sair\n");
        scanf("%c", &op);
        switch(op) {
            case '1':
                inclusao();
                break;
            case '2':
                listarTodos();
                break;
            case '3':
                ordenar();
                break;
            case '4':
                pesquisar();
                break;
            case '6':
                alterar();
                break;
            case '7':
                excluir();
                break;
        }
    } while (op != '0');
}
//---------------------------------------------------------------------------

#pragma argsused
int main(int argc, char* argv[]) {
    menu();
    system("pause");
    return 0;
}
//---------------------------------------------------------------------------

