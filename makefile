CC      = cc
CFLAGS  = -Wall -Wextra -pedantic -std=c99 -Isource -Isource/common
LDFLAGS =

SRC     = source/main.c source/lex.c #source/post.c source/builtin.c source/builtin/exit.c source/builtin/echo.c source/builtin/type.c
OBJ     = $(SRC:.c=.o)
BIN     = nsh

all: $(BIN)

$(BIN): $(OBJ)
	$(CC) $(LDFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f $(OBJ) $(BIN)

.PHONY: all clean
