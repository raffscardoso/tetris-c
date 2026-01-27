CC=gcc
CFLAGS=-Wall -g `sdl2-config --cflags`
LDFLAGS=`sdl2-config --libs`
EXEC=tetris

all: $(EXEC)

$(EXEC): main.o game.o sdl_handler.o font.o
	$(CC) -o $(EXEC) main.o game.o sdl_handler.o font.o $(LDFLAGS)

main.o: main.c game.h sdl_handler.h
	$(CC) $(CFLAGS) -c main.c

game.o: game.c game.h
	$(CC) $(CFLAGS) -c game.c

sdl_handler.o: sdl_handler.c sdl_handler.h game.h font.h
	$(CC) $(CFLAGS) -c sdl_handler.c

font.o: font.c font.h
	$(CC) $(CFLAGS) -c font.c

clean:
	rm -f *.o $(EXEC)
