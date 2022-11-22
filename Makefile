CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -g
IN = lexer.c main.c
OUT = mexpr

default:
	$(CC) $(IN) -o $(OUT) $(CFLAGS)