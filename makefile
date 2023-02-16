SRC := $(wildcard src/*.c)
INC := $(wildcard include/*.c)
OBJ_SRC := $(SRC:.c=.o)
OBJ_INC := $(INC:.c=.o)

all: build

build: $(OBJ_SRC) $(OBJ_INC)
	$(CC) `pkg-config --cflags gtk4` -g $^ -o build -lm -ldl `pkg-config --libs gtk4`

src/%.o: src/%.c
	$(CC) `pkg-config --cflags gtk4` -c $< -o $@ -lm -ldl `pkg-config --libs gtk4`

include/%.o: include/%.c
	$(CC) `pkg-config --cflags gtk4` -c $< -o $@ -lm -ldl `pkg-config --libs gtk4`

clean:
	rm -rf src/*.o include/*.o build