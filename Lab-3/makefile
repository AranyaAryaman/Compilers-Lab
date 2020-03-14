
# .PHONY = part1 part2
part1: clean
	flex q1.l
	gcc lex.yy.c -o part1
	# ./part1 main.c

part2: clean
	mkdir -p build
	flex q2.l
	bison q2.y
	gcc -g -c csv.c -o build/csv.o
	gcc -g -c sql_runner.c -o build/sql_runner.o
	gcc -g -c q2.tab.c -o build/q2.tab.o
	gcc -g build/*.o -o part2
	# ./part2

clean:
	rm -rf q2.tab.c q2.tab.h lex.yy.c part1 part2 output.txt build/