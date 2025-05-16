TARGET = main.out
CC = gcc

CFLAGS = create_object.c -lSDL2 -lSDL2main

SRC = main.c

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(SRC) $(CFLAGS) -o $(TARGET)

clean:
	rm -f $(TARGET)

