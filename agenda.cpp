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
	char endereco[250];
	char email[80];
	char dataNascimento[10];
} T_agenda;


//////////////////////////////////////////////////
//  Variáveis globais             
//////////////////////////////////////////////////
T_agenda agenda[50];

int total = 0;


//////////////////////////////////////////////////
//  Funções             
//////////////////////////////////////////////////

/**
 * Verifica se o contato jah existe na agenda retornando true, caso contrario
 * retorna false.
 */
bool jahExiste(char *nome) {
    for (int i= 0; i < total; i++) {
        if (strcmp(agenda[i].nome, nome) == 0) {
            return true;
        }
    }

    return false;
}

/**
 * Ordena os contatos da lista de contatos
 */
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

int getIndex(char pesq[]) {
    for (int i= 0; i < total; i++) {
        if (strcmp(agenda[i].nome, pesq) == 0) {
            return i;
        }
    }
    
    return -1;
}

/**
 * Mostra as informações do contato que está no index
 */
void mostrarInformacoes(int index, char extra[]) {
    printf("%s)Nome:%s\n", extra, agenda[index].nome);
    printf("  Fone:%s\n", agenda[index].fone);
    printf("  Endereco:%s\n", agenda[index].endereco);
    printf("  E-Mail:%s\n", agenda[index].email);
    printf("  Data de Nascimento:%s\n", agenda[index].dataNascimento);
}

/**
 * Inclui um contato na agenda
 */
void inclusao(void) {
    system("cls");
    getchar();

    char nomeTmp[50];
    printf("Nome: ");
    gets(nomeTmp);

    for (int j=0; j < strlen(nomeTmp); j++) {
        nomeTmp[j] = toupper(nomeTmp[j]);
    }

    if (strlen(nomeTmp) == 0) {
        printf("CONTATO INVALIDO!");
        getchar();
    } else if (jahExiste(nomeTmp)) {
        printf("CONTATO JA EXISTENTE!");
        getchar();
    } else {
        // Nome
        strcpy(agenda[total].nome, nomeTmp);
        
        // Telefone
        printf("Telefone: ");
        gets(agenda[total].fone);

        // Endereço
        printf("Endereco: ");
        gets(agenda[total].endereco);
        
        // E-mail
        printf("E-Mail: ");
        gets(agenda[total].email);
        
        // Data de Nascimento
        printf("Data de Nascimento: ");
        gets(agenda[total].dataNascimento);

        total++;
        
        ordenar();
    }
}

/**
 * Retorna a posição do contato na agenda, caso nada seja encontrado retorna -1;
 */
int pesquisarPorNome(bool mostrar = false) {
    system("cls");
    getchar();

    printf("Entre com o nome que deseja pesquisar: ");
    char pesq[20];
    gets(pesq);

    for(int j=0;j<strlen(pesq);j++){
        pesq[j]=toupper(pesq[j]);
    }

    for (int i= 0; i < total; i++) {
        if (strcmp(agenda[i].nome, pesq) == 0) {
            if (mostrar) {
                mostrarInformacoes(i, "1");
                getch();
            }
            return i;
        }
    }

    if (mostrar) {
        // Caso não tenha encontrado nenhum registro mostra a mensagem e retorna -1
        printf("\nNOME NAO CADASTRADO!");
        getch();
    }
    return -1;
}

/**
 * Pesquisar os contatos por letra
 */
int pesquisarPorLetra(void) {
    system("cls");
    getchar();

    char letra;
    printf("Entre com a letra que deseja pesquisar: ");
    letra = getchar();
    letra = toupper(letra);

    bool achou = false;

    int contador = 1;
    char contadorStr[10];
    for (int i= 0; i < total; i++) {
        if (agenda[i].nome[0] == letra) {
            printf("--\n");
            itoa(contador, contadorStr, 10);
            mostrarInformacoes(i, contadorStr);
            achou = true;
            contador++;
        }
    }

    // Caso não tenha encontrado nenhum registro mostra a mensagem e retorna -1
    if (!achou) {
        printf("\nNENHUM CONTATO FOI ENCONTRADO!");
    }
    
    getch();
}

/**
 * Apresenta um menu com as formas de pesquisas disponíveis
 */
void pesquisar() {
    char op;
    do {   
        system("cls");
        printf("(1) Pesquisar por letra\n");
        printf("(2) Pesquisar por nome\n");
        printf("(0) Voltar\n");
        printf("Escolha como deseja pesquisar: ");
        scanf("%c", &op);
        switch(op) {
            case '1':
                pesquisarPorLetra();                 
                break;
            case '2':
                pesquisarPorNome(true);
                break;
        }
    } while (op != '0');  
}

/**
 * Altera as informações do contato da agenda, de acordo com o campo escolhido
 */
void alterar(void) {    
    int index = pesquisarPorNome();
    if (index == -1) {
        printf("\nNOME NAO CADASTRADO!");
        getch();
       return;
    }

    char op;
    do {
        system("cls");
        mostrarInformacoes(index, "1");
        printf("\n");
        printf("(1) Nome\n");
        printf("(2) Telefone\n");
        printf("(3) Endereco\n");
        printf("(4) E-Mail\n");
        printf("(5) Data de Nascimento\n");
        printf("(0) Voltar\n");
        printf("Escolha o que deseja alterar: ");
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
    
                ordenar();
                index = getIndex(nomeTmp);
                 
                break;
            case '2':
                getchar();
                printf("Telefone: ");
                gets(agenda[index].fone);
                break;
            case '3':
                getchar();
                printf("Endereco: ");
                gets(agenda[index].endereco);
                break;
            case '4':
                getchar();
                printf("E-Mail: ");
                gets(agenda[index].email);
                break;
            case '5':
                getchar();
                printf("Data de Nascimento: ");
                gets(agenda[index].dataNascimento);
                break;
        }
    } while (op != '0');
}

/**
 * Lista todos os contatos da agenda.
 */
void listarTodos(void) {
    system("cls");
    getchar();

    char contadorStr[10];
    printf("Lista de contatos:\n\n");
    for (int i = 0; i < total; i++) {
        printf("--\n");
        itoa(i+1, contadorStr, 10);
        mostrarInformacoes(i, contadorStr);
    }

    getchar();
}

/**
 * Exclui um contato da agenda
 */
void excluir() {
    int index = pesquisarPorNome();
    if (index == -1) {
        printf("\nNOME NAO CADASTRADO!");
        getch();
        return;
    } else {
        char op;       
        do {
            system("cls");
            printf("Voce tem certeza que deseja excluir (%s) ?\n", agenda[index].nome);
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

/**
 * Apresenta todas as opções da agenda, e espera o usuário digita alguma válida
 */
void menu(void) {
    char op;
    do {
        system("cls");
        printf("(1) Incluir\n");
        printf("(2) Consultar todos\n");
        printf("(3) Pesquisar\n");
        printf("(4) Alterar\n");
        printf("(5) Excluir\n");
        printf("(0) Sair\n");
        printf("Digite a opcao desejada: ");
        scanf("%c", &op);
        switch(op) {
            case '1':
                inclusao();
                break;
            case '2':
                listarTodos();
                break;
            case '3':
                pesquisar();
                break;
            case '4':
                alterar();
                break;
            case '5':
                excluir();
                break;
        }
    } while (op != '0');
}

//---------------------------------------------------------------------------

//////////////////////////////////////////////////
//  Main
//////////////////////////////////////////////////
int main(int argc, char* argv[]) {
    menu();
    system("pause");
    return 0;
}

//---------------------------------------------------------------------------

