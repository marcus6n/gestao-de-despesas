#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_DESPESAS 100

struct Despesa {
    double valor;
    char data[11];
    char categoria[50];
};

// Protótipos das funções
void exibirMenu();
void limparBuffer();
void consultarSaldo(double *saldo, struct Despesa *despesas, int numDespesas);
void registrarDespesa(struct Despesa *despesa, int *numDespesas);
void adicionarSaldo(double *saldo);
void listarDespesas(struct Despesa *despesas, int numDespesas);
void exibirCabecalho(const char *titulo);

int main() {
    double saldo = 1000.0;
    struct Despesa despesas[MAX_DESPESAS];
    int numDespesas = 0;

    int opcao;

    do {
        exibirMenu();

        // Validar entrada numérica
        while (scanf("%d", &opcao) != 1) {
            limparBuffer();
            printf("Opção inválida. Por favor, escolha uma opção válida: ");
        }

        switch (opcao) {
            case 1:
                consultarSaldo(&saldo, despesas, numDespesas);
                break;
            case 2:
                registrarDespesa(despesas, &numDespesas);
                break;
            case 3:
                adicionarSaldo(&saldo);
                break;
            case 4:
                listarDespesas(despesas, numDespesas);
                break;
            case 5:
                printf("\nSaindo do aplicativo. Até logo!\n");
                break;
            default:
                printf("\nOpção inválida. Por favor, escolha uma opção válida.\n");
        }

    } while (opcao != 5);

    return 0;
}

void exibirMenu() {
    exibirCabecalho("BoltFinance");
    printf("1. Consultar saldo\n");
    printf("2. Registrar despesas\n");
    printf("3. Adicionar saldo\n");
    printf("4. Listar despesas\n");
    printf("5. Sair\n");
    printf("Escolha uma opção: ");
}

void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void consultarSaldo(double *saldo, struct Despesa *despesas, int numDespesas) {
    exibirCabecalho("Consultar Saldo");

    printf("\nSaldo atual: R$%.2f\n", *saldo);

    // Mostrar despesas e subtrair do saldo
    for (int i = 0; i < numDespesas; i++) {
        printf("Despesa %d - Valor: R$%.2f | Data: %s | Categoria: %s\n", i + 1,
               despesas[i].valor, despesas[i].data, despesas[i].categoria);

        *saldo -= despesas[i].valor;
    }

    printf("========================================\n");
    printf("Saldo após despesas: R$%.2f\n", *saldo);
}

void registrarDespesa(struct Despesa *despesa, int *numDespesas) {
    exibirCabecalho("Registrar Despesa");

    printf("\nDigite a data da despesa (DD/MM/AAAA): ");
    scanf("%s", despesa[*numDespesas].data);

    printf("Digite a categoria da despesa: ");
    scanf("%s", despesa[*numDespesas].categoria);

    printf("Digite o valor da despesa em real: ");
    while (scanf("%lf", &despesa[*numDespesas].valor) != 1) {
        limparBuffer();
        printf("Valor inválido. Digite novamente: ");
    }

    (*numDespesas)++;
    printf("\nDespesa registrada com sucesso!\n");
}

void adicionarSaldo(double *saldo) {
    exibirCabecalho("Adicionar Saldo");

    double valorAdicional;
    printf("\nDigite o valor a ser adicionado ao saldo: ");
    while (scanf("%lf", &valorAdicional) != 1) {
        limparBuffer();
        printf("Valor inválido. Digite novamente: ");
    }
    *saldo += valorAdicional;
    printf("Saldo atualizado com sucesso!\n");
}

void listarDespesas(struct Despesa *despesas, int numDespesas) {
    exibirCabecalho("Lista de Despesas");

    if (numDespesas == 0) {
        printf("Nenhuma despesa registrada.\n");
    } else {
        for (int i = 0; i < numDespesas; i++) {
            printf("Despesa %d - Valor: R$%.2f | Data: %s | Categoria: %s\n", i + 1,
                   despesas[i].valor, despesas[i].data, despesas[i].categoria);
        }
    }

    printf("========================================\n");
}

void exibirCabecalho(const char *titulo) {
    printf("\n========================================\n");
    printf("           %s\n", titulo);
    printf("========================================\n");
}
