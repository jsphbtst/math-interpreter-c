CC=gcc

main: lexer.c main.c
	$(CC) lexer.c main.c -o ./main