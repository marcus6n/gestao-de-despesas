#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_DESPESAS 100
#define MAX_NOME_PESSOA 50

// Estrutura para representar uma despesa
struct Despesa
{
    char nomePessoa[MAX_NOME_PESSOA];
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
void gerenciarDespesas(struct Despesa *despesas, int *numDespesas, double *saldo);
void exibirCategoriasFiltradas(struct Despesa *despesas, int numDespesas);
void mostrarDespesaMaiorValor(struct Despesa *despesas, int numDespesas);
void listarDespesasOrdemCrescenteValor(struct Despesa *despesas, int numDespesas);
void listarDespesasOrdemCrescenteCategoria(struct Despesa *despesas, int numDespesas);
void exibirCabecalho(const char *titulo);
void exibirMenuDespesas();
void listarDespesas(struct Despesa *despesas, int numDespesas);
void listarPessoasDespesas(struct Despesa *despesas, int numDespesas);

int main()
{
    double saldo = 1000.0;
    struct Despesa despesas[MAX_DESPESAS];
    int numDespesas = 0;

    int opcao;

    do
    {
        exibirMenu();

        // Validar entrada numérica
        while (scanf("%d", &opcao) != 1)
        {
            limparBuffer();
            printf("Opção inválida. Por favor, escolha uma opção válida: ");
        }

        switch (opcao)
        {
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
            gerenciarDespesas(despesas, &numDespesas, &saldo);
            break;
        case 6:
            printf("\nSaindo do aplicativo. Até logo!\n");
            break;
        default:
            printf("\nOpção inválida. Por favor, escolha uma opção válida.\n");
        }

    } while (opcao != 6);

    return 0;
}

// Função para gerenciar todas as operações relacionadas a despesas
void gerenciarDespesas(struct Despesa *despesas, int *numDespesas, double *saldo)
{
    int opcao;

    do
    {
        exibirMenuDespesas();

        // Validar entrada numérica
        while (scanf("%d", &opcao) != 1)
        {
            limparBuffer();
            printf("Opção inválida. Por favor, escolha uma opção válida: ");
        }

        switch (opcao)
        {
        case 1:
            exibirCategoriasFiltradas(despesas, *numDespesas);
            break;
        case 2:
            mostrarDespesaMaiorValor(despesas, *numDespesas);
            break;
        case 3:
            listarDespesasOrdemCrescenteValor(despesas, *numDespesas);
            break;
        case 4:
            listarDespesasOrdemCrescenteCategoria(despesas, *numDespesas);
            break;
        case 5:
            listarPessoasDespesas(despesas, *numDespesas);
            break;
        case 6:
            printf("\nRetornando ao menu principal.\n");
            break;
        default:
            printf("\nOpção inválida. Por favor, escolha uma opção válida.\n");
        }

    } while (opcao != 6);
}

// Lista as pessoas registradas nas despesas
void listarPessoasDespesas(struct Despesa *despesas, int numDespesas)
{
    exibirCabecalho("Usuários Registrados nas Despesas");

    if (numDespesas == 0)
    {
        printf("Nenhuma despesa registrada.\n");
    }
    else
    {
        printf("Usuários registrados nas despesas:\n");
        for (int i = 0; i < numDespesas; i++)
        {
            printf("%s\n", despesas[i].nomePessoa);
        }
    }

    printf("========================================\n");
}

// Exibe despesas filtradas por categoria
void exibirCategoriasFiltradas(struct Despesa *despesas, int numDespesas)
{
    exibirCabecalho("Categorias Filtradas");

    char categoriaFiltro[50];
    printf("\nDigite a categoria para filtrar: ");
    scanf("%s", categoriaFiltro);

    printf("\nDespesas na categoria %s:\n", categoriaFiltro);

    int encontrouDespesa = 0;

    for (int i = 0; i < numDespesas; i++)
    {
        if (strcmp(despesas[i].categoria, categoriaFiltro) == 0)
        {
            printf("Valor: R$%.2f | Data: %s\n", despesas[i].valor, despesas[i].data);
            encontrouDespesa = 1;
        }
    }

    if (!encontrouDespesa)
    {
        printf("Nenhuma despesa encontrada nesta categoria.\n");
    }
}

// Exibe a despesa de maior valor
void mostrarDespesaMaiorValor(struct Despesa *despesas, int numDespesas)
{
    exibirCabecalho("Despesa de Maior Valor");

    if (numDespesas == 0)
    {
        printf("Nenhuma despesa registrada.\n");
        return;
    }

    int indiceMaior = 0;
    for (int i = 1; i < numDespesas; i++)
    {
        if (despesas[i].valor > despesas[indiceMaior].valor)
        {
            indiceMaior = i;
        }
    }

    if (despesas[indiceMaior].valor > 0)
    {
        printf("Despesa de maior valor:\n");
        printf("Valor: R$%.2f | Data: %s | Categoria: %s\n",
               despesas[indiceMaior].valor, despesas[indiceMaior].data, despesas[indiceMaior].categoria);
    }
    else
    {
        printf("Nenhuma despesa encontrada.\n");
    }
}

// Lista despesas em ordem crescente de valor
void listarDespesasOrdemCrescenteValor(struct Despesa *despesas, int numDespesas)
{
    exibirCabecalho("Despesas em Ordem Crescente de Valor");

    if (numDespesas == 0)
    {
        printf("Nenhuma despesa registrada.\n");
        return;
    }

    // Ordenar despesas por valor (bubble sort)
    for (int i = 0; i < numDespesas - 1; i++)
    {
        for (int j = 0; j < numDespesas - i - 1; j++)
        {
            if (despesas[j].valor > despesas[j + 1].valor)
            {
                // Trocar despesas[j] e despesas[j + 1]
                struct Despesa temp = despesas[j];
                despesas[j] = despesas[j + 1];
                despesas[j + 1] = temp;
            }
        }
    }

    // Exibir despesas ordenadas
    for (int i = 0; i < numDespesas; i++)
    {
        printf("Valor: R$%.2f | Data: %s | Categoria: %s\n",
               despesas[i].valor, despesas[i].data, despesas[i].categoria);
    }

    if (numDespesas == 0)
    {
        printf("Nenhuma despesa encontrada.\n");
    }
}

// Lista despesas em ordem crescente de categoria
void listarDespesasOrdemCrescenteCategoria(struct Despesa *despesas, int numDespesas)
{
    exibirCabecalho("Despesas em Ordem Crescente de Categoria");

    if (numDespesas == 0)
    {
        printf("Nenhuma despesa registrada.\n");
        return;
    }

    // Ordenar despesas por categoria (bubble sort)
    for (int i = 0; i < numDespesas - 1; i++)
    {
        for (int j = 0; j < numDespesas - i - 1; j++)
        {
            if (strcmp(despesas[j].categoria, despesas[j + 1].categoria) > 0)
            {
                // Trocar despesas[j] e despesas[j + 1]
                struct Despesa temp = despesas[j];
                despesas[j] = despesas[j + 1];
                despesas[j + 1] = temp;
            }
        }
    }

    // Exibir despesas ordenadas
    for (int i = 0; i < numDespesas; i++)
    {
        printf("Valor: R$%.2f | Data: %s | Categoria: %s\n",
               despesas[i].valor, despesas[i].data, despesas[i].categoria);
    }

    if (numDespesas == 0)
    {
        printf("Nenhuma despesa encontrada.\n");
    }
}

// Exibe o menu principal
void exibirMenu()
{
    exibirCabecalho("BoltFinance");
    printf("1. Consultar saldo\n");
    printf("2. Registrar despesas\n");
    printf("3. Adicionar saldo\n");
    printf("4. Listar despesas\n");
    printf("5. Gerenciar Despesas\n");
    printf("6. Sair\n");
    printf("Escolha uma opção: ");
}

// Exibe o menu de gerenciamento de despesas
void exibirMenuDespesas()
{
    exibirCabecalho("Menu de Despesas");
    printf("1. Filtrar Categorias\n");
    printf("2. Mostrar Despesa de Maior Valor\n");
    printf("3. Listar Despesas por Ordem Crescente do Valor\n");
    printf("4. Listar Despesas por Ordem Crescente da Categoria\n");
    printf("5. Listar usuários registrados\n");
    printf("6. Voltar ao menu principal\n");
    printf("Escolha uma opção: ");
}

// Limpa o buffer do teclado
void limparBuffer()
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
        ;
}

// Consulta o saldo, exibindo as despesas e subtraindo do saldo
void consultarSaldo(double *saldo, struct Despesa *despesas, int numDespesas)
{
    exibirCabecalho("Consultar Saldo");

    printf("\nSaldo atual: R$%.2f\n", *saldo);

    // Mostrar despesas e subtrair do saldo
    for (int i = 0; i < numDespesas; i++)
    {
        printf("Despesa %d - Valor: R$%.2f | Data: %s | Categoria: %s\n", i + 1,
               despesas[i].valor, despesas[i].data, despesas[i].categoria);

        *saldo -= despesas[i].valor;
    }

    printf("========================================\n");
    printf("Saldo após despesas: R$%.2f\n", *saldo);
}

// Registra uma nova despesa
void registrarDespesa(struct Despesa *despesa, int *numDespesas)
{
    exibirCabecalho("Registrar Despesa");

    printf("\nDigite o nome da pessoa na despesa: ");
    scanf("%s", despesa[*numDespesas].nomePessoa);

    printf("Digite a data da despesa (DD/MM/AAAA): ");
    scanf("%s", despesa[*numDespesas].data);

    printf("Digite a categoria da despesa: ");
    scanf("%s", despesa[*numDespesas].categoria);

    printf("Digite o valor da despesa em real: ");
    while (scanf("%lf", &despesa[*numDespesas].valor) != 1)
    {
        limparBuffer();
        printf("Valor inválido. Digite novamente: ");
    }

    (*numDespesas)++;
    printf("\nDespesa registrada com sucesso!\n");
}

// Adiciona saldo à conta
void adicionarSaldo(double *saldo)
{
    exibirCabecalho("Adicionar Saldo");

    double valorAdicional;
    printf("\nDigite o valor a ser adicionado ao saldo: ");
    while (scanf("%lf", &valorAdicional) != 1)
    {
        limparBuffer();
        printf("Valor inválido. Digite novamente: ");
    }
    *saldo += valorAdicional;
    printf("Saldo atualizado com sucesso!\n");
}

// Lista todas as despesas
void listarDespesas(struct Despesa *despesas, int numDespesas)
{
    exibirCabecalho("Lista de Despesas");

    if (numDespesas == 0)
    {
        printf("Nenhuma despesa registrada.\n");
    }
    else
    {
        for (int i = 0; i < numDespesas; i++)
        {
            printf("Despesa %d - Valor: R$%.2f | Data: %s | Categoria: %s\n", i + 1,
                   despesas[i].valor, despesas[i].data, despesas[i].categoria);
        }
    }

    printf("========================================\n");
}

// Exibe um cabeçalho com o título
void exibirCabecalho(const char *titulo)
{
    printf("\n========================================\n");
    printf("           %s\n", titulo);
    printf("========================================\n");
}