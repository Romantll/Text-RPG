CC = gcc
CFLAGS = -Iinclude
SRC = src/main.c src/world.c src/player.c src/npc.c
OBJ = $(SRC:.c=.o)

main: $(OBJ)
	$(CC) -o main $(OBJ)

clean:
	del /Q src\*.o main.exe
