#include <stdio.h>
#include <stdlib.h>
#include "jogo.h"
#include "tabuleiro.h"
#include "nivel.h"
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

void desenhar_background(t_allegro_vars *allegro_vars, t_jogo *jogo){
    al_clear_to_color(al_map_rgb(255, 255, 255));
    al_draw_bitmap(allegro_vars->backgrounds[0], 0, 0, 0);
    al_draw_bitmap(allegro_vars->backgrounds[1], 0, 0, 0);
    al_draw_bitmap(allegro_vars->backgrounds[2], 0, 0, 0);
    al_draw_bitmap(allegro_vars->backgrounds[3], 0, 0, 0);
    al_draw_bitmap(allegro_vars->backgrounds[4], 0, 0, 0);
    al_draw_bitmap(allegro_vars->backgrounds[5], 0, 0, 0);
    char buffer[50];
    sprintf(buffer, "PONTUAÇÃO: %d", jogo->pontuacao);
    al_draw_text(allegro_vars->font, al_map_rgb(0, 0, 0), 900, 100, ALLEGRO_ALIGN_CENTRE, buffer);
    sprintf(buffer, "NÍVEL: %d", jogo->nivel);
    al_draw_text(allegro_vars->font, al_map_rgb(0, 0, 0), 900, 300, ALLEGRO_ALIGN_CENTRE, buffer);

}

void desenharTabuleiro(t_peca tabuleiro[8][8], t_allegro_vars *allegro_vars) {
    //srand(time(NULL));
    //int tempo = 5000;
    //int x;
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            switch(tabuleiro[i][j].tipo) {
                case 0:
                    al_draw_scaled_bitmap(allegro_vars->assets[0], 0, 0, 64, 64, tabuleiro[i][j].y, tabuleiro[i][j].x , 64, 64, 0);
                    break;
                case 1:
                    al_draw_scaled_bitmap(allegro_vars->assets[1], 0, 0, 64, 64, tabuleiro[i][j].y, tabuleiro[i][j].x , 64, 64, 0);
                    break;
                case 2:
                    al_draw_scaled_bitmap(allegro_vars->assets[2], 0, 0, 64, 64, tabuleiro[i][j].y, tabuleiro[i][j].x, 64, 64, 0);
                    break;
                case 3:
                    al_draw_scaled_bitmap(allegro_vars->assets[3], 0, 0, 64, 64, tabuleiro[i][j].y, tabuleiro[i][j].x , 64, 64, 0);
                    break;
                case 4:
                    al_draw_scaled_bitmap(allegro_vars->assets[4], 0, 0, 64, 64, tabuleiro[i][j].y, tabuleiro[i][j].x , 64, 64, 0);
                    break;
            }
        }
    }
}

void desenharAnimacao(t_peca tabuleiro[8][8], int x, int y, int pos_x, int pos_y, int tempo_animacao, t_allegro_vars *allegro_vars, t_jogo *jogo, bool linha) {
    int passo = 64 / tempo_animacao;
    //calcula a posição inicial e final de cada peça
    int x1_inicial = x * 64;
    int y1_inicial = y * 64;
    int x1_final = pos_x * 64;
    int y1_final = pos_y * 64;

    int x2_inicial = pos_x * 64;
    int y2_inicial = pos_y * 64;
    int x2_final = x * 64;
    int y2_final = y * 64;

    while (x1_inicial != x1_final || y1_inicial != y1_final || x2_inicial != x2_final || y2_inicial != y2_final ) {
    if (x1_inicial < x1_final) {
        x1_inicial += passo;
    if (x1_inicial > x1_final) {
        x1_inicial = x1_final;
    }
    }
    if (x1_inicial > x1_final) {
        x1_inicial -= passo;
    if (x1_inicial < x1_final) {
        x1_inicial = x1_final;
    }
    }
    if (y1_inicial < y1_final) {
        y1_inicial += passo;
    if (y1_inicial > y1_final) {
        y1_inicial = y1_final;
    }
    }
    if (y1_inicial > y1_final) {
        y1_inicial -= passo;
    if (x1_inicial < x1_final) {
        y1_inicial = y1_final;
    }
    }

    if(!linha){
    if (x2_inicial < x2_final) {
        x2_inicial += passo;
    if (x2_inicial > x2_final) {
        x2_inicial = x2_final;
    }
    }
    if (x2_inicial > x2_final) {
        x2_inicial -= passo;
    if (x2_inicial < x2_final) {
        x2_inicial = x2_final;
    }
    }
    if (y2_inicial < y2_final) {
        y2_inicial += passo;
    if (y2_inicial > y2_final) {
        y2_inicial = y2_final;
    }
    }
    if (y2_inicial > y2_final) {
        y2_inicial -= passo;
    if (x2_inicial < x2_final) {
        y2_inicial = y2_final;
    }
    }
        tabuleiro[pos_x][pos_y].x = x2_inicial;
        tabuleiro[pos_x][pos_y].y = y2_inicial;
    }
    
    
    //enquanto a animação não terminar
    
        tabuleiro[x][y].x = x1_inicial;
        tabuleiro[x][y].y = y1_inicial;

        desenharTabuleiro(tabuleiro, allegro_vars);
        //atualiza a tela
        al_flip_display();
        desenhar_background(allegro_vars, jogo);
    }
}

void desenharAnimacao2(t_peca tabuleiro[8][8], int x, int y, int pos_x, int pos_y, int tempo_animacao, t_allegro_vars *allegro_vars, t_jogo *jogo) {
    int passo = 64 / tempo_animacao;
    //calcula a posição inicial e final de cada peça
    int x1_inicial = x;
    int y1_inicial = y;
    int x1_final = pos_x;
    int y1_final = pos_y;

    while (x1_inicial != x1_final || y1_inicial != y1_final ) {
    if (x1_inicial < x1_final) {
        x1_inicial += passo;
    if (x1_inicial > x1_final) {
        x1_inicial = x1_final;
    }
    }
    if (x1_inicial > x1_final) {
        x1_inicial -= passo;
    if (x1_inicial < x1_final) {
        x1_inicial = x1_final;
    }
    }
    if (y1_inicial < y1_final) {
        y1_inicial += passo;
    if (y1_inicial > y1_final) {
        y1_inicial = y1_final;
    }
    }
    if (y1_inicial > y1_final) {
        y1_inicial -= passo;
    if (x1_inicial < x1_final) {
        y1_inicial = y1_final;
    }
    }
    
    //enquanto a animação não terminar
    
        tabuleiro[x / 64][y / 64].x = x1_inicial;
        tabuleiro[x / 64][y / 64].y = y1_inicial;

        desenharTabuleiro(tabuleiro, allegro_vars);
        //atualiza a tela
        al_flip_display();
        desenhar_background(allegro_vars, jogo);
    }
}

bool verificar_vizinho(t_peca tabuleiro[8][8], int pos_x, int pos_y, t_peca *pecaSelecionada){
    bool match = false;
    t_peca temp = tabuleiro[pecaSelecionada->x][pecaSelecionada->y];
    tabuleiro[pecaSelecionada->x][pecaSelecionada->y] = tabuleiro[pos_x][pos_y];
    tabuleiro[pos_x][pos_y] = temp;

    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (i < 6 && tabuleiro[i][j].tipo == tabuleiro[i + 1][j].tipo  && tabuleiro[i][j].tipo == tabuleiro[i + 2][j].tipo) {
                match = true;
            }
        }
    }
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (j < 6 && tabuleiro[i][j].tipo == tabuleiro[i][j + 1].tipo  && tabuleiro[i][j].tipo == tabuleiro[i][j + 2].tipo) {
                match = true;
            }
        }
    }

    temp = tabuleiro[pos_x][pos_y];
    tabuleiro[pos_x][pos_y] = tabuleiro[pecaSelecionada->x][pecaSelecionada->y];
    tabuleiro[pecaSelecionada->x][pecaSelecionada->y] = temp;

    if( ((pos_x == pecaSelecionada->x - 1 && pos_y == pecaSelecionada->y) || (pos_x == pecaSelecionada->x + 1 && pos_y == pecaSelecionada->y) || (pos_x == pecaSelecionada->x && pos_y == pecaSelecionada->y - 1) || (pos_x == pecaSelecionada->x && pos_y == pecaSelecionada->y + 1)) && (match))
        return 1;
    else
        return 0;
}

void verificarCombinacao(t_peca tabuleiro[8][8], t_allegro_vars *allegro_vars, t_jogo *jogo) {
    bool trocou = false;
    int contador = 0;
    srand(time(NULL));
    int i, j, k;
    bool linha = false;
    //verifica combinações nas linhas
    for (i = 0; i < 8; i++) {
        for (j = 0; j < 8; j++) {
            if (j < 6 && tabuleiro[i][j].tipo == tabuleiro[i][j + 1].tipo && tabuleiro[i][j].tipo == tabuleiro[i][j + 2].tipo) {
                tabuleiro[i][j].tipo = -1;
                tabuleiro[i][j + 1].tipo = -1;
                tabuleiro[i][j + 2].tipo = -1;
                al_play_sample(allegro_vars->sounds[0], 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
                for (k = i; k > 0; k--)
                {
                    desenharAnimacao(tabuleiro, tabuleiro[k-1][j].x / 64, tabuleiro[k-1][j].y / 64, tabuleiro[k][j].x / 64, tabuleiro[k][j].y / 64, 10, allegro_vars, jogo, linha);
                    t_peca temp = tabuleiro[k][j];
                    tabuleiro[k][j] = tabuleiro[k - 1][j];
                    tabuleiro[k - 1][j] = temp;
                    desenharAnimacao(tabuleiro,tabuleiro[k - 1][j + 1].x / 64, tabuleiro[k - 1][j + 1].y / 64, tabuleiro[k][j + 1].x / 64, tabuleiro[k][j + 1].y / 64, 10, allegro_vars, jogo, linha);
                    temp = tabuleiro[k][j + 1];
                    tabuleiro[k][j + 1] = tabuleiro[k - 1][j + 1];
                    tabuleiro[k - 1][j + 1] = temp;
                    desenharAnimacao(tabuleiro, tabuleiro[k - 1][j + 2].x / 64, tabuleiro[k - 1][j + 2].y / 64, tabuleiro[k][j + 2].x / 64, tabuleiro[k][j + 2].y / 64, 10, allegro_vars, jogo, linha);
                    temp = tabuleiro[k][j + 2];
                    tabuleiro[k][j + 2] = tabuleiro[k - 1][j + 2];
                    tabuleiro[k - 1][j + 2] = temp;
                    
                }
                trocou = true;
                linha = true;
                for (k = j; k <= j + 2; k++)
                {
                    tabuleiro[0][k].x = tabuleiro[0][k].x - 35;
                    tabuleiro[0][k].tipo = rand() % 5;
                    desenharAnimacao2(tabuleiro, tabuleiro[0][k].x, tabuleiro[0][k].y, (tabuleiro[0][k].x + 35), tabuleiro[0][k].y , 10, allegro_vars, jogo);
                }
                linha = false;
                contador += 3;
                jogo->pontuacao += contador * 10;
                desenhar_background(allegro_vars, jogo);
                desenharTabuleiro(tabuleiro, allegro_vars);
            }
        }
    }
    //verifica combinações nas colunas
    for (j = 0; j < 8; j++) {
        //int vazios = 0;
        for (i = 8 - 1; i >= 0; i--) {
            if (i > 1 && tabuleiro[i][j].tipo == tabuleiro[i - 1][j].tipo  && tabuleiro[i][j].tipo == tabuleiro[i - 2][j].tipo) {
                tabuleiro[i][j].tipo = -1;
                tabuleiro[i - 1][j].tipo = -1;
                tabuleiro[i - 2][j].tipo = -1;
                al_play_sample(allegro_vars->sounds[0], 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
                for (k = i; k > 2; k--)
                {
                    desenharAnimacao(tabuleiro, tabuleiro[k-3][j].x / 64, tabuleiro[k-3][j].y / 64, tabuleiro[k][j].x / 64, tabuleiro[k][j].y / 64, 15, allegro_vars, jogo, false);
                    t_peca temp = tabuleiro[k][j];
                    tabuleiro[k][j] = tabuleiro[k - 3][j];
                    tabuleiro[k - 3][j] = temp;
                }
                trocou = true;
                for (k = 2; k >=0; k--)
                {
                    //tabuleiro[k][j].x = tabuleiro[k][j].x;
                    tabuleiro[k][j].tipo = rand() % 5;
                    //desenharAnimacao2(tabuleiro, tabuleiro[k][j].x, tabuleiro[k][j].y, (tabuleiro[k][j].x + 35 * k), tabuleiro[k][j].y , 1, allegro_vars, jogo);
                }
                contador += 3;
                jogo->pontuacao += contador * 10;
                desenhar_background(allegro_vars, jogo);
                desenharTabuleiro(tabuleiro, allegro_vars);
            }
        }
    }


    if(trocou)
        verificarCombinacao(tabuleiro, allegro_vars, jogo);
    else
        return;
    
}


void gerenciarEntrada(t_peca tabuleiro[8][8], int pos_x, int pos_y, t_peca *pecaSelecionada, t_allegro_vars *allegro_vars, t_jogo *jogo) {
            
            if(pos_x > 7 || pos_y > 7 || pos_x < 0 || pos_y < 0)
                return;
            if (pecaSelecionada->x == -1 && pecaSelecionada->y == -1) {
                pecaSelecionada->x = pos_x;
                pecaSelecionada->y = pos_y;
            } else {
                // troca as peças de lugar
                if(verificar_vizinho(tabuleiro, pos_x, pos_y, pecaSelecionada)){
                desenharAnimacao(tabuleiro,pecaSelecionada->x, pecaSelecionada->y, pos_x, pos_y, 10, allegro_vars, jogo, false);
                t_peca temp = tabuleiro[pecaSelecionada->x][pecaSelecionada->y];
                tabuleiro[pecaSelecionada->x][pecaSelecionada->y] = tabuleiro[pos_x][pos_y];
                tabuleiro[pos_x][pos_y] = temp;

                //al_play_sample(allegro_vars->sounds[0], 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
                verificarCombinacao(tabuleiro, allegro_vars, jogo);

                pecaSelecionada->x = -1;
                pecaSelecionada->y = -1;
                
               
               }else{
                pecaSelecionada->x = -1;
                pecaSelecionada->y = -1;
            }
            }
}