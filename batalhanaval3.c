#include <stdio.h>

#define TAB_SIZE 10
#define SHIP 3
#define WATER 0
#define EFFECT 5

#define SKILL_SIZE 5 // Tamanho fixo das matrizes de habilidade 5x5

// Inicializa o tabuleiro com água
void init_board(int board[TAB_SIZE][TAB_SIZE]) {
    for (int i=0; i<TAB_SIZE; i++)
        for (int j=0; j<TAB_SIZE; j++)
            board[i][j] = WATER;
}

// Posiciona um navio horizontal ou vertical simples para exemplo
void place_sample_ships(int board[TAB_SIZE][TAB_SIZE]) {
    // Navio horizontal de tamanho 3
    int r = 2, c = 2;
    for (int i = 0; i < 3; i++) {
        board[r][c+i] = SHIP;
    }

    // Navio vertical de tamanho 3
    r = 5; c = 7;
    for (int i = 0; i < 3; i++) {
        board[r+i][c] = SHIP;
    }
}

// Cria matriz de habilidade Cone (forma de cone apontando para baixo)
void create_cone(int cone[SKILL_SIZE][SKILL_SIZE]) {
    // Limpa tudo
    for(int i=0; i<SKILL_SIZE; i++) {
        for(int j=0; j<SKILL_SIZE; j++) {
            cone[i][j] = 0;
        }
    }
    /*
    Exemplo visual do cone 5x5 (índice i = linha, j = coluna):

    Linha 0:       0 0 1 0 0
    Linha 1:       0 1 1 1 0
    Linha 2:       1 1 1 1 1
    Linha 3:       0 0 0 0 0
    Linha 4:       0 0 0 0 0

    Isso representa um cone que começa no topo e se abre para baixo.
    */
    for(int i=0; i<3; i++) {          // 3 primeiras linhas com cone
        int start = 2 - i;            // coluna inicial do cone na linha i
        int end = 2 + i;              // coluna final do cone na linha i
        for(int j=start; j<=end; j++) {
            cone[i][j] = 1;
        }
    }
}

// Cria matriz de habilidade Cruz (cruz com ponto central)
void create_cross(int cross[SKILL_SIZE][SKILL_SIZE]) {
    // Limpa tudo
    for(int i=0; i<SKILL_SIZE; i++)
        for(int j=0; j<SKILL_SIZE; j++)
            cross[i][j] = 0;

    /*
    Exemplo visual da cruz 5x5:

    Linha 0: 0 0 1 0 0
    Linha 1: 0 0 1 0 0
    Linha 2: 1 1 1 1 1
    Linha 3: 0 0 1 0 0
    Linha 4: 0 0 1 0 0
    */

    int center = SKILL_SIZE/2;
    for(int i=0; i<SKILL_SIZE; i++) {
        cross[i][center] = 1;      // coluna central
        cross[center][i] = 1;      // linha central
    }
}

// Cria matriz de habilidade Octaedro (losango com ponto central)
void create_octaedro(int octa[SKILL_SIZE][SKILL_SIZE]) {
    // Limpa tudo
    for(int i=0; i<SKILL_SIZE; i++)
        for(int j=0; j<SKILL_SIZE; j++)
            octa[i][j] = 0;

    /*
    Visual do octaedro (losango):

    Linha 0: 0 0 1 0 0
    Linha 1: 0 1 1 1 0
    Linha 2: 1 1 1 1 1
    Linha 3: 0 1 1 1 0
    Linha 4: 0 0 1 0 0
    */

    int center = SKILL_SIZE/2;
    for(int i=0; i<SKILL_SIZE; i++) {
        int dist = (i <= center) ? i : SKILL_SIZE - 1 - i;
        for(int j = center - dist; j <= center + dist; j++) {
            octa[i][j] = 1;
        }
    }
}

// Sobrepõe uma matriz de habilidade no tabuleiro a partir do ponto (origin_row, origin_col)
void apply_skill(int board[TAB_SIZE][TAB_SIZE], int skill[SKILL_SIZE][SKILL_SIZE], int origin_row, int origin_col) {
    int offset = SKILL_SIZE / 2;

    for(int i=0; i<SKILL_SIZE; i++) {
        for(int j=0; j<SKILL_SIZE; j++) {
            if(skill[i][j] == 1) {
                int r = origin_row - offset + i;
                int c = origin_col - offset + j;

                // Verifica se está dentro do tabuleiro
                if(r >=0 && r < TAB_SIZE && c >=0 && c < TAB_SIZE) {
                    // Marca a área de efeito apenas se não for navio (para não sobrescrever navios)
                    if(board[r][c] == WATER) {
                        board[r][c] = EFFECT;
                    }
                }
            }
        }
    }
}

// Imprime o tabuleiro com legendas para visualização clara
void print_board(int board[TAB_SIZE][TAB_SIZE]) {
    printf("Tabuleiro com navios e áreas de efeito:\n");
    printf("0 = Água | 3 = Navio | 5 = Área afetada\n\n");

    for(int i=0; i<TAB_SIZE; i++) {
        for(int j=0; j<TAB_SIZE; j++) {
            printf("%d ", board[i][j]);
        }
        printf("\n");
    }
}

int main() {
    int board[TAB_SIZE][TAB_SIZE];

    // Inicializa tabuleiro
    init_board(board);

    // Posiciona navios de exemplo
    place_sample_ships(board);

    // Cria matrizes de habilidades
    int cone[SKILL_SIZE][SKILL_SIZE];
    int cross[SKILL_SIZE][SKILL_SIZE];
    int octa[SKILL_SIZE][SKILL_SIZE];

    create_cone(cone);
    create_cross(cross);
    create_octaedro(octa);

    // Define pontos de origem das habilidades no tabuleiro
    int cone_origin_row = 1, cone_origin_col = 3;
    int cross_origin_row = 7, cross_origin_col = 7;
    int octa_origin_row = 4, octa_origin_col = 5;

    // Aplica as habilidades no tabuleiro
    apply_skill(board, cone, cone_origin_row, cone_origin_col);
    apply_skill(board, cross, cross_origin_row, cross_origin_col);
    apply_skill(board, octa, octa_origin_row, octa_origin_col);

    // Exibe o tabuleiro final
    print_board(board);

    return 0;
}
