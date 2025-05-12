TARGET = main.out
CC = gcc

CFLAGS = -lSDL2 -lSDL2main

SRC = main.c

all: $(TARGET)
$(TARGET): $(SRC)
	$(CC) $(SRC) $(CFLAGS) -o $(TARGET)

clean:
	rm -f $(TARGET)

