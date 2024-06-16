#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef char* string;

typedef struct{
    float executiva;
    float economica;
} Passagem;

typedef struct{
    string nome;
    string sobrenome;
    string cpf;
    string data;
    int dia;
    int mes;
    int ano;
    string num_voo;
    string assento;
    string classe;
    float valor;
    string origem;
    string destino;
} Reserva;

// Protótipo das Funções: tem que colocar os Reserva adquiridos no arquivo
void *aloca(int N, int J);
Reserva lerdados();
void AV(int assentos, float Passagem_economica, float Passagem_executiva);
void RR(string nome, string sobrenome, string cpf, string data, string numero_voo, string assento, string classe, float valor, string origem, string destino);
void CR(int assentos, Reserva *cadastro);
void MR(Reserva *cadastro, int assentos);
void CA(Reserva *cadastro, int assentos);
void FD(); // implementar FD
void FV(Reserva *cadastro, int assentos);


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
            printf("AAAAA");
            Reserva teste = lerdados();
            printf("Nome: %s \nSobrenome: %s\nCPF: %s\nValor: %f\nData: %s", teste.nome, teste.sobrenome, teste.cpf, teste.valor, teste.data);
            /*string nome, sobrenome, num_voo, origem, destino;
            char cpf[15], assento[4], classe[10], data[11];
            // Desculpe-me a ilegibilidade
            nome = (string) malloc(100 * sizeof(string)); if (nome == NULL) { printf("Ponteiro vazio.\n"); return 1;}
            sobrenome = (string) malloc(100 * sizeof(string)); if (sobrenome == NULL) { printf("Ponteiro vazio.\n"); return 1;}
            num_voo = (string) malloc(100 * sizeof(string)); if (num_voo == NULL) { printf("Ponteiro vazio.\n"); return 1;}
            origem = (string) malloc(100 * sizeof(string)); if (origem == NULL) { printf("Ponteiro vazio.\n"); return 1;}
            destino = (string) malloc(100 * sizeof(string)); if (destino == NULL) { printf("Ponteiro vazio.\n"); return 1;}
            float valor;
            scanf(" %s %s %s %s %s %s %s %f %s %s", nome, sobrenome, cpf, data, num_voo, assento, classe, &valor, origem, destino);
            nome = (string) realloc(nome, sizeof(string) * (strlen(nome)+1)); if (nome == NULL) { printf("Ponteiro vazio.\n"); return 1;}
            sobrenome = (string) realloc(sobrenome, sizeof(string) * (strlen(sobrenome)+1)); if (sobrenome == NULL) { printf("Ponteiro vazio.\n"); return 1;}
            num_voo = (string) realloc(num_voo, sizeof(string) * (strlen(num_voo))+1); if (num_voo == NULL) { printf("Ponteiro vazio.\n"); return 1;}
            origem = (string) realloc(origem, sizeof(string) * (sizeof(origem)+1)); if (origem == NULL) { printf("Ponteiro vazio.\n"); return 1;}
            destino = (string) realloc(destino, sizeof(string) * (strlen(destino)+1));  if (destino == NULL) { printf("Ponteiro vazio.\n"); return 1;}
            printf("Nome: %s\nTamanho de nome: %i\nTamanho em bits(bytes?): %i", nome, strlen(nome), sizeof(string) * sizeof(nome));*/


            /*cadastro = (Reserva *)aloca(sizeof(Reserva), assentos);

            RR(cadastro, cont, Passagemes, assentos);
            cont++;*/
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
    string nome, sobrenome, num_voo, origem, destino, cpf, assento, classe, data;
    // Desculpe-me a ilegibilidade
    nome = (string) malloc(100 * sizeof(string)); if (nome == NULL) { printf("Ponteiro vazio.\n"); exit(1);}
    cpf = (string) malloc(15 * sizeof(string)); if (cpf == NULL) { printf("Ponteiro vazio.\n"); exit(1);}
    assento = (string) malloc(4 * sizeof(string)); if (assento == NULL) { printf("Ponteiro vazio.\n"); exit(1);}
    classe = (string) malloc(10 * sizeof(string)); if (classe == NULL) { printf("Ponteiro vazio.\n"); exit(1);}
    data = (string) malloc(11 * sizeof(string)); if (data == NULL) { printf("Ponteiro vazio.\n"); exit(1);}
    sobrenome = (string) malloc(100 * sizeof(string)); if (sobrenome == NULL) { printf("Ponteiro vazio.\n");exit(1);}
    num_voo = (string) malloc(100 * sizeof(string)); if (num_voo == NULL) { printf("Ponteiro vazio.\n");exit(1);}
    origem = (string) malloc(100 * sizeof(string)); if (origem == NULL) { printf("Ponteiro vazio.\n");exit(1);}
    destino = (string) malloc(100 * sizeof(string)); if (destino == NULL) { printf("Ponteiro vazio.\n");exit(1);;}
    scanf(" %s %s %s %s %s %s %s %f %s %s", nome, sobrenome, cpf, data, num_voo, assento, classe, &valor, origem, destino);
    nome = (string) realloc(nome, sizeof(string) * (strlen(nome)+1)); if (nome == NULL) { printf("Ponteiro vazio.\n");exit(1);}
    sobrenome = (string) realloc(sobrenome, sizeof(string) * (strlen(sobrenome)+1)); if (sobrenome == NULL) { printf("Ponteiro vazio.\n");exit(1);}
    num_voo = (string) realloc(num_voo, sizeof(string) * (strlen(num_voo))+1); if (num_voo == NULL) { printf("Ponteiro vazio.\n");exit(1);}
    origem = (string) realloc(origem, sizeof(string) * (sizeof(origem)+1)); if (origem == NULL) { printf("Ponteiro vazio.\n");exit(1);}
    destino = (string) realloc(destino, sizeof(string) * (strlen(destino)+1));  if (destino == NULL) { printf("Ponteiro vazio.\n");exit(1);}
    Reserva reserva;
    reserva.nome = nome;
    reserva.sobrenome = sobrenome;
    reserva.cpf = cpf;
    reserva.data = data;
    reserva.num_voo = num_voo;
    reserva.assento = assento;
    reserva.origem = origem;
    reserva.destino = destino;
    reserva.valor = valor;
    return reserva;
}

void *aloca(int N, int J){
    void *p = malloc(N * J);

    if (p == NULL){
        printf("Sem espaço");
        exit(1);
    }

    return (p);
}

void AV(int assentos, float Passagem_economica, float Passagem_executiva){ // criar um novo arquivo

    printf("Assentos: %d\nPassagem executiva: %f\nPassagem economica: %f\n", assentos, Passagem_executiva, Passagem_economica);
    FILE *arquivo_precos = fopen("precos.txt", "w");
    if (arquivo_precos == NULL){
        printf("Erro na abertura do arquivo!\n");
        exit(1);
    }
    Passagem Passagemes;
    Passagemes.economica = Passagem_economica;
    Passagemes.executiva = Passagem_executiva;
    fprintf(arquivo_precos, "Economica: %.2f\nExecutiva: %.2f", Passagem_economica, Passagem_executiva);
    fclose(arquivo_precos);
}

void RR(string nome, string sobrenome, string cpf, string data, string numero_voo, string assento, string classe, float valor, string origem, string destino)
{ // ler e escrever no arquivo
    string p;

    /*if ((strcmp(cadastro[cont].classe, "executiva") == 0 && cadastro[cont].Passagem == Passagemes.executiva) ||
        (strcmp(cadastro[cont].classe, "economica") == 0 && cadastro[cont].Passagem == Passagemes.economica)){

        if (cadastro[cont].dia == cadastro[0].dia && cadastro[cont].mes == cadastro[0].mes && cadastro[cont].ano == cadastro[0].ano &&
            strcmp(cadastro[cont].num_voo, cadastro[0].num_voo) == 0 &&
            strcmp(cadastro[cont].origem, cadastro[0].origem) == 0 && strcmp(cadastro[cont].destino, cadastro[0].destino) == 0){
            
            for(int i = 0; i < assentos; i++){
                if(strcmp(cadastro[cont].assento, cadastro[i].assento) != 0){

                    p = (string )aloca(sizeof(char), 700);
                    scanf(" %s", p);
                    cadastro[cont].nome = (string )aloca(sizeof(char), strlen(p) + 1);
                    strcpy(cadastro[cont].nome, p);
                    free(p);

                    p = (string )aloca(sizeof(char), 700);
                    scanf(" %s", p);
                    cadastro[cont].sobrenome = (string )aloca(sizeof(char), strlen(p) + 1);
                    strcpy(cadastro[cont].sobrenome, p);
                    free(p);

                    scanf(" %s", cadastro[cont].cpf);

                    scanf("%d %d %d", &cadastro[cont].dia, &cadastro[cont].mes, &cadastro[cont].ano);

                    p = (string )aloca(sizeof(char), 50);
                    scanf(" %s", p);
                    cadastro[cont].num_voo = (string )aloca(sizeof(char), strlen(p) + 1);
                    strcpy(cadastro[cont].num_voo, p);
                    free(p);

                    scanf(" %s", cadastro[cont].assento);

                    scanf(" %s", cadastro[cont].classe);

                    scanf(" %f", &cadastro[cont].Passagem);

                    p = (string )aloca(sizeof(char), 5);
                    scanf(" %s", p);
                    cadastro[cont].origem = (string )aloca(sizeof(char), strlen(p) + 1);
                    strcpy(cadastro[cont].origem, p);
                    free(p);

                    p = (string )aloca(sizeof(char), 5);
                    scanf(" %s", p);
                    cadastro[cont].destino = (string )aloca(sizeof(char), strlen(p) + 1);
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
