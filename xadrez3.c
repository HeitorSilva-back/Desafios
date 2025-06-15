#include <stdio.h>

// =================== FUNÇÕES RECURSIVAS ===================

// Função recursiva para movimentar a Torre (direita)
void moverTorre(int casas, int atual) {
    if (atual > casas) return;
    printf("Direita %d\n", atual);
    moverTorre(casas, atual + 1);
}

// Função recursiva para movimentar a Rainha (esquerda)
void moverRainha(int casas, int atual) {
    if (atual > casas) return;
    printf("Esquerda %d\n", atual);
    moverRainha(casas, atual + 1);
}

// Função recursiva combinada com loops para o Bispo (diagonal cima-direita)
void moverBispoRecursivo(int casas, int atual) {
    if (atual > casas) return;

    // Loop aninhado para demonstrar controle horizontal e vertical
    for (int linha = 1; linha <= 1; linha++) { // externo: movimento "vertical"
        for (int coluna = 1; coluna <= 1; coluna++) { // interno: movimento "horizontal"
            printf("Cima Direita %d\n", atual);
        }
    }

    moverBispoRecursivo(casas, atual + 1);
}

// =================== CAVALO COM LOOPS COMPLEXOS ===================
void moverCavalo() {
    // O cavalo move-se duas casas para cima e uma para a direita.
    // Usamos duas variáveis para representar linha e coluna.
    printf("Movimento do Cavalo (2 casas para Cima, 1 para Direita):\n");

    int casasCima = 2;
    int casasDireita = 1;

    for (int i = 1; i <= casasCima; i++) {
        // Se chegar à segunda casa para cima, continue o movimento
        if (i == 2) {
            printf("Cima %d\n", i);
            int j = 1;
            while (j <= casasDireita) {
                if (j == 1) {
                    printf("Direita %d\n", j);
                    break; // após mover para direita, encerra
                }
                j++;
            }
        } else {
            printf("Cima %d\n", i);
        }
    }
}

// =================== MAIN ===================
int main() {
    // ---------- Torre ----------
    printf("Movimento da Torre (5 casas para a Direita):\n");
    moverTorre(5, 1);
    printf("\n");

    // ---------- Bispo ----------
    printf("Movimento do Bispo (5 casas na Diagonal Cima Direita):\n");
    moverBispoRecursivo(5, 1);
    printf("\n");

    // ---------- Rainha ----------
    printf("Movimento da Rainha (8 casas para a Esquerda):\n");
    moverRainha(8, 1);
    printf("\n");

    // ---------- Cavalo ----------
    moverCavalo();

    return 0;
}
