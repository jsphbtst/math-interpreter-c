CC=gcc

output: lexer.o parser.o main.o
	$(CC) lexer.o parser.o main.o -o ./main

main.o: main.c
	$(CC) main.c -c -o main.o

parser.o: parser.c parser.h
	$(CC) parser.c -c -o parser.o

lexer.o: lexer.c lexer.h
	$(CC) lexer.c -c -o lexer.o

clean:
	rm -rf *.o