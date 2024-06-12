#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct{
    float executiva;
    float economica;
}Valor;

typedef struct{
    char* nome;
    char* sobrenome;
    char cpf[15];
    int dia;
    int mes;
    int ano;
    char* idvoo;
    char assento[4];
    char classe[10];
    float valor;
    char* origem; 
    char* destino;
} Dados;

void* aloca(int N, int J);
Valor AV(int *assentos, Valor valores); 
void RR(Dados *cadastro, int cont);
void CR(char *cpf); //Implementar CR
void MR(char *cpf, char* nome, char *sobrenome, char *cpf, char *assento); // Implementar MR
void CA(char * cpf); // Implementar CA
void * FD();
void * FV();

void* aloca(int N, int J){
    void *p;

    p= calloc(N*J);

    if(p==NULL){
        printf("Sem espaço");

        exit(1);
    }

return(p);
}

Valor AV(int *assentos, Valor valores){
    int assentos;
    Valor valores;

    scanf("%d %f %f", assentos, &valores.executiva, &valores.economica);

    FILE *arquivo;
    arquivo = fopen("info_voo.txt", "w");
    if(arquivo == NULL){
        printf("Erro na abertura do arquivo!");
        return(valores);
    }

    fclose(arquivo);
}

void RR(Dados *cadastro, int cont){
    char *p;

    p=(char*) aloca(sizeof(char), 700);
    scanf(" %s", p);
    cadastro[cont].nome=(char*) aloca(sizeof(char), strlen(p)+1);
    strcpy(cadastro[cont].nome, p);
    free(p);

    p=(char*) aloca(sizeof(char), 700);
    scanf(" %s", p);
    cadastro[cont].sobrenome=(char*) aloca(sizeof(char), strlen(p)+1);
    strcpy(cadastro[cont].sobrenome, p);
    free(p);

    scanf(" %s", cadastro[cont].cpf);

    scanf("%d %d %d", &cadastro[cont].dia,  &cadastro[cont].mes,  &cadastro[cont].ano);

    p=(char*) aloca(sizeof(char), 50);
    scanf(" %s", p);
    cadastro[cont].idvoo=(char*) aloca(sizeof(char), strlen(p)+1);
    strcpy(cadastro[cont].idvoo, p);
    free(p);

    scanf(" %s", cadastro[cont].assento);

    scanf(" %s", cadastro[cont].classe);

    scanf(" %f", &cadastro[cont].valor);

    p=(char*) aloca(sizeof(char), 500);
    scanf(" %s", p);
    cadastro[cont].origem=(char*) aloca(sizeof(char), strlen(p)+1);
    strcpy(cadastro[cont].origem, p);
    free(p);

    p=(char*) aloca(sizeof(char), 500);
    scanf(" %s", p);
    cadastro[cont].destino=(char*) aloca(sizeof(char), strlen(p)+1);
    strcpy(cadastro[cont].destino, p);
    free(p);
    
return;
}

int main(void){
    char comando[3];
    Dados *cadastro;
    int cont=0;

    scanf("%s", comando);

    if(strcmp(comando, "AV")==0){
        int assentos;
        Valor valores;

        valores= AV(&assentos, valores);
    }

    do{
        scanf("%s", comando);

        if(strcmp(comando, "RR")==0){

            cadastro = (Dados*)aloca(sizeof(Dados), assentos);

            RR(cadastro, cont);

            cont++;
        }

    }while(strcmp(comando, "FA")!=0 && strcmp(comando, "FV")!=0 && cont<assentos);


}
