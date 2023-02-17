#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "jogo.h"
#include "tabuleiro.h"
#include "nivel.h"
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

void desenhar_background(t_allegro_vars *allegro_vars, t_jogo *jogo){
    if(jogo->nivel == 1){
    al_clear_to_color(al_map_rgb(255, 255, 255));
    al_draw_bitmap(allegro_vars->backgrounds[0], 0, 0, 0);
    al_draw_bitmap(allegro_vars->backgrounds[1], 0, 0, 0);
    al_draw_bitmap(allegro_vars->backgrounds[2], 0, 0, 0);
    al_draw_bitmap(allegro_vars->backgrounds[3], 0, 0, 0);
    al_draw_bitmap(allegro_vars->backgrounds[4], 0, 0, 0);
    al_draw_bitmap(allegro_vars->backgrounds[5], 0, 0, 0);
   }
    else if(jogo->nivel == 2){
    al_clear_to_color(al_map_rgb(255, 255, 255));
    al_draw_bitmap(allegro_vars->backgrounds[6], 0, 0, 0);
    al_draw_bitmap(allegro_vars->backgrounds[7], 0, 0, 0);
    al_draw_bitmap(allegro_vars->backgrounds[8], 0, 0, 0);
    al_draw_bitmap(allegro_vars->backgrounds[9], 0, 0, 0);
    al_draw_bitmap(allegro_vars->backgrounds[10], 0, 0, 0);
    al_draw_bitmap(allegro_vars->backgrounds[11], 0, 0, 0);
    }
    else if(jogo->nivel == 3){
    al_clear_to_color(al_map_rgb(255, 255, 255));
    al_draw_bitmap(allegro_vars->backgrounds[12], 0, 0, 0);
    al_draw_bitmap(allegro_vars->backgrounds[13], 0, 0, 0);
    al_draw_bitmap(allegro_vars->backgrounds[14], 0, 0, 0);
    al_draw_bitmap(allegro_vars->backgrounds[15], 0, 0, 0);
    al_draw_bitmap(allegro_vars->backgrounds[16], 0, 0, 0);
    al_draw_bitmap(allegro_vars->backgrounds[17], 0, 0, 0);
    }
    
    char buffer[50];
    sprintf(buffer, "PONTUAÇÃO: %d", jogo->pontuacao);
    al_draw_text(allegro_vars->font, al_map_rgb(0, 0, 0), 900, 100, ALLEGRO_ALIGN_CENTRE, buffer);
    sprintf(buffer, "NÍVEL: %d", jogo->nivel);
    al_draw_text(allegro_vars->font, al_map_rgb(0, 0, 0), 900, 300, ALLEGRO_ALIGN_CENTRE, buffer);
}

void show_txt(ALLEGRO_FONT *font, char *file_name)
{
    int i = 5;
    char str[1024];
    FILE *txt_file = fopen(file_name, "r");

    if (txt_file == NULL)
        fprintf(stderr, "nao foi possivel abrir %s", file_name);

    al_clear_to_color(al_map_rgb(173, 216, 230));
    while (!feof(txt_file))
    {
        fgets(str, 1024, txt_file);
        al_draw_text(font, al_map_rgb(0, 0, 0), 100, i + 100, 0, str);
        i += 45;
    }
    al_draw_text(font, al_map_rgb(0, 0, 0), 100, i + 100, 0, "Clique para continuar o jogo!");
    fclose(txt_file);
}

t_peca **gerar_tab(t_jogo *jogo) {
    t_peca **tabuleiro = (t_peca**) malloc(8 * sizeof(t_peca*));  
    // seed the random number generator
    srand(time(NULL));
    for (int i = 0; i < 8; i++) {
        tabuleiro[i] = (t_peca*) malloc(8 * sizeof(t_peca));
        for (int j = 0; j < 8; j++) {
            // assign a random type to the piece
            if(jogo->nivel == 1)
            tabuleiro[i][j].tipo = rand() % 5;
            else
            tabuleiro[i][j].tipo = rand() % 6;
            tabuleiro[i][j].x = i * 64;
            tabuleiro[i][j].y = j * 64;
            tabuleiro[i][j].estado = 0;
            // check for matching pieces in a row/column
            while ((i > 1 && tabuleiro[i][j].tipo == tabuleiro[i-1][j].tipo && tabuleiro[i][j].tipo == tabuleiro[i-2][j].tipo) ||
                (j > 1 && tabuleiro[i][j].tipo == tabuleiro[i][j-1].tipo && tabuleiro[i][j].tipo == tabuleiro[i][j-2].tipo)) {
                tabuleiro[i][j].tipo = rand() % 5;
            }
        }
    }
    return tabuleiro;
}

// libera a memória alocada para um tabuleiro 8x8 do tipo t_peca **
void liberar_tabuleiro(t_peca **tabuleiro) {
    for (int i = 0; i < 8; i++) {
        free(tabuleiro[i]);
    }
    free(tabuleiro);
}

void desenharTabuleiro(t_peca **tabuleiro, t_allegro_vars *allegro_vars, t_jogo *jogo) {

    if (jogo->leadboard)
        show_txt(allegro_vars->font, "records.txt");
    else if(jogo->instrucoes)
        show_txt(allegro_vars->font, "instrucoes.txt");
    else if(jogo->novoNivel){
        show_txt(allegro_vars->font, "nivel.txt");
        tabuleiro = gerar_tab(jogo);
    }
    else{
    desenhar_background(allegro_vars, jogo);
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
                case 5:
                    al_draw_scaled_bitmap(allegro_vars->assets[5], 0, 0, 64, 64, tabuleiro[i][j].y, tabuleiro[i][j].x , 64, 64, 0);
                break;
            }
        }
    }
    }
    al_flip_display();
}

void desenharAnimacao(t_peca **tabuleiro, int x, int y, int pos_x, int pos_y, int tempo_animacao, t_allegro_vars *allegro_vars, t_jogo *jogo, bool linha) {
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

        desenharTabuleiro(tabuleiro, allegro_vars, jogo);
    }
}

void desenharAnimacao2(t_peca **tabuleiro, int x, int y, int pos_x, int pos_y, int tempo_animacao, t_allegro_vars *allegro_vars, t_jogo *jogo) {
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

        desenharTabuleiro(tabuleiro, allegro_vars, jogo);
    }
}

bool verificar_vizinho(t_peca **tabuleiro, int pos_x, int pos_y, t_peca *pecaSelecionada){
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

void verificarCombinacao(t_peca **tabuleiro, t_allegro_vars *allegro_vars, t_jogo *jogo) {
    bool trocou = false;
    int contador = 0;
    srand(time(NULL));
    int i, j, k, z, elementos, ite, aux;
    bool linha = false;
    t_peca temp;
    //verifica combinações nas linhas
    for (i = 0; i < 8; i++) {
        for (j = 0; j < 6; j++) {
             elementos = 1;
            ite = 1;
            while(((j + ite) < 8) && (tabuleiro[i][j].tipo == tabuleiro[i][j + ite].tipo)){
                elementos++;
                ite++;
            }
            if(elementos>= 3){
                aux = j + ite;
                for (k = j; k < aux; k++){
                    printf("i: %d, k: %d \n", i, k);
                    tabuleiro[i][k].tipo = -1;
                }
                
                al_play_sample(allegro_vars->sounds[0], 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
                for (k = i; k > 0; k--){
                    aux = j + ite;
                    for (z = j; z < aux; z++)
                    {
                        desenharAnimacao(tabuleiro, tabuleiro[k - 1][z].x / 64, tabuleiro[k - 1][z].y / 64, tabuleiro[k][z].x / 64, tabuleiro[k][z].y / 64, 10, allegro_vars, jogo, linha);
                        temp = tabuleiro[k][z];
                        tabuleiro[k][z] = tabuleiro[k - 1][z];
                        tabuleiro[k - 1][z] = temp;
                        }
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
                if(jogo->egg)
                    jogo->pontuacao += contador * 20;
                else
                    jogo->pontuacao += contador * 10;
                desenharTabuleiro(tabuleiro, allegro_vars, jogo);
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
                    desenharAnimacao(tabuleiro, tabuleiro[k-3][j].x / 64, tabuleiro[k-3][j].y / 64, tabuleiro[k][j].x / 64, tabuleiro[k][j].y / 64, 32, allegro_vars, jogo, false);
                    t_peca temp = tabuleiro[k][j];
                    tabuleiro[k][j] = tabuleiro[k - 3][j];
                    tabuleiro[k - 3][j] = temp;
                }
                trocou = true;
                for (k = 2; k >=0; k--)
                {
                    //tabuleiro[k][j].x = tabuleiro[k][j].x;
                    if(jogo->nivel == 1)
                    tabuleiro[k][j].tipo = rand() % 5;
                    else
                    tabuleiro[k][j].tipo = rand() %6;
                    //desenharAnimacao2(tabuleiro, tabuleiro[k][j].x, tabuleiro[k][j].y, (tabuleiro[k][j].x + 35 * k), tabuleiro[k][j].y , 1, allegro_vars, jogo);
                }
                contador += 3;
                jogo->pontuacao += contador * 10;
                desenharTabuleiro(tabuleiro, allegro_vars, jogo);
            }
        }
    }


    if(trocou)
        verificarCombinacao(tabuleiro, allegro_vars, jogo);
    else
        return;
    
}


void gerenciarEntrada(t_peca **tabuleiro, int pos_x, int pos_y, t_peca *pecaSelecionada, t_allegro_vars *allegro_vars, t_jogo *jogo) {
            
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