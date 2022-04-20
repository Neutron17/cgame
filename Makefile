CC = gcc

PNAME = c

SRC  = $(shell find src -name "*.c")
OBJ  = $(SRC:.c=.o)
BIN = build

EXEC = $(BIN)/$(PNAME)
INCFLAGS  = -Isrc/
INCFLAGS += -Isrc/lib/ctor/include

CCFLAGS += $(INCFLAGS)


LDFLAGS  = $(INCFLAGS)
# LDFLAGS += -lstdc++
LDFLAGS += -Lsrc/lib/ctor
# LDFLAGS += -larrCtor

all: build

run: build
	$(BIN)/c $*

build: $(OBJ)
	$(CC) -ggdb --std=gnu18 -o $(BIN)/c $(filter %.o,$^) $(LDFLAGS)

clean:
	rm $(BIN)/* $(OBJ)

%.o: %.c
	$(CC) -ggdb --std=gnu18 -o $@ -c $< $(CCFLAGS)
