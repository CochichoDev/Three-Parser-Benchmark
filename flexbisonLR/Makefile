all: flexbison

parser.tab.c parser.tab.h:	parser.y
	bison -t -v -d parser.y

lex.yy.c: lexer.l parser.tab.h
	flex lexer.l

flexbison: lex.yy.c parser.tab.c parser.tab.h code_generator.c main.c
	gcc -o flexbison main.c parser.tab.c lex.yy.c code_generator.c

clean:
	rm flexbison parser.tab.c lex.yy.c parser.tab.h parser.output
