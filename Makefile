CC=gcc

output: lexer.o parser.o main.o
	$(CC) lexer.o parser.o main.o -o ./main

main.o: main.c
	$(CC) main.c -c -o main.o

parser.o: parser/parser.c parser/parser.h
	$(CC) parser/parser.c -c -o parser.o

lexer.o: lexer/lexer.c lexer/lexer.h
	$(CC) lexer/lexer.c -c -o lexer.o

clean:
	rm -rf *.o