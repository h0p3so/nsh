CC      = cc
CFLAGS  = -Wall -Wextra -pedantic -std=c99 -Isource -Isource/common
LDFLAGS =

SRC     = source/main.c source/lex.c source/parser.c source/req.c source/builtin.c source/ext.c source/err.c \
	  source/builtin/exit.c source/builtin/echo.c source/builtin/type.c source/builtin/pwd.c source/builtin/cd.c
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
