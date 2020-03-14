
# .PHONY = part1 part2
all: part1 part2
part1: clean
	@echo Running Flex
	@flex q1.l
	@echo Building lex.yy.c
	@gcc lex.yy.c -o part1
	@echo 'Run using "./part1 main.c"'

part2: clean
	@echo Running Flex
	@flex q2.l
	@echo Running Bison
	@bison q2.y
	@echo Building q2.tab.o
	@gcc -g q2.tab.c -o part2
	@echo Run using '"./part2"'

clean:
	@echo Cleaning
	@rm -rf q2.tab.c q2.tab.h lex.yy.c part1 part2