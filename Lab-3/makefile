all:
	lex q2.l
	bison -tv -d q2.y
	gcc -Wall -Wextra -g q2.tab.c lex.yy.c -lfl -ly -DYYDEBUG -D_XOPEN_SOURCE=700
