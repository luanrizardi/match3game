TARGET=program.exe
CC=gcc
ALLEGRO=C:\allegro\include
STATIC=liballegro_monolith.dll.a liballegro_font.dll.a liballegro_acodec.dll.a liballegro_audio.dll.a liballegro_primitives.dll.a liballegro_image.dll.a
LD=gcc
OBJS=jogo.o nivel.o recordes.o
all: $(OBJS)
	$(LD) -I $(ALLEGRO) mainn.c -o $(TARGET) $(OBJS)  $(STATIC)
	$(TARGET)
jogo.o: jogo.c
	$(CC) -I $(ALLEGRO) -c jogo.c -o jogo.o -Wall
nivel.o: nivel.c
	$(CC) -I $(ALLEGRO) -c nivel.c -o nivel.o -Wall
recordes.o: recordes.c
	$(CC) -I $(ALLEGRO) -c recordes.c -o recordes.o -Wall


