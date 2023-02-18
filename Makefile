CFLAGS = -Wall -std=c99

allegro_deps = -lallegro -lallegro_font -lallegro_image -lallegro_audio -lallegro_acodec -lallegro_primitives

common_o = jogo.o nivel.o recordes.o

all:
	gcc ${CFLAGS} -c jogo.c -o jogo.o
	gcc ${CFLAGS} -c nivel.c -o nivel.o
	gcc ${CFLAGS} -c recordes.c -o recordes.o
	gcc ${CFLAGS} ${common_o} mainn.c ${allegro_deps} -o jewels

clean:
	-rm -f *~ *.o

purge:
	-rm -f jewels
	-rm -f recordes.txt

