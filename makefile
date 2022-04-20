SRC := $(wildcard src/*.c)
INC := $(wildcard include/*.c)
OBJ_SRC := $(SRC:.c=.o)
OBJ_INC := $(INC:.c=.o)

all: build

build: $(OBJ_SRC) $(OBJ_INC)
	$(CC) `pkg-config --cflags gtk4 glib-2.0` -g $^ -o build -lglut -lGL -lGLU -lGLEW -lm -ldl `pkg-config --libs gtk4 glib-2.0`

src/%.o: src/%.c
	$(CC) `pkg-config --cflags gtk4 glib-2.0` -c $< -o $@ -lglut -lGL -lGLU -lGLEW -lm -ldl `pkg-config --libs gtk4 glib-2.0`

include/%.o: include/%.c
	$(CC) `pkg-config --cflags gtk4 glib-2.0` -c $< -o $@ -lglut -lGL -lGLU -lGLEW -lm -ldl `pkg-config --libs gtk4 glib-2.0`

clean:
	rm -rf src/*.o include/*.o build