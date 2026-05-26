#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Dica sincera: pra testar antes de mandar, muda esse 26 pra uns 3 pra não ter que digitar tudo!
#define NUM_ESTADOS 26

typedef struct {
    char nome[50];
    int num_veiculos;
    int num_acidentes;
} Estado;

// (a) Procedimento para coletar dados
void coletarDados(Estado estados[]) {
    for (int i = 0; i < NUM_ESTADOS; i++) {
        printf("\n--- Coletando dados do Estado %d ---\n", i + 1);
        printf("Nome do estado: ");
        scanf(" %[^\n]", estados[i].nome);
        printf("Número de veículos (em 2007): ");
        scanf("%d", &estados[i].num_veiculos);
        printf("Número de acidentes (em 2007): ");
        scanf("%d", &estados[i].num_acidentes);
    }
}

// (b) Procedimento para maior e menor número de acidentes
void maiorMenorAcidentes(Estado estados[], int *ind_maior, int *ind_menor) {
    *ind_maior = 0;
    *ind_menor = 0;
    for (int i = 1; i < NUM_ESTADOS; i++) {
        if (estados[i].num_acidentes > estados[*ind_maior].num_acidentes) {
            *ind_maior = i;
        }
        if (estados[i].num_acidentes < estados[*ind_menor].num_acidentes) {
            *ind_menor = i;
        }
    }
}

// (c) Função que retorna o percentual de veículos envolvidos em acidentes
float percentualAcidentes(Estado estados[], int indice) {
    if (estados[indice].num_veiculos == 0) return 0.0;
    return ((float)estados[indice].num_acidentes / estados[indice].num_veiculos) * 100.0;
}

// (d) Função que retorna a média de acidentes no país
float mediaAcidentes(Estado estados[]) {
    int soma = 0;
    for (int i = 0; i < NUM_ESTADOS; i++) {
        soma += estados[i].num_acidentes;
    }
    return (float)soma / NUM_ESTADOS;
}

// (e) Procedimento que informa os estados acima da média
void acimaDaMedia(Estado estados[], float media) {
    printf("\n--- Estados com acidentes acima da média nacional (%.2f) ---\n", media);
    for (int i = 0; i < NUM_ESTADOS; i++) {
        if (estados[i].num_acidentes > media) {
            printf("- %s (Acidentes: %d)\n", estados[i].nome, estados[i].num_acidentes);
        }
    }
}

int main() {
    Estado estados[NUM_ESTADOS];
    int ind_maior, ind_menor;
    float media;

    // a) Coletar
    coletarDados(estados);

    // b) Maior e menor
    maiorMenorAcidentes(estados, &ind_maior, &ind_menor);
    printf("\n--- Estatísticas Extremas ---\n");
    printf("Maior número de acidentes: %d (Estado: %s)\n", estados[ind_maior].num_acidentes, estados[ind_maior].nome);
    printf("Menor número de acidentes: %d (Estado: %s)\n", estados[ind_menor].num_acidentes, estados[ind_menor].nome);

    // c) Percentuais
    printf("\n--- Percentual de Veículos em Acidentes por Estado ---\n");
    for (int i = 0; i < NUM_ESTADOS; i++) {
        printf("%s: %.2f%%\n", estados[i].nome, percentualAcidentes(estados, i));
    }

    // d) Média nacional
    media = mediaAcidentes(estados);
    printf("\nMédia de acidentes no país: %.2f\n", media);

    // e) Acima da média
    acimaDaMedia(estados, media);

    return 0;
}
