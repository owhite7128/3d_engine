SRC := $(wildcard src/*.c)
INC := $(wildcard include/*.c)
OBJ_SRC := $(SRC:.c=.o)
OBJ_INC := $(INC:.c=.o)

all: build

build: $(OBJ_SRC) $(OBJ_INC)
	$(CC) -g $^ -o build `sdl2-config --cflags --libs`

src/%.o: src/%.c
	$(CC) -c $< -o $@ `sdl2-config --cflags --libs`

include/%.o: include/%.c
	$(CC) -c $< -o $@ `sdl2-config --cflags --libs`

clean:
	rm -rf src/*.o include/*.o build