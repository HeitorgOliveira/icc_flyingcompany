#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef char * string;
//TODO: criar classe reserva. Os atributos são: nome, sobrenome, cpf, data, numero do voo, id, numero de assento, classe, valor, origem e destino.
typedef struct 
{
    string nome, sobrenome, cpf, data, numassento, classe, origem, destino;
    float valor;
}Reserva;
//alguns dados são o mesmo para todos os outros. 

void AV(int assentos, float valor); // Implementar AV
void RR(string nome, string sobrenome, string cpf, string  data, int idvoo, string assento, string classe, float valor, string  origem, string destino); // Implementar RR
Reserva CR(string cpf); //Implementar CR
Reserva MR(string cpf, string nome, string sobrenome, string assento); // Implementar MR
void CA(string  cpf); // Implementar CA
Reserva * FD();
Reserva * FV();

int main(void)
{
    
}
