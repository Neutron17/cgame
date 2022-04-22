CC = clang

PNAME = c

SRC  = $(shell find src -name "*.c")
OBJ  = $(SRC:.c=.o)
BIN = build

EXEC = $(BIN)/$(PNAME)
INCFLAGS  = -Isrc/

CCFLAGS += $(INCFLAGS)
CCFLAGS += -Ofast
#CCFLAGS += -fblocks
#CCFLAGS += -s
#CCFLAGS += -ffast-math
#CCFLAGS += -nostartfiles
#CCFLAGS += -nodefaultlibs

LDFLAGS  = $(INCFLAGS)
#LDFLAGS += -lBlocksRuntime

all: build

run: build
	$(BIN)/c $*

build: $(OBJ)
	$(CC) $(CCFLAGS) -ggdb -o $(BIN)/c $(filter %.o,$^) $(LDFLAGS)

clean:
	rm $(BIN)/* $(OBJ)

%.o: %.c
	$(CC) -ggdb -o $@ -c $< $(CCFLAGS)
