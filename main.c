#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_RESERVAS 100


typedef struct{
    float executiva;
    float economica;
} Passagem;

typedef struct{
    char nome[100];
    char sobrenome[100];
    char cpf[12];
    char data[11];
    int dia;
    int mes;
    int ano;
    char num_voo[5];
    char assento[10];
    char classe[20];
    float valor;
    char origem[100];
    char destino[100];
} Reserva;

void *aloca(int N, int J);
void AV(int assentos, float Passagem_economica, float Passagem_executiva);
void RR(Reserva reserva);
void CR(char * cpf);
void MR(char *identificador, char* nome, char *sobrenome, char *novocpf, char*assento);
void CA(char *cpf);
void FD();
void FV();
int findreserva(char *identificador);
int contreservas();
int getcapacidade();
Reserva lerdados();



int main(void){
    char comando[3];
    do
    {
        scanf("%s", comando);

        //FEITA
        if (strcmp(comando, "AV") == 0){
            int assentos;
            float Passagem_economica, Passagem_executiva;
            scanf("%d %f %f", &assentos, &Passagem_economica, &Passagem_executiva);
            AV(assentos, Passagem_economica, Passagem_executiva);
        }

        //FEITA
        if (strcmp(comando, "RR") == 0){
            if (contreservas() >= getcapacidade())
            {
                printf("Capacidade máxima atingida\n");
                FV();
            }
            else 
            {
                Reserva reserva = lerdados();
                RR(reserva);
                //libertarreserva(&reserva);
            }
        }

        //FEITA
        if (strcmp(comando, "CR") == 0)
        {
            char cpf[15];
            scanf("%s", cpf);
            CR(cpf);
            return 0;
        }

        //FEITA
        if (strcmp(comando, "MR") == 0){
            char cpf[15], nome[100], sobrenome[100], novocpf[15], assento[15];
            scanf(" %s %s %s %s %s", cpf, nome, sobrenome, novocpf, assento);
            MR(cpf, nome, sobrenome, novocpf, assento);
        }

        //FEITA
        if (strcmp(comando, "CA") == 0){
            char cpf[15];
            scanf(" %s", cpf);
            CA(cpf);
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
    char nome[100], sobrenome[100], num_voo[5], origem[100], destino[100], cpf[15], assento[6], classe[15], data[11];
    scanf(" %s %s %s %s %s %s %s %f %s %s", nome, sobrenome, cpf, data, num_voo, assento, classe, &valor, origem, destino);
    Reserva reserva;
    strcpy(reserva.nome, nome);
    strcpy(reserva.sobrenome, sobrenome);
    strcpy(reserva.cpf, cpf);
    strcpy(reserva.data, data);
    strcpy(reserva.num_voo, num_voo);
    strcpy(reserva.classe, classe);
    strcpy(reserva.assento, assento);
    strcpy(reserva.origem, origem);
    strcpy(reserva.destino, destino);
    reserva.valor = valor;    
    return reserva;
}

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
    fprintf(arquivo_reservas, "nome,sobrenome,cpf,data,numero_voo,assento,classe,valor,origem,destino");
    fclose(arquivo_precos);
    fclose(arquivo_reservas);
}

void RR(Reserva reserva)
{
    FILE *arquivo_reservas = fopen("reservas.csv", "a");
    if (arquivo_reservas == NULL)
    {
        printf("Arquivo 'reservas.csv' não abriu\n");
        exit(1);
    }
    fprintf(arquivo_reservas, "\n%s,%s,%s,%s,%s,%s,%s,%.2f,%s,%s", reserva.nome, reserva.sobrenome
    , reserva.cpf, reserva.data, reserva.num_voo, reserva.assento, reserva.classe, reserva.valor, reserva.origem, reserva.destino);
    fclose(arquivo_reservas);
}

int findreserva(char * identificador)
{
    FILE *arquivo_reservas = fopen("reservas.csv", "r");
    if (arquivo_reservas == NULL)
    {
        printf("Arquivo 'reservas.csv' não abriu\n");
        exit(1);
    }

    char *cpf;
    char *nome;
    char *sobrenome;
    char linha[400];

    if (fgets(linha, sizeof(linha), arquivo_reservas) == NULL)
    {
        printf("Arquivo sem cabeçalho\n");
        exit(1);
    }
    while(fgets(linha, sizeof(linha), arquivo_reservas) != NULL)
    {
        linha[strcspn(linha, "\n")] = '\0';
        char delimitador[] = ",";
        char *resultado = strtok(linha, delimitador);
        nome = resultado;

        resultado = strtok(NULL, delimitador);
        sobrenome = resultado;

        resultado = strtok(NULL, delimitador);
        cpf = resultado;

        if (strcmp(cpf, identificador) == 0)
        {
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
        strcpy(reserva.nome, resultado);

        resultado = strtok(NULL, delimitador);
        strcpy(reserva.sobrenome, resultado);


        resultado = strtok(NULL, delimitador);
        strcpy(reserva.cpf, resultado);


        if (strcmp(reserva.cpf, cpf) == 0)
        {
            resultado = strtok(NULL, delimitador);
            strcpy(reserva.data, resultado);


            resultado = strtok(NULL, delimitador);
            strcpy(reserva.num_voo, resultado);


            resultado = strtok(NULL, delimitador);
            strcpy(reserva.assento, resultado);

            resultado = strtok(NULL, delimitador);
            strcpy(reserva.classe, resultado);

            resultado = strtok(NULL, delimitador);
            reserva.valor = atof(resultado);

            resultado = strtok(NULL, delimitador);
            strcpy(reserva.origem, resultado);

            resultado = strtok(NULL, delimitador);
            strcpy(reserva.destino, resultado);

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

void MR(char *identificador, char *nome, char *sobrenome, char *novocpf, char *assento)
{
    if(!findreserva(identificador))
    {
        printf("CPF não encontrado");
        return;
    }
    FILE *arquivo_reservasMR = fopen("reservas.csv", "r");
    if(arquivo_reservasMR == NULL)
    {
        printf("Erro abrindo o arquivo de reservas\n");
        exit(1);
    }
    int qtdreservas = contreservas();
    Reserva reservas[qtdreservas];
    char *aux;
    char linha[400];
    int cont = 0;

    if (fgets(linha, sizeof(linha), arquivo_reservasMR) == NULL)
    {
        printf("Arquivo sem cabeçalho\n");
        exit(1);
    }
    while (fgets(linha, sizeof(linha), arquivo_reservasMR) != NULL && (cont < qtdreservas))
    {
        linha[strcspn(linha, "\n")] = '\0';
        char delimitador[] = ",";
        char *token = strtok(linha, delimitador);
        strcpy(reservas[cont].nome, token);
        
        token = strtok(NULL, delimitador);
        strcpy(reservas[cont].sobrenome, token);

        token = strtok(NULL, delimitador);
        strcpy(reservas[cont].cpf, token);

        if (strcmp(reservas[cont].cpf, identificador) == 0)
        {
            strcpy(reservas[cont].nome, nome);                                                                                                                                                                                                                   
            strcpy(reservas[cont].sobrenome, sobrenome);          
            strcpy(reservas[cont].cpf, novocpf);                                                                                                                                                                                                                                                    

            token = strtok(NULL, delimitador);
            strcpy(reservas[cont].data, token);

            token = strtok(NULL, delimitador);
            strcpy(reservas[cont].num_voo, token);

            token = strtok(NULL, delimitador);
            strcpy(reservas[cont].assento, token);
            strcpy(reservas[cont].assento, assento);

            token = strtok(NULL, delimitador);
            strcpy(reservas[cont].classe, token);

            token = strtok(NULL, delimitador);
            reservas[cont].valor = atof(token);

            token = strtok(NULL, delimitador);
            strcpy(reservas[cont].origem, token);

            token = strtok(NULL, delimitador);
            strcpy(reservas[cont].destino, token);
            cont++;
        }
        else
        {
            token = strtok(NULL, delimitador);
            strcpy(reservas[cont].data, token);

            token = strtok(NULL, delimitador);
            strcpy(reservas[cont].num_voo, token);

            token = strtok(NULL, delimitador);
            strcpy(reservas[cont].assento, token);

            token = strtok(NULL, delimitador);
            strcpy(reservas[cont].classe, token);

            token = strtok(NULL, delimitador);
            reservas[cont].valor = atof(token);

            token = strtok(NULL, delimitador);
            strcpy(reservas[cont].origem, token);

            token = strtok(NULL, delimitador);
            strcpy(reservas[cont].destino, token);            
            cont++;
        }
    }
    fclose(arquivo_reservasMR);

    arquivo_reservasMR = fopen("reservas.csv", "w");
    if(arquivo_reservasMR == NULL)
    {
        printf("Erro ao abrir arquivo");
        exit(1);
    }
    fprintf(arquivo_reservasMR, "nome,sobrenome,cpf,data,numero_voo,assento,classe,valor,origem,destino");
    for(int i = 0; i < qtdreservas; i++)
    {
        fprintf(arquivo_reservasMR, "\n%s,%s,%s,%s,%s,%s,%s,%.2f,%s,%s", reservas[i].nome, reservas[i].sobrenome
    , reservas[i].cpf, reservas[i].data, reservas[i].num_voo, reservas[i].assento, reservas[i].classe, reservas[i].valor, reservas[i].origem, reservas[i].destino);
    }
    fclose(arquivo_reservasMR);
}

void CA(char *identificador){
    if(!findreserva(identificador))
    {
        printf("CPF não encontrado!\n");
        return;
    }
    FILE *arquivo_reservasCA = fopen("reservas.csv", "r");
    if(arquivo_reservasCA == NULL)
    {
        printf("Erro abrindo o arquivo de reservas\n");
        exit(1);
    }
    int qtdreservas = contreservas();
    Reserva reservas[qtdreservas];
    char *aux;
    char linha[400];
    int cont = 0;
    char auxnome[100];
    char auxsobrenome[100];
    char auxcpf[15];

    if (fgets(linha, sizeof(linha), arquivo_reservasCA) == NULL)
    {
        printf("Arquivo sem cabeçalho\n");
        exit(1);
    }
    while (fgets(linha, sizeof(linha), arquivo_reservasCA) != NULL && (cont < qtdreservas))
    {
        linha[strcspn(linha, "\n")] = '\0';
        char delimitador[] = ",";
        char *token = strtok(linha, delimitador);
        strcpy(auxnome, token);
        
        token = strtok(NULL, delimitador);
        strcpy(auxsobrenome, token);

        token = strtok(NULL, delimitador);
        strcpy(auxcpf, token);

        if (!(strcmp(auxcpf, identificador) == 0))
        {
            strcpy(reservas[cont].nome, auxnome);
            strcpy(reservas[cont].sobrenome, auxsobrenome);
            strcpy(reservas[cont].cpf, auxcpf);
            token = strtok(NULL, delimitador);
            strcpy(reservas[cont].data, token);

            token = strtok(NULL, delimitador);
            strcpy(reservas[cont].num_voo, token);

            token = strtok(NULL, delimitador);
            strcpy(reservas[cont].assento, token);

            token = strtok(NULL, delimitador);
            strcpy(reservas[cont].classe, token);

            token = strtok(NULL, delimitador);
            reservas[cont].valor = atof(token);

            token = strtok(NULL, delimitador);
            strcpy(reservas[cont].origem, token);

            token = strtok(NULL, delimitador);
            strcpy(reservas[cont].destino, token);            
            printf("Cont: %i\nNome: %s\n", cont, reservas[cont].nome);
            cont++;
        }
    }
    fclose(arquivo_reservasCA);

    arquivo_reservasCA = fopen("reservas.csv", "w");
    if(arquivo_reservasCA == NULL)
    {
        printf("Erro ao abrir arquivo");
        exit(1);
    }
    fprintf(arquivo_reservasCA, "nome,sobrenome,cpf,data,numero_voo,assento,classe,valor,origem,destino");
    qtdreservas--;
    for(int i = 0; i < qtdreservas; i++)
    {
        fprintf(arquivo_reservasCA, "\n%s,%s,%s,%s,%s,%s,%s,%.2f,%s,%s", reservas[i].nome, reservas[i].sobrenome
    , reservas[i].cpf, reservas[i].data, reservas[i].num_voo, reservas[i].assento, reservas[i].classe, reservas[i].valor, reservas[i].origem, reservas[i].destino);
    }
    fclose(arquivo_reservasCA);
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