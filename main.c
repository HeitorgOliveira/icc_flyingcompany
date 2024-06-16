#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_RESERVAS 100


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

void *aloca(int N, int J);
void AV(int assentos, float Passagem_economica, float Passagem_executiva);
void RR(Reserva reserva);
void CR(char * cpf);
void MR(Reserva *cadastro, int assentos);
void CA(Reserva *cadastro, int assentos);
void FD(); // implementar FD
void FV();
void libertarreserva(Reserva *reserva);
int findreserva(Reserva *reserva);
int contreservas();
int getcapacidade();
Reserva lerdados();



int main(void){
    char comando[3];
    Passagem Passagemes;
    Reserva *cadastro;
    int cont = 0;

    do
    {
        scanf("%s", comando);

        if (strcmp(comando, "AV") == 0){
            int assentos;
            float Passagem_economica, Passagem_executiva;
            scanf("%d %f %f", &assentos, &Passagem_economica, &Passagem_executiva);
            AV(assentos, Passagem_economica, Passagem_executiva);
        }

        if (strcmp(comando, "RR") == 0){
            Reserva reserva = lerdados();
            if (contreservas() >= getcapacidade())
            {
                printf("Capacidade máxima atingida\n");
                FV();
            }
            RR(reserva);
            libertarreserva(&reserva);
        }

        if (strcmp(comando, "CR") == 0)
        {
            char cpf[15];
            scanf("%s", cpf);
            CR(cpf);
            return 0;
        }

        if (strcmp(comando, "MR") == 0){
            //MR(cadastro, assentos);
            printf("%i\n", getcapacidade());
            /*Reserva teste;
            teste.cpf = "um";
            teste.nome = "sera";
            teste.sobrenome = "que";
            teste.assento = "mudou?";
            printf("%i\n", findreserva(&teste));
            /*free(teste.nome);
            free(teste.sobrenome);
            free(teste.cpf);*/
            return 0;
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

int getcapacidade()
{
    FILE *arquivo_precos = fopen("precos.txt", "r");
    char linha[16];
    fgets(linha, sizeof(linha), arquivo_precos);
    char *token = strtok(linha, ": ");
    char * lorem = token;

    token = strtok(NULL, "\n");
    float capacidade = atof(token);
    return capacidade;
}

int contreservas()
{
    FILE *arquivo_reservas = fopen("reservas.csv", "r");
    if (arquivo_reservas == NULL)
    {
        printf("Erro ao abrir o arquivo\n");
        exit(1);
    }
    int cont = 0;
    char linha[400];

    if (fgets(linha, sizeof(linha), arquivo_reservas) == NULL)
    {
        printf("Arquivo sem cabeçalho\n");
        exit(1);
    }
    while(fgets(linha, sizeof(linha), arquivo_reservas) != NULL)
        cont++;
    return cont;
}

void AV(int assentos, float Passagem_economica, float Passagem_executiva){ // criar um novo arquivo

    FILE *arquivo_precos = fopen("precos.txt", "w");
    FILE *arquivo_reservas = fopen("reservas.csv", "w");
    if (arquivo_precos == NULL){
        printf("Erro na abertura do arquivo!\n");
        exit(1);
    }
    Passagem Passagemes;
    Passagemes.economica = Passagem_economica;
    Passagemes.executiva = Passagem_executiva;
    fprintf(arquivo_precos, "Capacidade: %i\nEconomica: %.2f\nExecutiva: %.2f", assentos, Passagem_economica, Passagem_executiva);
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
    fprintf(arquivo_reservas, "\n%s,%s,%s,%s,%s,%s,%s,%.2f,%s,%s", reserva.nome, reserva.sobrenome
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

int findreserva(Reserva *reserva)
{
    FILE *arquivo_reservas = fopen("reservas.csv", "r");
    if (arquivo_reservas == NULL)
    {
        printf("Arquivo 'reservas.csv' não abriu\n");
        exit(1);
    }
    char * cpf;
    char *nome;
    char *sobrenome;

    Reserva aux;

    cpf = reserva->cpf;
    char linha[400];
    if (fgets(linha, sizeof(linha), arquivo_reservas) == NULL)
    {
        printf("Arquivo sem cabeçalho\n");
        exit(1);
    }
    while(fgets(linha, sizeof(linha), arquivo_reservas) != NULL)
    {
        linha[strcspn(linha, "\n")] = '\0';
        printf("----------Linha:----------\n %s\n", linha);
        char delimitador[] = ",";
        char *resultado = strtok(linha, delimitador);
        nome = resultado;

        resultado = strtok(NULL, delimitador);
        sobrenome = resultado;

        resultado = strtok(NULL, delimitador);
        cpf = resultado;

        if (strcmp(cpf, reserva->cpf) == 0)
        {
            resultado = strtok(NULL, delimitador);
            aux.data = resultado;

            resultado = strtok(NULL, delimitador);
            aux.num_voo = resultado;

            resultado = strtok(NULL, delimitador);
            aux.classe = resultado;

            resultado = strtok(NULL, delimitador);
            aux.valor = atof(resultado);

            resultado = strtok(NULL, delimitador);
            aux.origem = resultado;

            resultado = strtok(NULL, delimitador);
            aux.destino = resultado;

            printf("AUX classe: %s\n", aux.classe);
            
            int i = 0;
            while(linha[i] != '\0')
            {
                linha[i] = '\0';
                i++;
            }

            fclose(arquivo_reservas);
            FILE *arquivo_reservas = fopen("reservas.csv", "a");
            fprintf(arquivo_reservas, "\n%s,%s,%s,%s,%s,%s,%s,%.2f,%s,%s", aux.nome, aux.sobrenome, aux.cpf, aux.data, aux.num_voo, aux.assento, aux.classe, aux.valor, aux.origem, aux.destino);
            fclose(arquivo_reservas);
            return 1;
        }
    }
    fclose(arquivo_reservas);
    return 0;
}

void CR(char *cpf)
{
    FILE *arquivo_reservas = fopen("reservas.csv", "r");
    if (arquivo_reservas == NULL)
    {
        printf("Arquivo 'reservas.csv' não abriu\n");
        exit(1);
    }
    Reserva reserva;

    char linha[400];
    int encontrou = 0;
    if(fgets(linha, sizeof(linha), arquivo_reservas) == NULL)
    {
        printf("Arquivo sem cabeçalho\n");
    }
    while (fgets(linha, sizeof(linha), arquivo_reservas) != NULL)
    {
        linha[strcspn(linha, "\n")] = '\0';
        char delimitador[] = ",";
        char *resultado = strtok(linha, delimitador);
        reserva.nome = resultado;

        resultado = strtok(NULL, delimitador);
        reserva.sobrenome = resultado;

        resultado = strtok(NULL, delimitador);
        reserva.cpf = resultado;

        if (strcmp(reserva.cpf, cpf) == 0)
        {
            resultado = strtok(NULL, delimitador);
            reserva.data = resultado;

            resultado = strtok(NULL, delimitador);
            reserva.num_voo = resultado;


            resultado = strtok(NULL, delimitador);
            reserva.assento = resultado;

            resultado = strtok(NULL, delimitador);
            reserva.classe = resultado;

            resultado = strtok(NULL, delimitador);
            reserva.valor = atof(resultado);

            resultado = strtok(NULL, delimitador);
            reserva.origem = resultado;

            resultado = strtok(NULL, delimitador);
            reserva.destino = resultado;

            printf("%s\n%s %s\n%s\nVoo:%s\n", reserva.cpf, reserva.nome, reserva.sobrenome, reserva.data, reserva.num_voo);
            printf("Assento:%s\nClasse:%s\nTrecho:%s %s\nValor:%.2f\n", reserva.assento, reserva.classe, reserva.origem, reserva.destino, reserva.valor);
            fclose(arquivo_reservas);
            return;
        }
    }
    if (!encontrou)
        printf("Não encontramos o CPF %s\n", cpf);
    fclose(arquivo_reservas);
    return;
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

void FV(){ //imprimir todo o arquivo, fechar o arquivo e liberar memoria
    printf("Voo Fechado!\n");

    /*for (int i = 0; i < assentos; i++){

        printf("\n%s\n", cadastro[i].cpf);
        printf("%s %s\n", cadastro[i].nome, cadastro[i].sobrenome);
        printf("%s\n", cadastro[i].assento);
    }

    float Passagem_total = 0;
    for (int k = 0; k < assentos; k++){
        Passagem_total += cadastro[k].Passagem;
    }

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
    free(cadastro);*/
}

void libertarreserva(Reserva *reserva)
{
    free(reserva->nome);
    free(reserva->sobrenome);
    free(reserva->cpf);
    free(reserva->data);
    free(reserva->num_voo);
    free(reserva->assento);
    free(reserva->classe);
    free(reserva->origem);
    free(reserva->destino);
}