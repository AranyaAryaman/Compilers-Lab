all: 

part1:
	flex q1_1.l
	gcc lex.yy.c
	./a.exe main.c 1 > pass1.txt
	flex q1_2.l
	gcc lex.yy.c
	./a.exe pass1.txt

part2:
	flex -i q2.l
	bison -d q2.y
	gcc q2.tab.c
	./a.exe
	