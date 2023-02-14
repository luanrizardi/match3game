#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>

#ifndef _NIVEL_H_
#define _NIVEL_H_

void desenhar_background(t_allegro_vars *allegro_vars, t_jogo *jogo);

void desenharTabuleiro(t_peca tabuleiro[8][8], t_allegro_vars *allegro_vars);

void desenharAnimacao(t_peca tabuleiro[8][8], int x, int y, int pos_x, int pos_y, int tempo_animacao, t_allegro_vars *allegro_vars, t_jogo *jogo, bool linha);

void desenharAnimacao2(t_peca tabuleiro[8][8], int x, int y, int pos_x, int pos_y, int tempo_animacao, t_allegro_vars *allegro_vars, t_jogo *jogo);

bool verificar_vizinho(t_peca tabuleiro[8][8], int pos_x, int pos_y, t_peca *pecaSelecionada);

void verificarCombinacao(t_peca tabuleiro[8][8], t_allegro_vars *allegro_vars, t_jogo *jogo);

void gerenciarEntrada(t_peca tabuleiro[8][8], int pos_x, int pos_y, t_peca *pecaSelecionada, t_allegro_vars *allegro_vars, t_jogo *jogo);

//void desenharTabuleiro(t_peca tabuleiro, t_allegro_vars *allegro_vars);

#endif