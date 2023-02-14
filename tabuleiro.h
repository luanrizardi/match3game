#ifndef _TABULEIRO_H_
#define _TABULEIRO_H_

typedef struct t_peca {
    int tipo; // 0 a 5 para representar cada tipo de peça diferente
    int x; // posição x no tabuleiro
    int y; // posição y no tabuleiro
    int estado; // 0 = normal, 1 = bomba, 2 = mais
} t_peca;

typedef struct t_jogo {
    int pontuacao;
    int nivel;
} t_jogo;

/*enum TipoPeca {
    TRIANGULO = 0,
    QUADRADO,
    CIRCULO,
    HEXAGONO,
    LOSANGO,
};*/

/*enum EstadoPeca {
    NORMAL = 0,
    BOMBA,
    MAIS
};*/

//void gerarTabuleiro(struct Peca tabuleiro[8][8]);

#endif