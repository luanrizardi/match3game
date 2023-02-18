#include <stdio.h>
#include <stdlib.h>
#include "jogo.h"
#include "tabuleiro.h"
#include "nivel.h"
#include "recordes.h"

#define NUM_ASSETS 6
#define NUM_LAYERS 18
#define NUM_SOUNDS 3
#define NUM_FONTS 1
#define linhas 8
#define colunas 8
#define pontNivel 1000

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

    allegro_vars->queue = al_create_event_queue();
    must_init(allegro_vars->queue, "queue");

    allegro_vars->disp = al_create_display(d_height, d_width);
    must_init(allegro_vars->disp, "display");

    al_init_font_addon();
    al_init_ttf_addon();
    
    /* allegro_vars->font = al_load_font("./resources/font.ttf", 20, 0);
    must_init(allegro_vars->font, "ttf"); */

    allegro_vars->font = al_create_builtin_font();
    must_init(allegro_vars->font, "font");

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
    allegro_vars->sounds[2] = al_load_sample("./resources/levelup.wav");
    must_init(allegro_vars->sounds[2], "levelup");


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
    allegro_vars->backgrounds[6] = al_load_bitmap("./resources/layers2/1.png");
    must_init(allegro_vars->backgrounds[6], "7");
    allegro_vars->backgrounds[7] = al_load_bitmap("./resources/layers2/2.png");
    must_init(allegro_vars->backgrounds[7], "8");
    allegro_vars->backgrounds[8] = al_load_bitmap("./resources/layers2/3.png");
    must_init(allegro_vars->backgrounds[8], "9");
    allegro_vars->backgrounds[9] = al_load_bitmap("./resources/layers2/4.png");
    must_init(allegro_vars->backgrounds[9], "10");
    allegro_vars->backgrounds[10] = al_load_bitmap("./resources/layers2/5.png");
    must_init(allegro_vars->backgrounds[10], "11");
    allegro_vars->backgrounds[11] = al_load_bitmap("./resources/layers2/6.png");
    must_init(allegro_vars->backgrounds[11], "12");
    allegro_vars->backgrounds[12] = al_load_bitmap("./resources/layers3/1.png");
    must_init(allegro_vars->backgrounds[12], "13");
    allegro_vars->backgrounds[13] = al_load_bitmap("./resources/layers3/2.png");
    must_init(allegro_vars->backgrounds[13], "14");
    allegro_vars->backgrounds[14] = al_load_bitmap("./resources/layers3/3.png");
    must_init(allegro_vars->backgrounds[14], "15");
    allegro_vars->backgrounds[15] = al_load_bitmap("./resources/layers3/4.png");
    must_init(allegro_vars->backgrounds[15], "16");
    allegro_vars->backgrounds[16] = al_load_bitmap("./resources/layers3/5.png");
    must_init(allegro_vars->backgrounds[16], "17");
    allegro_vars->backgrounds[17] = al_load_bitmap("./resources/layers3/6.png");
    must_init(allegro_vars->backgrounds[17], "18");

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
    allegro_vars->assets[5] = al_load_bitmap("./resources/sprites/PNG/simple/6.png");
    must_init(allegro_vars->assets[5], "pentagono");
    
    al_register_event_source(allegro_vars->queue, al_get_mouse_event_source());
    al_register_event_source(allegro_vars->queue, al_get_keyboard_event_source());
    al_register_event_source(allegro_vars->queue, al_get_display_event_source(allegro_vars->disp));
    al_register_event_source(allegro_vars->queue, al_get_timer_event_source(allegro_vars->timer));

    return allegro_vars;
}

t_peca *alocarPeca(){
    t_peca *pecaSelecionada = NULL;
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
    return pecaSelecionada;
}

t_jogo *alocarJogo(){
    t_jogo *jogo = NULL;
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
        (jogo)->leadboard = false;
        (jogo)->instrucoes = false;
        (jogo)->egg = false;
        (jogo)->novoNivel = false;
        (jogo)->menu = true;
        (jogo)->missaoTotal = 6;
        (jogo)->missaoAtual = 0;
        (jogo)->tipoMissao = -1;
        (jogo)->qtdMissoes = 0;
        (jogo)->jogoAcabou = false;
    }
    return jogo;
}

void jogo_main_loop(t_allegro_vars *allegro_vars)
{
    bool done = false;
    bool redraw = true;
    t_jogo *jogo = NULL;
    t_peca **tabuleiro;
    t_peca *pecaSelecionada = NULL;
    pecaSelecionada = alocarPeca();
    jogo = alocarJogo();
    tabuleiro = gerar_tab(jogo);
    int pos_x;
    int pos_y;
    ALLEGRO_EVENT event;

    unsigned char key[ALLEGRO_KEY_MAX];
    memset(key, 0, sizeof(key));

    al_play_sample(allegro_vars->sounds[1], 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_LOOP, NULL);
    al_start_timer(allegro_vars->timer);

    while(1)
    {
        al_wait_for_event(allegro_vars->queue, &event);

        switch(event.type)
        {
            case ALLEGRO_EVENT_TIMER:

                if (jogo->pontuacao > pontNivel * jogo->nivel && jogo->nivel < 3)
                {
                    jogo->nivel++;
                    al_play_sample(allegro_vars->sounds[2], 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
                    if(jogo->nivel == 3)
                        criarMissao(jogo);
                    tabuleiro = gerar_tab(jogo);
                    jogo->novoNivel = true;
                }
                if(jogo->missaoAtual >= jogo->missaoTotal){
                    jogo->pontuacao += 100;
                    criarMissao(jogo);
                    jogo->missaoAtual = 0;
                    jogo->qtdMissoes++;
                }
                if(jogo->qtdMissoes == 3){
                    save_recordes(jogo->pontuacao);
                    jogo->jogoAcabou = true;
                    jogo->qtdMissoes++;
                    
                }
                redraw = true;
                break;

            case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN:
                if(jogo->instrucoes || jogo->leadboard || jogo->novoNivel || jogo->menu){
                    jogo->leadboard = false;
                    jogo->instrucoes = false;
                    jogo->novoNivel = false;
                    jogo->menu = false;
                }else if(event.mouse.button & 1){
                    pos_y = event.mouse.x / 64;
                    pos_x = event.mouse.y / 64;
                    gerenciarEntrada(tabuleiro, pos_x, pos_y, pecaSelecionada, allegro_vars, jogo);
            }
            redraw = true;
            break;
            
            case ALLEGRO_EVENT_KEY_DOWN:
                if(event.keyboard.keycode == ALLEGRO_KEY_L){
                    jogo->leadboard = true;
                }
                if(event.keyboard.keycode == ALLEGRO_KEY_H || event.keyboard.keycode == ALLEGRO_KEY_F1)
                    jogo->instrucoes = true;
                if(event.keyboard.keycode == ALLEGRO_KEY_E)
                    jogo->egg = true;
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
            desenharTabuleiro(tabuleiro, allegro_vars, jogo);
            redraw = false;
        }
    }
    liberar_tabuleiro(tabuleiro);
    free(jogo);
    free(pecaSelecionada);
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
    al_destroy_event_queue(allegro_vars->queue);
}
