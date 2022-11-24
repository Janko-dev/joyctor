CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -g
SRC = src/
IN = $(SRC)runtime.c $(SRC)parser.c $(SRC)lexer.c $(SRC)main.c
OUT = funcr

default:
	$(CC) $(IN) -o $(OUT) $(CFLAGS)