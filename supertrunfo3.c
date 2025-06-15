#include <stdio.h>
#include <string.h>

// Estrutura para armazenar os dados de uma carta
typedef struct {
    char nome_pais[50];
    int populacao;
    float area;
    float pib;
    int pontos_turisticos;
    float densidade;
    float pib_per_capita;
} Carta;

// Função para calcular densidade e PIB per capita
void calcularDados(Carta *c) {
    c->densidade = c->area > 0 ? c->populacao / c->area : 0;
    c->pib_per_capita = c->populacao > 0 ? (c->pib * 1000000000.0) / c->populacao : 0;
}

// Função para exibir os dados da carta
void exibirCarta(Carta c) {
    printf("\nNome do país: %s\n", c.nome_pais);
    printf("População: %d\n", c.populacao);
    printf("Área: %.2f km²\n", c.area);
    printf("PIB: %.2f bilhões de reais\n", c.pib);
    printf("Pontos turísticos: %d\n", c.pontos_turisticos);
    printf("Densidade Demográfica: %.2f hab/km²\n", c.densidade);
    printf("PIB per capita: %.2f reais\n", c.pib_per_capita);
}

// Função para obter o valor de um atributo
float obterValorAtributo(Carta c, int atributo) {
    switch (atributo) {
        case 1: return c.populacao;
        case 2: return c.area;
        case 3: return c.pib;
        case 4: return c.pontos_turisticos;
        case 5: return c.densidade;
        case 6: return c.pib_per_capita;
        default: return 0;
    }
}

// Função para mostrar o nome de um atributo
const char* nomeAtributo(int atributo) {
    switch (atributo) {
        case 1: return "População";
        case 2: return "Área";
        case 3: return "PIB";
        case 4: return "Pontos Turísticos";
        case 5: return "Densidade Demográfica";
        case 6: return "PIB per capita";
        default: return "Desconhecido";
    }
}

int main() {
    Carta carta1, carta2;

    // Cadastro das cartas
    printf("Cadastro da carta 1:\n");
    printf("Nome do país: "); fgets(carta1.nome_pais, 50, stdin); strtok(carta1.nome_pais, "\n");
    printf("População: "); scanf("%d", &carta1.populacao);
    printf("Área (km²): "); scanf("%f", &carta1.area);
    printf("PIB (em bilhões): "); scanf("%f", &carta1.pib);
    printf("Número de pontos turísticos: "); scanf("%d", &carta1.pontos_turisticos);
    calcularDados(&carta1);
    
    getchar(); // limpar buffer

    printf("\nCadastro da carta 2:\n");
    printf("Nome do país: "); fgets(carta2.nome_pais, 50, stdin); strtok(carta2.nome_pais, "\n");
    printf("População: "); scanf("%d", &carta2.populacao);
    printf("Área (km²): "); scanf("%f", &carta2.area);
    printf("PIB (em bilhões): "); scanf("%f", &carta2.pib);
    printf("Número de pontos turísticos: "); scanf("%d", &carta2.pontos_turisticos);
    calcularDados(&carta2);

    int atributo1, atributo2;

    // Menu para escolha dos atributos
    printf("\nEscolha o primeiro atributo para comparação:\n");
    printf("1 - População\n2 - Área\n3 - PIB\n4 - Pontos Turísticos\n5 - Densidade Demográfica\n6 - PIB per capita\n");
    scanf("%d", &atributo1);

    do {
        printf("Escolha o segundo atributo (diferente do primeiro):\n");
        scanf("%d", &atributo2);
    } while (atributo1 == atributo2 || atributo2 < 1 || atributo2 > 6);

    float valor1_a1 = obterValorAtributo(carta1, atributo1);
    float valor2_a1 = obterValorAtributo(carta2, atributo1);

    float valor1_a2 = obterValorAtributo(carta1, atributo2);
    float valor2_a2 = obterValorAtributo(carta2, atributo2);

    int v1 = 0, v2 = 0;

    // Regra: menor valor vence apenas para densidade
    if (atributo1 == 5) (valor1_a1 < valor2_a1) ? v1++ : (valor2_a1 < valor1_a1 ? v2++ : 0);
    else (valor1_a1 > valor2_a1) ? v1++ : (valor2_a1 > valor1_a1 ? v2++ : 0);

    if (atributo2 == 5) (valor1_a2 < valor2_a2) ? v1++ : (valor2_a2 < valor1_a2 ? v2++ : 0);
    else (valor1_a2 > valor2_a2) ? v1++ : (valor2_a2 > valor1_a2 ? v2++ : 0);

    float soma1 = valor1_a1 + valor1_a2;
    float soma2 = valor2_a1 + valor2_a2;

    // Exibir cartas e resultados
    printf("\n--- CARTA 1 ---"); exibirCarta(carta1);
    printf("\n--- CARTA 2 ---"); exibirCarta(carta2);

    printf("\nAtributos escolhidos: %s e %s\n", nomeAtributo(atributo1), nomeAtributo(atributo2));
    printf("%s - %s: %.2f | %s: %.2f | Soma: %.2f\n",
        carta1.nome_pais, nomeAtributo(atributo1), valor1_a1, nomeAtributo(atributo2), valor1_a2, soma1);
    printf("%s - %s: %.2f | %s: %.2f | Soma: %.2f\n",
        carta2.nome_pais, nomeAtributo(atributo1), valor2_a1, nomeAtributo(atributo2), valor2_a2, soma2);

    if (soma1 > soma2)
        printf("\nResultado: %s venceu a rodada!\n", carta1.nome_pais);
    else if (soma2 > soma1)
        printf("\nResultado: %s venceu a rodada!\n", carta2.nome_pais);
    else
        printf("\nResultado: Empate!\n");

    return 0;
}
