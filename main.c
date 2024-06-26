/*
Membros do grupo:
Nome: Heitor Gomes de Oliveira. No USP: 15458350
*/

/*

    Introdução:

        O código presente é feito na linguagem de programação C e é responsável pelo cadastro e gerenciamento de reservas de avião.
    
    Propósito:

        O projeto tem como propósito o estudo de conceitos da linguagem C como loops, verificações, declaração de variáveis.
        uso de ponteiros, uso de alocação dinâmica, modularização por meio de funções, declaração e implementação de funções, estruturas e
        armazenamento de dados com o uso de arquivos.

        O propósito do código é a criação de uma interface que auxilie o gerenciamento de reservas de avião, exibição de dados e do lucro total

*/


// Incluí as bibliotecas necessárias
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

// -------------------------------------------Structs--------------------------------------------------------|

//Defini as structs que serão usadas durante a execução do programa
//Essa primeira struct serve apenas para armazenar as informações dos preços das passagens
typedef struct{
    float executiva;
    float economica;
} Passagem;


//A segunda struct armazena as informações da reserva, como nome, sobrenome, cpf etc.
typedef struct{
    char nome[100];
    char sobrenome[100];
    char cpf[16];
    char data[11];
    char num_voo[5];
    char assento[10];
    char classe[20];
    float valor;
    char origem[100];
    char destino[100];
} Reserva;

// ----------------------------------------------------------------------------------------------------------|

// ---------------------------------------Protótipos das funções---------------------------------------------|

//Defini as funções que foram pedidas no documento, serão usadas duarante a execução do programa

//A função AV é a de abertura de voo, que recebe o numero de assentos disponíveis e o preço de cada classe: economica e executiva nesta ordem.
//Também são criados dois arquivos, o arquivo de reservas e o arquivo de preços
void AV(int assentos, float Passagem_economica, float Passagem_executiva);

//A função RR significa realizar reserva, e cria uma struct reserva com os dados necessários e insere no final do arquivo de reservas
void RR(Reserva reserva);

//A função Cr significa consultar reserva recebe um CPF e exibe os dados do CPF caso exista. Em caso de CPF inexistente, a função exibe um aviso
void CR(char * cpf);

//A função MR significa modificar reserva e recebe um CPF alvo, nome sobrenome, cpf e assento. Os dados após o CPF alvo serão os novos dados do cpf procurado caso exista. Em caso de CPF inxistente a função dará um aviso.
void MR(char *identificador, char* nome, char *sobrenome, char *novocpf, char*assento);

// A função CA significa cancelar reserva e deleta o CPF alvo da lisa de reservas do arquivo csv
void CA(char *cpf);

//A função FD significa fim do dia e exibe as reservas realizadas, exibe o lucro total e sai do programa.
void FD();

//A função FV significa fim do voo e exibe as reservas realizadas, exibe o lucro total e sai do programa, fechando o voo
void FV();

/*Também criei algumas funções utilitárias para ajudar a implementação. Dentre elas pode-se contar as reservas criadas,
encontrar uma reserva especifica dado um CPF, pode-se obter a capacidade informada pelo usuário, pode-se ler dados e retornar
um ponteiro para um array da struct Reserva e é possivel ler os dados informados pelo usuario no caso de um cadastro de reserva*/
int findreserva(char *identificador);
int contreservas();
int getcapacidade();
Reserva lerdados();
Reserva *getdados();

// ----------------------------------------------------------------------------------------------------------|

// -------------------------------------------------Main-----------------------------------------------------|

int main(void){
    char comando[3];
    do
    {
        scanf(" %s", comando);
        //cada caso que o usuário pode pedir foi checado
        if (strcmp(comando, "AV") == 0)
        {
            int assentos;
            float Passagem_economica, Passagem_executiva;
            scanf("%d %f %f", &assentos, &Passagem_economica, &Passagem_executiva);
            AV(assentos, Passagem_economica, Passagem_executiva);
        }

        else if (strcmp(comando, "RR") == 0){
            if (contreservas() >= getcapacidade())
            {
                printf("Capacidade máxima atingida\n");
                FV();
            }
            else 
            {
                Reserva reserva = lerdados();
                RR(reserva);
            }
        }

        else if (strcmp(comando, "CR") == 0)
        {
            char cpf[16];
            scanf("%s", cpf);
            CR(cpf);
        }

        else if (strcmp(comando, "MR") == 0){
            char cpf[16], nome[100], sobrenome[100], novocpf[20], assento[15];
            scanf(" %s %s %s %s %s", cpf, nome, sobrenome, novocpf, assento);
            MR(cpf, nome, sobrenome, novocpf, assento);
        }

        else if (strcmp(comando, "CA") == 0){
            char cpf[16];
            scanf(" %s", cpf);
            CA(cpf);
        }

        else if (strcmp(comando, "FV") == 0){
            FV();
            return 0;
        }
        else if (strcmp(comando, "FD") == 0){
            FD();
            return 0;
        }
        else
        {
            ;
        }

    //Se o numero de reservas for maior que a capacidade o loop para, porem esse usuario não sera cadastrado devido a funcao RR, que chama FV nesse caso
    } while (contreservas() <= getcapacidade());
    return 0;
}
// ----------------------------------------------------------------------------------------------------------|

// ---------------------------------------Funções------------------------------------------------------------|

//Aqui criei uma struct Reserva com os dados que serao lidos e a retornamos para a funcao RR

// ---------------------------------------Ler dados----------------------------------------------------------|

//A função ler dados terimina de ler os dados oferecidos pelo usuario via terminal e retorna uma struct Reserva que será usada posteriormente
Reserva lerdados()
{
    //São definidos os valores da struct e lidos os valores do terminal
    float valor;
    char nome[100], sobrenome[100], num_voo[5], origem[100], destino[100], cpf[16], assento[6], classe[15];
    int dia, mes, ano;
    scanf(" %s %s %s %2d %2d %4d %s %s %s %f %s %s", nome, sobrenome, cpf, &dia, &mes, &ano, num_voo, assento, classe, &valor, origem, destino);
    //Há uma verificação de data inválida
    if ((dia > 28 && mes == 2) || (dia > 31) || (dia < 1 ) || (mes > 12) || (mes < 1) || (ano < 1914))
    {
        printf("Dia: %i\nMes: %i\nAno: %i\n", dia, mes, ano);
        printf("Data inválida.\n");
        exit(1);
    }
    Reserva reserva;
    //A data informada é convertida para o formato DD/MM/AAAA
    sprintf(reserva.data, "%i/%i/%i", dia, mes,ano);
    strcpy(reserva.nome, nome);
    strcpy(reserva.sobrenome, sobrenome);
    strcpy(reserva.cpf, cpf);
    strcpy(reserva.num_voo, num_voo);
    strcpy(reserva.classe, classe);
    strcpy(reserva.assento, assento);
    strcpy(reserva.origem, origem);
    strcpy(reserva.destino, destino);
    reserva.valor = valor;    
    return reserva;
}
// ----------------------------------------------------------------------------------------------------------|

// ---------------------------------------Get dados----------------------------------------------------------|


//Na função getdados resgatei os dados de todas as reservas cadastradas para auxiliar em consultas futuras
Reserva *getdados()
{
    //A função abre um ponteiro de leitura para o arquivo reservas.csv, onde estão armazenadas as reservas e retorna um ponteiro para as reservas
    //A liberação da memória alocada fica a cargo da função que chamou getdados();
    FILE *arquivo_reservas = fopen("reservas.csv", "r");
    if (arquivo_reservas == NULL)
    {
        printf("Erro ao abrir o arquivo reservas!\n");
        exit(1);
    }

    char linha[400];
    int cont = 0;
    int qtdreservas = contreservas();
    Reserva *reservas = malloc(sizeof(Reserva) * qtdreservas);

    if(fgets(linha, sizeof(linha), arquivo_reservas) == NULL)
    {
        printf("Arquivo sem cabeçalho\n");
        exit(1);
    }
    //Os dados são separados por vírgula e armazenados no conteudo do ponteiro para uma struct Reserva
    while(fgets(linha, sizeof(linha), arquivo_reservas) != NULL)
    {
        linha[strcspn(linha, "\n")] = '\0';
        char delim[] = ",";
        char *token = strtok(linha, delim);
        strcpy(reservas[cont].nome, token);

        token = strtok(NULL, delim);
        strcpy(reservas[cont].sobrenome, token);

        token = strtok(NULL, delim);
        strcpy(reservas[cont].cpf, token);

        token = strtok(NULL, delim);
        strcpy(reservas[cont].data, token);

        token = strtok(NULL, delim);
        strcpy(reservas[cont].num_voo, token);

        token = strtok(NULL, delim);
        strcpy(reservas[cont].assento, token);

        token = strtok(NULL, delim);
        strcpy(reservas[cont].classe, token);

        token = strtok(NULL, delim);
        reservas[cont].valor = atof(token);

        token = strtok(NULL, delim);
        strcpy(reservas[cont].origem, token);

        token = strtok(NULL, delim);
        strcpy(reservas[cont].destino, token);
        
        cont++;
    }
    fclose(arquivo_reservas);
    return reservas;
}
// ----------------------------------------------------------------------------------------------------------|

// --------------------------------------- Find reserva -----------------------------------------------------|


//Na função findreserva() verifiquei se o identificador CPF está cadastrado, se sim retorna 1, em caso contrário retorna 0;
int findreserva(char * identificador)
{
    FILE *arquivo_reservas = fopen("reservas.csv", "r");
    if (arquivo_reservas == NULL)
    {
        printf("Arquivo 'reservas.csv' não abriu\n");
        exit(1);
    }

    char *cpf;
    char linha[400];

    if (fgets(linha, sizeof(linha), arquivo_reservas) == NULL)
    {
        printf("Arquivo sem cabeçalho\n");
        exit(1);
    }
    //Usa strtok para obter o CPF, caso não exista a função fecha o arquivo e retorna 0;
    while(fgets(linha, sizeof(linha), arquivo_reservas) != NULL)
    {
        linha[strcspn(linha, "\n")] = '\0';
        char delimitador[] = ",";
        char *resultado = strtok(linha, delimitador);

        resultado = strtok(NULL, delimitador);

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
// ----------------------------------------------------------------------------------------------------------|

// --------------------------------------- Get Capacidade ---------------------------------------------------|


//Na função getcapacidade é retornada a capacidade máxima de reservas como um inteiro, para facilitar o acesso a esse dado futuramente
int getcapacidade()
{
    //É aberto um ponteiro para o arquivo de preços e retorna a capacidade máxima
    FILE *arquivo_precos = fopen("precos.bin", "r");
    char linha[25];
    fgets(linha, sizeof(linha), arquivo_precos);
    char *token = strtok(linha, ": ");

    token = strtok(NULL, "\n");
    float capacidade = atof(token);
    return capacidade;
}
// ----------------------------------------------------------------------------------------------------------|

// --------------------------------------- Cont Reservas ----------------------------------------------------|


//Na função contreservas retornei o numero de reservas realizadas para facilitar o uso de outras funções ao longo do codigo
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
// ----------------------------------------------------------------------------------------------------------|

// --------------------------------------- Abertura de voo --------------------------------------------------|


void AV(int assentos, float Passagem_economica, float Passagem_executiva)
{ 
    //Aqui criei o arquivo com as informações das reservas e criei o cabeçalho do arquivo CSV que armazenará as reservas e a capacidade do voo
    FILE *arquivo_precos = fopen("precos.bin", "w");
    FILE *arquivo_reservas = fopen("reservas.csv", "w");
    if (arquivo_precos == NULL){
        printf("Erro na abertura do arquivo!\n");
        exit(1);
    }
    fprintf(arquivo_precos, "Capacidade: %i\nEconomica: %.2f\nExecutiva: %.2f", assentos, Passagem_economica, Passagem_executiva);
    //O cabeçalho segue o padrão de RR e das reservas, para facilitar o armazenamento de dados, decidi salvar em um formato de tabela ou planilha.
    fprintf(arquivo_reservas, "nome,sobrenome,cpf,data,numero_voo,assento,classe,valor,origem,destino");
    fclose(arquivo_precos);
    fclose(arquivo_reservas);
}
// ----------------------------------------------------------------------------------------------------------|

// --------------------------------------- Realizar Reserva -------------------------------------------------|

//A função realizar reserva recebe uma struct reserva para armazenar no arquivo CSV, a leitura dos dados foi feita pela função ler dados
void RR(Reserva reserva)
{
    //Para facilitar a função de realizar reserva, fiz uma função auxiliar para receber os dados da reserva e chamei a função RR com esses dados já armazenados
    //A função RR recebe os dados para realizar a reserva e usa a extensão append no arquivo para escrever uma nova reserva no arquivo
    FILE *arquivo_reservas = fopen("reservas.csv", "a");
    
    if (arquivo_reservas == NULL)
    {
        printf("Arquivo 'reservas.csv' não abriu\n");
        exit(1);
    }
    //Adicionei a tabela reserva no arquivo CSV
    fprintf(arquivo_reservas, "\n%s,%s,%s,%s,%s,%s,%s,%.2f,%s,%s", reserva.nome, reserva.sobrenome
    , reserva.cpf, reserva.data, reserva.num_voo, reserva.assento, reserva.classe, reserva.valor, reserva.origem, reserva.destino);
    fclose(arquivo_reservas);
}
// ----------------------------------------------------------------------------------------------------------|

// --------------------------------------- Consultar Reserva ------------------------------------------------|


void CR(char *cpf)
{
    //A função recebe um CPF como entrada e realiza iterações pelo arquivo procurando por um CPF que seja igual ao informado. caso acabe a iteraçãoe o CPF não foi encontrado
    //notifica-se o usuário da inexistência do CPF requisitado

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
    //É feita uma iteração pelo arquivo CSV linha por linha e foi usada a função strtok, salvando cada dado do usuario separado por virgula.
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

        //Os dados são copiados até chegar em CPF, que é comparado com o CPF alvo, em caso positivo os outros dados são exibidos, em caso negativo
        //O loop continua
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

            printf("%s\n%s %s\n%s\nVoo: %s\n", reserva.cpf, reserva.nome, reserva.sobrenome, reserva.data, reserva.num_voo);
            printf("Assento: %s\nClasse: %s\nTrecho: %s %s\nValor: %.2f\n--------------------------------------------------\n", reserva.assento, reserva.classe, reserva.origem, reserva.destino, reserva.valor);
            fclose(arquivo_reservas);
            return;
        }
    }
    if (!encontrou)
        printf("Não encontramos o CPF %s\n", cpf);
    fclose(arquivo_reservas);
    return;
}
// ----------------------------------------------------------------------------------------------------------|

// --------------------------------------- Modificar Reserva ------------------------------------------------|

//Modificar reserva recebe o CPF alvo que vai ser modificado. as outras entradas são os dados a serem alterados, sendo eles o nome, sobrenome,
//o novo CPF e o novo assento. A função não retorna nenhum valor
void MR(char *identificador, char *nome, char *sobrenome, char *novocpf, char *assento)
{
    /*O funcionamento desta função é interessante. Na verdade nenhum dado é modificado, eu apaguei a tabela
    com os dados de todos os usuarios e escrevi uma outra onde o usuario solicitado tem suas devidas alterações*/
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
    Reserva *reservas = malloc(sizeof(Reserva) * qtdreservas);
    char linha[400];
    int cont = 0;

    if (fgets(linha, sizeof(linha), arquivo_reservasMR) == NULL)
    {
        printf("Arquivo sem cabeçalho\n");
        exit(1);
    }
    //No loop while são feitas as separações dos dados por vírgula, com o uso da função strtok 
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
            
            //São informadas ao usuário as modificações realizadas.
            printf("Reserva Modificada:\n%s\n%s %s\n%s\nVoo: %s\nAssento: %s\nClasse: %s\nTrecho: %s %s\nValor: %.2f\n--------------------------------------------------\n", reservas[cont].cpf,
            reservas[cont].nome, reservas[cont].sobrenome, reservas[cont].data, reservas[cont].num_voo, reservas[cont].assento, reservas[cont].classe,
            reservas[cont].origem, reservas[cont].destino, reservas[cont].valor);
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


    //O arquivo é reescrito. Para isso o arquivo foi aberto no modo W, que reescreve o arquivo, é feito o cabeçalho da tabela e após isso
    //Os usuários são cadastrados novamente.
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
    free(reservas);
    reservas = NULL;
}
// ----------------------------------------------------------------------------------------------------------|

// --------------------------------------- Cancelar Reserva -------------------------------------------------|


void CA(char *identificador)
{
    /*A função CA tem um funcionamento semelhante ao MR, ela apaga a tabela com as reservas e a reescreve sem o usuario que quero deletar*/
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
    char linha[400];
    int cont = 0;
    char auxnome[100];
    char auxsobrenome[100];
    char auxcpf[16];

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
// ----------------------------------------------------------------------------------------------------------|

// ------------------------------------------ Fim do dia ----------------------------------------------------|


void FD()
{
    //Aqui as funções utilitárias são usadas de uma forma elegante para exibir os dados requisitados
    printf("Fechamento do dia:\n");
    int qtdreservas = contreservas();
    float lucrobruto = 0;
    Reserva *reservas = getdados();
    printf("Quantidade de reservas: %i\n", qtdreservas);
    for(int i = 0; i < qtdreservas; i++)
    {
        lucrobruto+= reservas[i].valor;
    }
    printf("Posição: %.2f\n", lucrobruto);
    printf("--------------------------------------------------\n");
    free(reservas);
    reservas = NULL;
}
// ----------------------------------------------------------------------------------------------------------|

// --------------------------------------- Fechamento do voo ------------------------------------------------|

void FV()
{
    //Aqui também foram usadas as fuções auxiliares para facilitar o trabalho
    printf("Voo Fechado!\n\n");
    Reserva *reservas = getdados();
    float lucrobruto = 0;
    int qtdreservas = contreservas();
    for(int i = 0; i < qtdreservas; i++)
    {
        printf("%s\n%s %s\n%s\n\n", reservas[i].cpf, reservas[i].nome, reservas[i].sobrenome, reservas[i].assento);
        lucrobruto += reservas[i].valor;
    }
    printf("Valor total: %.2f\n", lucrobruto);
    printf("--------------------------------------------------\n");
    free(reservas);
    reservas = NULL;
}

// ----------------------------------------------------------------------------------------------------------|
