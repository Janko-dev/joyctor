CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -g
IN = parser.c lexer.c main.c
OUT = funcr

default:
	$(CC) $(IN) -o $(OUT) $(CFLAGS)