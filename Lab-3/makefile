all: 

part1:
	flex q1.l
	gcc lex.yy.c
	./a.exe main.c > out.txt

part2:
	flex q2.l
	bison q2.y
	gcc q2.tab.c
	./a.exe
	