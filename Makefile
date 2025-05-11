CC = gcc
CFLAGS = -Iinclude
SRC = src/main.c src/world.c src/player.c src/npc.c src/input.c src/item.c src/save_load.c 
OBJ = $(SRC:.c=.o)

main: $(OBJ)
	$(CC) -o main $(OBJ)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	del /Q src\*.o main.exe
