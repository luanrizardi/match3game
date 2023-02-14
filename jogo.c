#include <stdio.h>
#include <stdlib.h>
#include "jogo.h"
#include "tabuleiro.h"
#include "nivel.h"


#define NUM_ASSETS 6
#define NUM_LAYERS 6
#define NUM_SOUNDS 2
#define NUM_FONTS 1
#define linhas 8
#define colunas 8

void must_init(bool test, const char *description)
{
    if(test) return;

    printf("couldn't initialize %s\n", description);
    exit(1);
}

t_allegro_vars *vars_init()
{
    t_allegro_vars *allegro_vars = malloc(sizeof(t_allegro_vars));

    if (allegro_vars == NULL)
    {
        fprintf(stderr, "erro de malloc");
        exit(1);
    }

    must_init(al_init(), "allegro");
    must_init(al_install_mouse(), "mouse");
    must_init(al_install_keyboard(), "keyboard");

    allegro_vars->timer = al_create_timer(1.0 / 60.0);
    must_init(allegro_vars->timer, "timer");

    allegro_vars->tick = al_create_timer(1.0 / 10.0);
    must_init(allegro_vars->tick, "tick");

    allegro_vars->time_limit = al_create_timer(1.0 / 1.0);
    must_init(allegro_vars->time_limit, "time_limit");

    allegro_vars->queue = al_create_event_queue();
    must_init(allegro_vars->queue, "queue");

    allegro_vars->disp = al_create_display(d_height, d_width);
    must_init(allegro_vars->disp, "display");

    al_init_font_addon();
    al_init_ttf_addon();
    
    allegro_vars->font = al_load_font("./resources/font.ttf", 50, 0);
    must_init(allegro_vars->font, "ttf");

    must_init(al_init_image_addon(), "image addon");

    // init sons
    
    must_init(al_install_audio(), "audio");
    must_init(al_init_acodec_addon(), "audio codecs");
    must_init(al_reserve_samples(16), "reserve samples");

    allegro_vars->sounds = malloc(NUM_SOUNDS * sizeof(ALLEGRO_SAMPLE *));

    if (allegro_vars->sounds == NULL)
    {
        fprintf(stderr, "erro de malloc");
        exit(1);
    }

    allegro_vars->sounds[0] = al_load_sample("./resources/floop2_x.wav");
    must_init(allegro_vars->sounds[0], "floop");
    allegro_vars->sounds[1] = al_load_sample("./resources/song.wav");
    must_init(allegro_vars->sounds[1], "song");


    // carrega assets

    allegro_vars->backgrounds = malloc(NUM_LAYERS * sizeof(ALLEGRO_BITMAP *));

    if (allegro_vars->backgrounds == NULL)
    {
        fprintf(stderr, "erro de malloc");
        exit(1);
    }

    allegro_vars->assets = malloc(NUM_ASSETS * sizeof(ALLEGRO_BITMAP *));

    if (allegro_vars->assets == NULL)
    {
        fprintf(stderr, "erro de malloc");
        exit(1);
    }

    allegro_vars->backgrounds[0] = al_load_bitmap("./resources/layers/1.png");
    must_init(allegro_vars->backgrounds[0], "1");
    allegro_vars->backgrounds[1] = al_load_bitmap("./resources/layers/2.png");
    must_init(allegro_vars->backgrounds[1], "2");
    allegro_vars->backgrounds[2] = al_load_bitmap("./resources/layers/3.png");
    must_init(allegro_vars->backgrounds[2], "3");
    allegro_vars->backgrounds[3] = al_load_bitmap("./resources/layers/4.png");
    must_init(allegro_vars->backgrounds[3], "4");
    allegro_vars->backgrounds[4] = al_load_bitmap("./resources/layers/5.png");
    must_init(allegro_vars->backgrounds[4], "5");
    allegro_vars->backgrounds[5] = al_load_bitmap("./resources/layers/6.png");
    must_init(allegro_vars->backgrounds[5], "6");

    allegro_vars->assets[0] = al_load_bitmap("./resources/sprites/PNG/simple/1.png");
    must_init(allegro_vars->assets[0], "triangulo");
    allegro_vars->assets[1] = al_load_bitmap("./resources/sprites/PNG/simple/2.png");
    must_init(allegro_vars->assets[1], "quadrado");
    allegro_vars->assets[2] = al_load_bitmap("./resources/sprites/PNG/simple/3.png");
    must_init(allegro_vars->assets[2], "circulo");
    allegro_vars->assets[3] = al_load_bitmap("./resources/sprites/PNG/simple/4.png");
    must_init(allegro_vars->assets[3], "hexagono");
    allegro_vars->assets[4] = al_load_bitmap("./resources/sprites/PNG/simple/5.png");
    must_init(allegro_vars->assets[4], "losango");
    
    al_register_event_source(allegro_vars->queue, al_get_mouse_event_source());
    al_register_event_source(allegro_vars->queue, al_get_keyboard_event_source());
    al_register_event_source(allegro_vars->queue, al_get_display_event_source(allegro_vars->disp));
    al_register_event_source(allegro_vars->queue, al_get_timer_event_source(allegro_vars->timer));
    al_register_event_source(allegro_vars->queue, al_get_timer_event_source(allegro_vars->tick));
    al_register_event_source(allegro_vars->queue, al_get_timer_event_source(allegro_vars->time_limit));

    return allegro_vars;
}


void gerar_tab(t_peca tabuleiro[8][8], t_allegro_vars *allegro_vars) {
       
    // seed the random number generator
    srand(time(NULL));
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            // assign a random type to the piece
            tabuleiro[i][j].tipo = rand() % 5;
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
}


void jogo_main_loop(t_allegro_vars *allegro_vars)
{
    bool done = false;
    bool redraw = true;

    t_jogo *jogo = NULL;
    t_peca tabuleiro[8][8];
    t_peca *pecaSelecionada = NULL;
    gerar_tab(tabuleiro, allegro_vars);
    if (!pecaSelecionada)
    {
        pecaSelecionada = malloc(sizeof(t_peca));
        if (pecaSelecionada == NULL)
        {
            fprintf(stderr, "erro de malloc");
            exit(1);
        }
        (pecaSelecionada)->x = -1;
        (pecaSelecionada)->y = -1;
    }

    if (!jogo)
    {
        jogo = malloc(sizeof(t_jogo));
        if (jogo == NULL)
        {
            fprintf(stderr, "erro de malloc");
            exit(1);
        }
        (jogo)->pontuacao = 0;
        (jogo)->nivel = 1;
    }
    int pos_x;
    int pos_y;
    ALLEGRO_EVENT event;

    al_play_sample(allegro_vars->sounds[1], 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_LOOP, NULL);
    al_start_timer(allegro_vars->timer);

    while(1)
    {
        al_wait_for_event(allegro_vars->queue, &event);

        switch(event.type)
        {
            case ALLEGRO_EVENT_TIMER:
                 // once again, no game logic. fishy? maybe.
                redraw = true;
                break;
                
            case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN:
                if(event.mouse.button & 1){
                    pos_y = event.mouse.x / 64;
                    pos_x = event.mouse.y / 64;
                    gerenciarEntrada(tabuleiro, pos_x, pos_y, pecaSelecionada, allegro_vars, jogo);
            }
            redraw = true;
            break;


            //case ALLEGRO_EVENT_KEY_DOWN:
            case ALLEGRO_EVENT_DISPLAY_CLOSE:
                done = true;
                break;
        }

        if(done)
            break;

        if(redraw && al_is_event_queue_empty(allegro_vars->queue))
        {
            //desenhar_tabuleiro
            desenhar_background(allegro_vars, jogo);
            desenharTabuleiro(tabuleiro, allegro_vars);
            al_flip_display();

            redraw = false;
        }
    }
}

void vars_destroy(t_allegro_vars *allegro_vars)
{
    for (int i = 0; i < NUM_LAYERS; i++)
        al_destroy_bitmap(allegro_vars->backgrounds[i]);
    free(allegro_vars->backgrounds);

    for (int i = 0; i < NUM_ASSETS; i++)
        al_destroy_bitmap(allegro_vars->assets[i]);

    for (int i = 0; i < NUM_SOUNDS; i++)
        al_destroy_sample(allegro_vars->sounds[i]);

    free(allegro_vars->assets);
    al_destroy_font(allegro_vars->font);
    al_destroy_display(allegro_vars->disp);
    al_destroy_timer(allegro_vars->timer);
    al_destroy_timer(allegro_vars->tick);
    al_destroy_event_queue(allegro_vars->queue);
}
