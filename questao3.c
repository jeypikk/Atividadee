#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CONTAS 100

typedef struct {
    int numero;
    char nome[50];
    char cpf[15];
    char telefone[20];
    float saldo;
} Conta;

typedef struct {
    Conta contas[MAX_CONTAS];
    int qtd;
} Cadastro;

// (a) Função de busca
int buscarConta(Cadastro cad, int numero) {
    if (cad.qtd == 0) return -1; // Cadastro vazio
    for (int i = 0; i < cad.qtd; i++) {
        if (cad.contas[i].numero == numero) return i; // Encontrou, retorna a posição
    }
    return -2; // Não encontrou
}

// (b) Procedimento para cadastrar nova conta
void cadastrarConta(Cadastro *cad, int numero) {
    int pos = buscarConta(*cad, numero);
    if (pos >= 0) {
        printf("Aviso: Você não pode fazer o cadastramento, pois se trata de um número de conta repetido!\n");
    } else {
        if (cad->qtd >= MAX_CONTAS) {
            printf("Aviso: Cadastro cheio, impossível adicionar novas contas!\n");
            return;
        }
        cad->contas[cad->qtd].numero = numero;
        printf("Nome do titular: ");
        scanf(" %[^\n]", cad->contas[cad->qtd].nome);
        printf("CPF: ");
        scanf(" %[^\n]", cad->contas[cad->qtd].cpf);
        printf("Telefone: ");
        scanf(" %[^\n]", cad->contas[cad->qtd].telefone);
        printf("Saldo inicial: R$ ");
        scanf("%f", &cad->contas[cad->qtd].saldo);
        cad->qtd++;
        printf("Conta cadastrada com sucesso!\n");
    }
}

// (c) Procedimento para consultar saldo
void consultarSaldo(Cadastro cad, int numero) {
    int pos = buscarConta(cad, numero);
    if (pos >= 0) {
        printf("Saldo da conta %d: R$ %.2f\n", numero, cad.contas[pos].saldo);
    } else {
        printf("Aviso: A conta informada não está cadastrada.\n");
    }
}

// (d) Procedimento para fazer um depósito
void depositar(Cadastro *cad, int numero) {
    int pos = buscarConta(*cad, numero);
    if (pos >= 0) {
        float valor;
        printf("Informe o valor do depósito: R$ ");
        scanf("%f", &valor);
        if (valor > 0) {
            cad->contas[pos].saldo += valor;
            printf("Depósito realizado com sucesso! Novo saldo: R$ %.2f\n", cad->contas[pos].saldo);
        } else {
            printf("Erro: Valor de depósito inválido.\n");
        }
    } else {
        printf("Aviso: A conta informada não está cadastrada.\n");
    }
}

// (e) Procedimento para fazer um saque
void sacar(Cadastro *cad, int numero) {
    int pos = buscarConta(*cad, numero);
    if (pos >= 0) {
        float valor;
        printf("Informe o valor do saque: R$ ");
        scanf("%f", &valor);
        if (valor > 0 && cad->contas[pos].saldo >= valor) {
            cad->contas[pos].saldo -= valor;
            printf("Saque realizado com sucesso! Novo saldo: R$ %.2f\n", cad->contas[pos].saldo);
        } else if (valor > 0) {
            printf("Aviso: Não existe saldo suficiente para este saque.\n");
        } else {
            printf("Erro: Valor de saque inválido.\n");
        }
    } else {
        printf("Aviso: A conta informada não está cadastrada.\n");
    }
}

// (f) Procedimento para exibir os dados do cadastro
void exibirContas(Cadastro cad) {
    if (cad.qtd == 0) {
        printf("Nenhuma conta cadastrada neste banco.\n");
        return;
    }
    printf("\n=== Relatório de Contas Cadastradas ===\n");
    for (int i = 0; i < cad.qtd; i++) {
        printf("Conta: %d | Titular: %-20s | Telefone: %s\n", 
               cad.contas[i].numero, cad.contas[i].nome, cad.contas[i].telefone);
    }
    printf("=======================================\n");
}

int main() {
    Cadastro cad_corrente = {.qtd = 0};
    Cadastro cad_poupanca = {.qtd = 0};
    int opcao, tipo, numero;

    do {
        printf("\n========= BANCO DINHEIRO CERTO =========\n");
        printf("1. Cadastrar Conta\n");
        printf("2. Consultar Saldo\n");
        printf("3. Efetuar Depósito\n");
        printf("4. Efetuar Saque\n");
        printf("5. Exibir Cadastro Completo\n");
        printf("0. Sair\n");
        printf("========================================\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        if (opcao >= 1 && opcao <= 5) {
            printf("Selecione o tipo de conta (1 - Corrente | 2 - Poupança): ");
            scanf("%d", &tipo);
            if (tipo != 1 && tipo != 2) {
                printf("Tipo de conta inválido! Tente novamente.\n");
                continue;
            }
            
            Cadastro *cad_atual = (tipo == 1) ? &cad_corrente : &cad_poupanca;

            if (opcao != 5) {
                printf("Informe o número da conta: ");
                scanf("%d", &numero);
            }

            switch (opcao) {
                case 1: cadastrarConta(cad_atual, numero); break;
                case 2: consultarSaldo(*cad_atual, numero); break;
                case 3: depositar(cad_atual, numero); break;
                case 4: sacar(cad_atual, numero); break;
                case 5: exibirContas(*cad_atual); break;
            }
        } else if (opcao != 0) {
            printf("Opção inválida!\n");
        }
    } while (opcao != 0);

    printf("Encerrando o sistema do Banco Dinheiro Certo. Até logo!\n");
    return 0;
}
