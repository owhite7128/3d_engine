SRC := $(wildcard src/*.c)
INC := $(wildcard include/*.c)
OBJ_SRC := $(SRC:.c=.o)
OBJ_INC := $(INC:.c=.o)

LDLIBS := $(shell sdl2-config --cflags --libs) -lm

all: build

build: $(OBJ_SRC) $(OBJ_INC)
	$(CC) -g $^ -o build $(LDLIBS)

src/%.o: src/%.c
	$(CC) -c $< -o $@

include/%.o: include/%.c
	$(CC) -c $< -o $@

clean:
	rm -rf src/*.o include/*.o build
