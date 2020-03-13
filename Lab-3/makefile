
.PHONY = part1 part2
part1:
	flex q1.l
	gcc lex.yy.c -o a.out
	./a.out main.c

part2:
	flex -i q2.l
	bison -d q2.y
	gcc q2.tab.c -o a.out
	./a.out
	