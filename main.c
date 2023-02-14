#include <stdio.h>
#include <stdlib.h>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/mouse.h>

const int altura_peca = 35;
const int largura_peca = 35;

void must_init(bool test, const char *description)
{
    if(test) return;

    printf("couldn't initialize %s\n", description);
    exit(1);
}

struct Peca {
    int tipo; // 0 a 5 para representar cada tipo de peça diferente
    int x; // posição x no tabuleiro
    int y; // posição y no tabuleiro
    int estado; // 0 = normal, 1 = bomba, 2 = mais
};



enum TipoPeca {
    TRIANGULO = 0,
    QUADRILATERO,
    PENTAGONO,
    HEXAGONO,
    SETIMAGEM,
    OITAVAIMAGEM
};

enum EstadoPeca {
    NORMAL = 0,
    BOMBA,
    MAIS
};

void gerarTabuleiro(struct Peca tabuleiro[8][8]) {
    // seed the random number generator
    srand(time(NULL));
    
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            // assign a random type to the piece
            tabuleiro[i][j].tipo = rand() % 6;
            tabuleiro[i][j].x = i;
            tabuleiro[i][j].y = j;
            tabuleiro[i][j].estado = 0;
            // check for matching pieces in a row/column
            while ((i > 1 && tabuleiro[i][j].tipo == tabuleiro[i-1][j].tipo && tabuleiro[i][j].tipo == tabuleiro[i-2][j].tipo) ||
                (j > 1 && tabuleiro[i][j].tipo == tabuleiro[i][j-1].tipo && tabuleiro[i][j].tipo == tabuleiro[i][j-2].tipo)) {
                tabuleiro[i][j].tipo = rand() % 6;
            }
        }
    }
}

void desenharTabuleiro(struct Peca tabuleiro[8][8], ALLEGRO_BITMAP *triangulo, ALLEGRO_BITMAP *quadrado, ALLEGRO_BITMAP *pentagono, ALLEGRO_BITMAP *hexagono, ALLEGRO_BITMAP *setimaimagem, ALLEGRO_BITMAP *oitavaimagem) {
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            switch(tabuleiro[i][j].tipo) {
                case TRIANGULO:
                    al_draw_bitmap(triangulo, tabuleiro[i][j].x * 40, tabuleiro[i][j].y * 40, 0);
                    break;
                case QUADRILATERO:
                    al_draw_bitmap(quadrado, tabuleiro[i][j].x * 40, tabuleiro[i][j].y * 40, 0);
                    break;
                case PENTAGONO:
                    al_draw_bitmap(pentagono, tabuleiro[i][j].x * 40, tabuleiro[i][j].y * 40, 0);
                    break;
                case HEXAGONO:
                    al_draw_bitmap(hexagono, tabuleiro[i][j].x * 40, tabuleiro[i][j].y * 40, 0);
                    break;
                case SETIMAGEM:
                    al_draw_bitmap(setimaimagem, tabuleiro[i][j].x * 40, tabuleiro[i][j].y * 40, 0);
                    break;
                case OITAVAIMAGEM:
                    al_draw_bitmap(oitavaimagem, tabuleiro[i][j].x * 40, tabuleiro[i][j].y * 40, 0);
break;
            }
            //verifica se a peça tem algum estado especial
            switch(tabuleiro[i][j].estado) {
                case BOMBA:
                //desenha algo especial para indicar que a peça é uma bomba
                break;
                case MAIS:
                //desenha algo especial para indicar que a peça tem um "mais"
                break;
            }
        }
    }
}

void gerenciarEntrada(struct Peca tabuleiro[8][8]) {
    ALLEGRO_EVENT_QUEUE *event_queue = al_create_event_queue();
    must_init(event_queue, "queue");
    al_register_event_source(event_queue, al_get_mouse_event_source());

    struct Peca pecaSelecionada;
    pecaSelecionada.x = -1;
    pecaSelecionada.y = -1;
    bool done = false;
    while (!done) {
        ALLEGRO_EVENT event;
        al_wait_for_event(event_queue, &event);

        if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
            int x = event.mouse.x / 40;
            int y = event.mouse.y / 40;

            if (pecaSelecionada.x == -1 && pecaSelecionada.y == -1) {
                pecaSelecionada.x = x;
                pecaSelecionada.y = y;
            } else {
                // troca as peças de lugar
                struct Peca temp = tabuleiro[pecaSelecionada.x][pecaSelecionada.y];
                tabuleiro[pecaSelecionada.x][pecaSelecionada.y] = tabuleiro[x][y];
                tabuleiro[x][y] = temp;

                pecaSelecionada.x = -1;
                pecaSelecionada.y = -1;

            }
        }
        done = true;
    }
    al_destroy_event_queue(event_queue);
}

void verificarCombinacao(struct Peca tabuleiro[8][8], int *pontuacao) {
    //array para armazenar as peças a serem removidas
    bool remover[8][8] = {false};
    int contador = 0;

    //verifica combinações nas linhas
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (j < 6 && tabuleiro[i][j].tipo == tabuleiro[i][j + 1].tipo && tabuleiro[i][j].tipo == tabuleiro[i][j + 2].tipo) {
                remover[i][j] = true;
                remover[i][j + 1] = true;
                remover[i][j + 2] = true;
                contador += 3;
            }
        }
    }
    //verifica combinações nas colunas
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (i < 6 && tabuleiro[i][j].tipo == tabuleiro[i + 1][j].tipo  && tabuleiro[i][j].tipo == tabuleiro[i + 2][j].tipo) {
                remover[i][j] = true;
                remover[i + 1][j] = true;
                remover[i + 2][j] = true;
                contador += 3;
            }
        }
    }

    //atualiza a pontuação
    pontuacao += contador * 10;

    //remove as peças marcadas
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (remover[i][j]) {
                tabuleiro[i][j].tipo = -1;
            }
        }
    }
}

void atualizarTabuleiro(struct Peca tabuleiro[8][8], int *pontuacao) {
    //preenche as lacunas
    for (int j = 0; j < 8; j++) {
        int top = 7;
        for (int i = 7; i >= 0; i--) {
            if (tabuleiro[i][j].tipo != -1) {
                tabuleiro[top--][j] = tabuleiro[i][j];
            }
        }
        while (top >= 0) {
            tabuleiro[top--][j].tipo = rand() % 6;
        }
    }

    //verifica se há novas combinações
    verificarCombinacao(tabuleiro, pontuacao);
}

//verifica combinações nas linhas
    for (i = 0; i < 8; i++) {
        for (j = 0; j < 8; j++) {
            if (j < 6 && tabuleiro[i][j].tipo == tabuleiro[i][j + 1].tipo && tabuleiro[i][j].tipo == tabuleiro[i][j + 2].tipo) {
                int elementos = 1;
                int ite = 1;
                while(((j + ite) < 8) && (tabuleiro[i][j].tipo == tabuleiro[i][j + ite].tipo)){
                    elementos++;
                    ite++;
                }
                if(elementos >= 3){
                    match = true;
                    desenharAnimacao(tabuleiro, tabuleiro[k-1][j].x / 64, tabuleiro[k-1][j].y / 64, tabuleiro[k][j].x / 64, tabuleiro[k][j].y / 64, 10, allegro_vars, jogo);
                }
                tabuleiro[i][j].tipo = -1;
                tabuleiro[i][j + 1].tipo = -1;
                tabuleiro[i][j + 2].tipo = -1;
                al_play_sample(allegro_vars->sounds[0], 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
                for (k = i; k > 0; k--)
                {
                    desenharAnimacao(tabuleiro, tabuleiro[k-1][j].x / 64, tabuleiro[k-1][j].y / 64, tabuleiro[k][j].x / 64, tabuleiro[k][j].y / 64, 10, allegro_vars, jogo);
                    t_peca temp = tabuleiro[k][j];
                    tabuleiro[k][j] = tabuleiro[k - 1][j];
                    tabuleiro[k - 1][j] = temp;
                    desenharAnimacao(tabuleiro,tabuleiro[k - 1][j + 1].x / 64, tabuleiro[k - 1][j + 1].y / 64, tabuleiro[k][j + 1].x / 64, tabuleiro[k][j + 1].y / 64, 10, allegro_vars, jogo);
                    temp = tabuleiro[k][j + 1];
                    tabuleiro[k][j + 1] = tabuleiro[k - 1][j + 1];
                    tabuleiro[k - 1][j + 1] = temp;
                    desenharAnimacao(tabuleiro, tabuleiro[k - 1][j + 2].x / 64, tabuleiro[k - 1][j + 2].y / 64, tabuleiro[k][j + 2].x / 64, tabuleiro[k][j + 2].y / 64, 10, allegro_vars, jogo);
                    temp = tabuleiro[k][j + 2];
                    tabuleiro[k][j + 2] = tabuleiro[k - 1][j + 2];
                    tabuleiro[k - 1][j + 2] = temp;
                    
                }
                trocou = true;
                tabuleiro[0][j].tipo = rand() % 5;
                tabuleiro[0][j + 1].tipo = rand() % 5;
                tabuleiro[0][j + 2].tipo = rand() % 5;
                contador += 3;
                jogo->pontuacao += contador * 10;
                 printf("pont: %d \n", jogo->pontuacao);
                desenhar_background(allegro_vars, jogo);
                desenharTabuleiro(tabuleiro, allegro_vars);
            }
        }
    }

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
                    desenharAnimacao(tabuleiro, tabuleiro[k-3][j].x / 64, tabuleiro[k-3][j].y / 64, tabuleiro[k][j].x / 64, tabuleiro[k][j].y / 64, 15, allegro_vars, jogo);
                    t_peca temp = tabuleiro[k][j];
                    tabuleiro[k][j] = tabuleiro[k - 3][j];
                    tabuleiro[k - 3][j] = temp;
                }
                trocou = true;
                tabuleiro[0][j].tipo = rand() % 5;
                tabuleiro[1][j].tipo = rand() % 5;
                tabuleiro[2][j].tipo = rand() % 5;
                contador += 3;
                jogo->pontuacao += contador * 10;
                printf("pont: %d \n", jogo->pontuacao);
                desenhar_background(allegro_vars, jogo);
                desenharTabuleiro(tabuleiro, allegro_vars);
            }
        }
    }


int pontuacao = 0;
int main(int argc, char **argv) {
    //inicializa a biblioteca Allegro
    must_init(al_init(), "allegro");
    must_init(al_install_mouse(),"mouse");

    ALLEGRO_TIMER* timer = al_create_timer(1.0 / 30.0);
    must_init(timer, "timer");

    ALLEGRO_EVENT_QUEUE* event_queue = al_create_event_queue();
    must_init(event_queue, "queue");
    
    al_set_new_display_option(ALLEGRO_SAMPLE_BUFFERS, 1, ALLEGRO_SUGGEST);
    al_set_new_display_option(ALLEGRO_SAMPLES, 8, ALLEGRO_SUGGEST);
    al_set_new_bitmap_flags(ALLEGRO_MIN_LINEAR | ALLEGRO_MAG_LINEAR);

    ALLEGRO_DISPLAY *display = al_create_display(480, 480);
    must_init(display, "display");

    ALLEGRO_FONT* font = al_create_builtin_font();
    must_init(font, "font");
    
    //carrega as imagens das peças
    must_init(al_init_image_addon(), "image addon");
    ALLEGRO_BITMAP *triangulo = al_load_bitmap("triangulo.png");
    must_init(triangulo, "triangulo");
    ALLEGRO_BITMAP *quadrado = al_load_bitmap("quadrado.png");
    must_init(quadrado, "quadrado");
    ALLEGRO_BITMAP *pentagono = al_load_bitmap("pentagono.png");
    must_init(pentagono, "pentagono");
    ALLEGRO_BITMAP *hexagono = al_load_bitmap("hexagono.png");
    must_init(hexagono, "hexagono");
    ALLEGRO_BITMAP *heptagono = al_load_bitmap("heptagono.png");
    must_init(heptagono, "heptagono");
    ALLEGRO_BITMAP *octagono = al_load_bitmap("octagono.png");
    must_init(octagono, "octagono");

    al_register_event_source(event_queue, al_get_display_event_source(display));
    al_register_event_source(event_queue, al_get_timer_event_source(timer));
    al_register_event_source(event_queue, al_get_mouse_event_source());
    srand(time(NULL));


    //inicializa o tabuleiro
    struct Peca tabuleiro[8][8];
    gerarTabuleiro(tabuleiro);
    al_start_timer(timer);
    //loop principal do jogo
    while (true) {
        ALLEGRO_EVENT event;
        al_wait_for_event(event_queue, &event);
    

        if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
            break;
        }
        desenharTabuleiro(tabuleiro, triangulo, quadrado, pentagono, hexagono, heptagono, octagono);
        al_flip_display();

        gerenciarEntrada(tabuleiro);
        verificarCombinacao(tabuleiro, &pontuacao);
        atualizarTabuleiro(tabuleiro, &pontuacao);
        //al_clear_to_color(al_map_rgb(101, 110, 0));
        //al_draw_text(font, al_map_rgb(255, 255, 255), 0, 0, 0, "Hello world!");
        //al_flip_display();
    }
        //finaliza o jogo
    al_destroy_bitmap(triangulo);
    al_destroy_bitmap(quadrado);
    al_destroy_bitmap(pentagono);
    al_destroy_bitmap(hexagono);
    al_destroy_bitmap(heptagono);
    al_destroy_bitmap(octagono);
    al_destroy_display(display);
    al_destroy_event_queue(event_queue);

    printf("Fim de jogo! Sua pontuação foi: %d\n", pontuacao);

    return 0;
}
