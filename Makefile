CC=gcc
CFLAGS=-Wall -g `sdl2-config --cflags`
LDFLAGS=`sdl2-config --libs`
EXEC=tetris

all: $(EXEC)

$(EXEC): main.o game.o sdl_handler.o
	$(CC) -o $(EXEC) main.o game.o sdl_handler.o $(LDFLAGS)

main.o: main.c
	$(CC) $(CFLAGS) -c main.c

game.o: game.c
	$(CC) $(CFLAGS) -c game.c

sdl_handler.o: sdl_handler.c
	$(CC) $(CFLAGS) -c sdl_handler.c

clean:
	rm -f *.o $(EXEC)
