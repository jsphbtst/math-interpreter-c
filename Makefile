CC=gcc

main: lexer.c parser.c main.c
	$(CC) lexer.c parser.c main.c -o ./main