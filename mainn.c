#include "jogo.h"

int main()
{
    t_allegro_vars *allegro_vars = vars_init();

    jogo_main_loop(allegro_vars);

    vars_destroy(allegro_vars);

    return 0;
}