
# .PHONY = part1 part2
part1: clean
	flex q1.l
	gcc lex.yy.c -o part1
	# ./part1 main.c

part2: clean
	flex q2.l
	bison q2.y
	gcc q2.tab.c -o part2
	# ./part2

clean:
	rm -f q2.tab.c q2.tab.h lex.yy.c part1 part2 output.txt