#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>

#ifndef _NIVEL_H_
#define _NIVEL_H_

void desenhar_background(t_allegro_vars *allegro_vars, t_jogo *jogo);

void show_txt(ALLEGRO_FONT *font, char *file_name);

t_peca **gerar_tab(t_jogo *jogo);

void liberar_tabuleiro(t_peca **tabuleiro);

void desenharTabuleiro(t_peca **tabuleiro, t_allegro_vars *allegro_vars, t_jogo *jogo);

void desenharAnimacao(t_peca **tabuleiro, int x, int y, int pos_x, int pos_y, int tempo_animacao, t_allegro_vars *allegro_vars, t_jogo *jogo, bool linha);

void desenharAnimacao2(t_peca **tabuleiro, int x, int y, int pos_x, int pos_y, int tempo_animacao, t_allegro_vars *allegro_vars, t_jogo *jogo);

bool verificar_vizinho(t_peca **tabuleiro, int pos_x, int pos_y, t_peca *pecaSelecionada);

void verificarCombinacao(t_peca **tabuleiro, t_allegro_vars *allegro_vars, t_jogo *jogo);

void gerenciarEntrada(t_peca **tabuleiro, int pos_x, int pos_y, t_peca *pecaSelecionada, t_allegro_vars *allegro_vars, t_jogo *jogo);

//void desenharTabuleiro(t_peca tabuleiro, t_allegro_vars *allegro_vars);

#endif