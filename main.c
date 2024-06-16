#include <stdio.h>
#include <string.h>
#include <stdlib.h>


typedef struct{
    float executiva;
    float economica;
} Passagem;

typedef struct{
    char * nome;
    char * sobrenome;
    char * cpf;
    char * data;
    int dia;
    int mes;
    int ano;
    char * num_voo;
    char * assento;
    char * classe;
    float valor;
    char * origem;
    char * destino;
} Reserva;

// Protótipo das Funções: tem que colocar os Reserva adquiridos no arquivo
void *aloca(int N, int J);
Reserva lerdados();
void AV(int assentos, float Passagem_economica, float Passagem_executiva);
void RR(Reserva reserva);
void CR(int assentos, Reserva *cadastro);
void MR(Reserva *cadastro, int assentos);
void CA(Reserva *cadastro, int assentos);
void FD(); // implementar FD
void FV(Reserva *cadastro, int assentos);
//void libertarreserva(Reserva *reserva);


int main(void){
    char comando[3];
    Passagem Passagemes;
    Reserva *cadastro;
    int cont = 0;

    scanf("%s", comando);

    if (strcmp(comando, "AV") == 0){
        int assentos;
        float Passagem_economica, Passagem_executiva;
        scanf("%d %f %f", &assentos, &Passagem_economica, &Passagem_executiva);
        AV(assentos, Passagem_economica, Passagem_executiva);
    }

    do{
        scanf("%s", comando);

        if (strcmp(comando, "RR") == 0){
            Reserva reserva = lerdados();
            /*cadastro = (Reserva *)aloca(sizeof(Reserva), assentos);
            
            RR(cadastro, cont, Passagemes, assentos);
            cont++;*/
            printf("TESTE DOS DADOS \n\n\nNome: %s\nSobrenome: %s\nCPF: %s\nData: %s\nNum_voo: %s\nClasse: %s\nAssento: %s\nValor: %.2f\nOrigem: %s\nDestino: %s\n"
            ,reserva.nome, reserva.sobrenome, reserva.cpf, reserva.data, reserva.num_voo, reserva.classe, reserva.assento, reserva.valor, reserva.origem, reserva.destino);
            RR(reserva);
            //libertarreserva(&reserva);
        }

        if (strcmp(comando, "CR") == 0){
            //CR(assentos, cadastro);
        }

        if (strcmp(comando, "MR") == 0){
            //MR(cadastro, assentos);
        }

        if (strcmp(comando, "CA") == 0){
            //CA(cadastro, assentos);
        }

    } while (strcmp(comando, "FD") != 0 || strcmp(comando, "FV") != 0 /*|| cont < assentos)*/);

    /*if (strcmp(comando, "FV") == 0 || cont >= assentos){
        FV(cadastro, assentos);
    } else if (strcmp(comando, "FD") == 0){
        FD();
    }*/

    return 0;
}

Reserva lerdados()
{
    float valor;
    char *nome, *sobrenome, *num_voo, *origem, *destino, *cpf, *assento, *classe, *data;
    // Desculpe-me a ilegibilidade
    nome = (char *) malloc(100 * sizeof(char *)); if (nome == NULL) { printf("Ponteiro vazio.\n"); exit(1);}
    cpf = (char *) malloc(15 * sizeof(char *)); if (cpf == NULL) { printf("Ponteiro vazio.\n"); exit(1);}
    assento = (char *) malloc(4 * sizeof(char *)); if (assento == NULL) { printf("Ponteiro vazio.\n"); exit(1);}
    classe = (char *) malloc(10 * sizeof(char *)); if (classe == NULL) { printf("Ponteiro vazio.\n"); exit(1);}
    data = (char *) malloc(11 * sizeof(char *)); if (data == NULL) { printf("Ponteiro vazio.\n"); exit(1);}
    sobrenome = (char *) malloc(100 * sizeof(char *)); if (sobrenome == NULL) { printf("Ponteiro vazio.\n");exit(1);}
    num_voo = (char *) malloc(100 * sizeof(char *)); if (num_voo == NULL) { printf("Ponteiro vazio.\n");exit(1);}
    origem = (char *) malloc(100 * sizeof(char *)); if (origem == NULL) { printf("Ponteiro vazio.\n");exit(1);}
    destino = (char *) malloc(100 * sizeof(char *)); if (destino == NULL) { printf("Ponteiro vazio.\n");exit(1);}

    scanf(" %s %s %s %s %s %s %s %f %s %s", nome, sobrenome, cpf, data, num_voo, assento, classe, &valor, origem, destino);
    
    Reserva reserva;
    reserva.nome = nome;
    reserva.sobrenome = sobrenome;
    reserva.cpf = cpf;
    reserva.data = data;
    reserva.num_voo = num_voo;
    reserva.classe = classe;
    reserva.assento = assento;
    reserva.origem = origem;
    reserva.destino = destino;
    reserva.valor = valor;
    return reserva;
}

/*void *aloca(int N, int J){
    void *p = malloc(N * J);

    if (p == NULL){
        printf("Sem espaço");
        exit(1);
    }

    return (p);
}*/

void AV(int assentos, float Passagem_economica, float Passagem_executiva){ // criar um novo arquivo

    printf("Assentos: %d\nPassagem executiva: %f\nPassagem economica: %f\n", assentos, Passagem_executiva, Passagem_economica);
    FILE *arquivo_precos = fopen("precos.txt", "w");
    FILE *arquivo_reservas = fopen("reservas.csv", "w");
    if (arquivo_precos == NULL){
        printf("Erro na abertura do arquivo!\n");
        exit(1);
    }
    Passagem Passagemes;
    Passagemes.economica = Passagem_economica;
    Passagemes.executiva = Passagem_executiva;
    fprintf(arquivo_precos, "Economica: %.2f\nExecutiva: %.2f", Passagem_economica, Passagem_executiva);
    fprintf(arquivo_reservas, "nome, sobrenome, cpf, data, numero_voo, assento, classe, valor, origem, destino");
    fclose(arquivo_precos);
    fclose(arquivo_reservas);
}

void RR(Reserva reserva)
{ // ler e escrever no arquivo
    FILE *arquivo_reservas = fopen("reservas.csv", "a");
    if (arquivo_reservas == NULL)
    {
        printf("Arquivo 'reservas.csv' não abriu\n");
        exit(1);
    }
    fprintf(arquivo_reservas, "\n%s, %s, %s, %s, %s, %s, %s, %.2f, %s, %s", reserva.nome, reserva.sobrenome
    , reserva.cpf, reserva.data, reserva.num_voo, reserva.assento, reserva.classe, reserva.valor, reserva.origem, reserva.destino);
    fclose(arquivo_reservas);
    /*char * p;

    if ((strcmp(cadastro[cont].classe, "executiva") == 0 && cadastro[cont].Passagem == Passagemes.executiva) ||
        (strcmp(cadastro[cont].classe, "economica") == 0 && cadastro[cont].Passagem == Passagemes.economica)){

        if (cadastro[cont].dia == cadastro[0].dia && cadastro[cont].mes == cadastro[0].mes && cadastro[cont].ano == cadastro[0].ano &&
            strcmp(cadastro[cont].num_voo, cadastro[0].num_voo) == 0 &&
            strcmp(cadastro[cont].origem, cadastro[0].origem) == 0 && strcmp(cadastro[cont].destino, cadastro[0].destino) == 0){
            
            for(int i = 0; i < assentos; i++){
                if(strcmp(cadastro[cont].assento, cadastro[i].assento) != 0){

                    p = (char * )aloca(sizeof(char), 700);
                    scanf(" %s", p);
                    cadastro[cont].nome = (char * )aloca(sizeof(char), strlen(p) + 1);
                    strcpy(cadastro[cont].nome, p);
                    free(p);

                    p = (char * )aloca(sizeof(char), 700);
                    scanf(" %s", p);
                    cadastro[cont].sobrenome = (char * )aloca(sizeof(char), strlen(p) + 1);
                    strcpy(cadastro[cont].sobrenome, p);
                    free(p);

                    scanf(" %s", cadastro[cont].cpf);

                    scanf("%d %d %d", &cadastro[cont].dia, &cadastro[cont].mes, &cadastro[cont].ano);

                    p = (char * )aloca(sizeof(char), 50);
                    scanf(" %s", p);
                    cadastro[cont].num_voo = (char * )aloca(sizeof(char), strlen(p) + 1);
                    strcpy(cadastro[cont].num_voo, p);
                    free(p);

                    scanf(" %s", cadastro[cont].assento);

                    scanf(" %s", cadastro[cont].classe);

                    scanf(" %f", &cadastro[cont].Passagem);

                    p = (char * )aloca(sizeof(char), 5);
                    scanf(" %s", p);
                    cadastro[cont].origem = (char * )aloca(sizeof(char), strlen(p) + 1);
                    strcpy(cadastro[cont].origem, p);
                    free(p);

                    p = (char * )aloca(sizeof(char), 5);
                    scanf(" %s", p);
                    cadastro[cont].destino = (char * )aloca(sizeof(char), strlen(p) + 1);
                    strcpy(cadastro[cont].destino, p);
                    free(p);
                }
            }
        }
    } else {
        printf("Erro nos Reserva da reserva.\n");
    }*/
}

void CR(int assentos, Reserva *cadastro){ //ler arquivo 
    char cpf[15];

    scanf("%s", cpf);

    for (int i = 0; i < assentos; i++){
        if (strcmp(cpf, cadastro[i].cpf) == 0){

            printf("%s\n", cadastro[i].cpf);
            printf("%s %s\n", cadastro[i].nome, cadastro[i].sobrenome);
            printf("%d/%d/%d\n", cadastro[i].dia, cadastro[i].mes, cadastro[i].ano);
            printf("Voo: %s\n", cadastro[i].num_voo);
            printf("Assento: %s\n", cadastro[i].assento);
            printf("Classe: %s\n", cadastro[i].classe);
            printf("Trecho: %s %s\n", cadastro[i].origem, cadastro[i].destino);
            //printf("Passagem %.2f\n", cadastro[i].Passagem);

            for (int j = 0; j < 50; j++){
                printf("-");
            }

            printf("\n");
            break;
        }
    }
}

void MR(Reserva *cadastro, int assentos){ // ler, escrever por cima / apagar e escrever no lugar
    char cpf[15], *nome, *sobrenome, assento_mod[4];
    int encontrado = 0;

    scanf("%s %s %s %s %s", cpf, nome, sobrenome, cpf, assento_mod);

    for (int i = 0; i < assentos; i++){
        if (strcmp(cpf, cadastro[i].cpf) == 0){

            encontrado = 1;

            printf("Reserva Modificada:\n");
            printf("%s\n", cadastro[i].cpf);
            printf("%s %s\n", cadastro[i].nome, cadastro[i].sobrenome);
            printf("%d/%d/%d\n", cadastro[i].dia, cadastro[i].mes, cadastro[i].ano);
            printf("Voo: %s\n", cadastro[i].num_voo);

            strcpy(cadastro[i].assento, assento_mod);
            printf("Assento: %s\n", cadastro[i].assento);

            printf("Classe: %s\n", cadastro[i].classe);
            printf("Trecho: %s %s\n", cadastro[i].origem, cadastro[i].destino);
            //printf("Passagem %.2f\n", cadastro[i].Passagem);

            for (int j = 0; j < 50; j++){
                printf("-");
            }

            printf("\n");
            break;
        }
    }

    if (!encontrado){
        printf("Reserva não encontrada.\n");
    }
}

void CA(Reserva *cadastro, int assentos){ // ler e apagar reserva
    char cpf[15];
    int encontrado = 0;

    scanf("%s", cpf);

    for (int i = 0; i < assentos; i++){
        if (strcmp(cpf, cadastro[i].cpf) == 0){

            encontrado = 1;

            strcpy(cadastro[i].cpf, "");

            free(cadastro[i].nome);
            cadastro[i].nome = NULL;

            free(cadastro[i].sobrenome);
            cadastro[i].sobrenome = NULL;

            cadastro[i].dia = 0;
            cadastro[i].mes = 0;
            cadastro[i].ano = 0;

            strcpy(cadastro[i].num_voo, "");
            strcpy(cadastro[i].assento, "");
            strcpy(cadastro[i].classe, "");
            //cadastro[i].Passagem = 0.0;

            strcpy(cadastro[i].origem, "");
            strcpy(cadastro[i].destino, "");

            break;
        }
    }

    if (!encontrado){
        printf("Reserva não encontrada.\n");
    }
}

void FD(){ // RR inseridos no dia, antes do arquivo fechar
    
    //fclose(arquivo);
}

void FV(Reserva *cadastro, int assentos){ //imprimir todo o arquivo, fechar o arquivo e liberar memoria
    printf("Voo Fechado!\n");

    for (int i = 0; i < assentos; i++){

        printf("\n%s\n", cadastro[i].cpf);
        printf("%s %s\n", cadastro[i].nome, cadastro[i].sobrenome);
        printf("%s\n", cadastro[i].assento);
    }

    float Passagem_total = 0;
    /*for (int k = 0; k < assentos; k++){
        Passagem_total += cadastro[k].Passagem;
    }*/

    printf("\nPassagem Total: %f\n", Passagem_total);

    for (int j = 0; j < 50; j++){
        printf("-");
    }

    //fclose(arquivo);

    for (int h = 0; h < assentos; h++){

        free(cadastro[h].nome);
        cadastro[h].nome = NULL;

        free(cadastro[h].sobrenome);
        cadastro[h].sobrenome = NULL;

        strcpy(cadastro[h].cpf, "");

        cadastro[h].dia = 0;
        cadastro[h].mes = 0;
        cadastro[h].ano = 0;

        strcpy(cadastro[h].num_voo, "");
        strcpy(cadastro[h].assento, "");
        strcpy(cadastro[h].classe, "");
        //cadastro[h].Passagem = 0.0;

        strcpy(cadastro[h].origem, "");
        strcpy(cadastro[h].destino, "");
    }
    free(cadastro);
}

void libertarreserva(Reserva *reserva)
{
    free(reserva->nome);
    printf("1");
    free(reserva->sobrenome);
    printf("2");
    free(reserva->cpf);
    printf("3");
    free(reserva->data);
    printf("4");
    free(reserva->num_voo);
    printf("5");
    free(reserva->assento);
    printf("6");
    free(reserva->classe);
    printf("7");
    free(reserva->origem);
    printf("8");
    free(reserva->destino);
    printf("9");
}