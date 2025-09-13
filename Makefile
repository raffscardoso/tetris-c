CC=gcc
CFLAGS=-Wall -g `sdl2-config --cflags`
LDFLAGS=`sdl2-config --libs`
EXEC=tetris

all: $(EXEC)

$(EXEC): main.o
	$(CC) -o $(EXEC) main.o $(LDFLAGS)

main.o: main.c
	$(CC) $(CFLAGS) -c main.c

clean:
	rm -f *.o $(EXEC)
