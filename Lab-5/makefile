all:
	bison -d parser.y
	flex lexer.l
	gcc -o compiler parser.tab.c lex.yy.c
	rm lex.yy.c parser.tab.c
