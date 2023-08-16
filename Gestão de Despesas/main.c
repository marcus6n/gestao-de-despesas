#include <stdio.h>
#include <stdlib.h>

struct Despesa {
    double valor; // Doubke para valores com casas decimais
    char data[11];
    char categoria[50];
};

int main() {
    // Criando uma despesa de exemplo
    struct Despesa despesa1;
    despesa1.valor = 50.0;
    strcpy(despesa1.data, "10/08/2023"); // strcpy é usado para copiar strings para um array de char
    strcpy(despesa1.categoria, "Alimentação");

    // Exibindo a despesa
    printf("Valor: R$%.2f | Data: %s | Categoria: %s\n", despesa1.valor, despesa1.data, despesa1.categoria);

    return 0;
}