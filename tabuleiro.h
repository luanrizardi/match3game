#ifndef _TABULEIRO_H_
#define _TABULEIRO_H_

typedef struct t_peca {
    int tipo; // 0 a 5 para representar cada tipo de peça diferente
    int x; // posição x no tabuleiro
    int y; // posição y no tabuleiro
} t_peca;

typedef struct t_jogo {
    int pontuacao;
    int nivel;
    bool leadboard;
    bool instrucoes;
    bool egg;
    bool novoNivel;
    bool menu;
    int missaoTotal;
    int missaoAtual;
    int tipoMissao;
    int qtdMissoes;
    bool jogoAcabou;
} t_jogo;

#endif