#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>
#include <time.h>

#ifndef _JOGO_H_
#define _JOGO_H_

#define d_height 1280
#define d_width 720

#define image_tam 64

typedef struct t_allegro_vars {
    ALLEGRO_TIMER *timer;
    ALLEGRO_TIMER *tick;
    ALLEGRO_TIMER *time_limit;

    ALLEGRO_EVENT_QUEUE *queue;
    ALLEGRO_DISPLAY *disp;
    ALLEGRO_FONT *font;


    ALLEGRO_BITMAP **backgrounds;
    ALLEGRO_BITMAP **assets;
    ALLEGRO_SAMPLE **sounds;
} t_allegro_vars;

void must_init(bool test, const char *description);

t_allegro_vars *vars_init();

void jogo_main_loop(t_allegro_vars *allegro_vars);

void vars_destroy(t_allegro_vars *allegro_vars);


#endif