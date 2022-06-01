CC = clang

PNAME = c

SRC  = $(shell find src -name "*.c")
OBJ  = $(SRC:.c=.o)
BIN = build

EXEC = $(BIN)/$(PNAME)
INCFLAGS  = -Isrc/

CCFLAGS += $(INCFLAGS)
CCFLAGS += -O0
CCFLAGS += -Wall

LDFLAGS  = $(INCFLAGS)
LDFLAGS += -lncurses

all: build

run: build
	$(BIN)/c $*

build: $(OBJ)
	$(CC) $(CCFLAGS) -ggdb -o $(BIN)/c $(filter %.o,$^) $(LDFLAGS)

clean:
	rm $(BIN)/* $(OBJ)

%.o: %.c
	$(CC) -ggdb -o $@ -c $< $(CCFLAGS)

$(BIN):
	mkdir -p $(BIN)

