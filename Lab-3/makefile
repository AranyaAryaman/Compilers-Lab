
# .PHONY = part1 part2
all: part1 part2
part1: clean
	@echo Running Flex
	@flex q1.l
	@echo Building lex.yy.c
	@gcc lex.yy.c -o part1
	@echo 'Run using "./part1 main.c"'

part2: clean
	@echo Creating build directory
	@mkdir -p build
	@echo Running Flex
	@flex q2.l
	@echo Running Bison
	@bison q2.y
	@echo Building q2.tab.o
	@gcc -g -c q2.tab.c -o build/q2.tab.o
	@echo Building csv.o
	@gcc -g -c csv.c -o build/csv.o
	@echo Building sql_runner.o
	@gcc -g -c sql_runner.c -o build/sql_runner.o
	@echo Linking everything...
	@gcc -g build/*.o -o part2
	@echo Run using '"./part2"'

clean:
	@echo Cleaning...
	@rm -rf q2.tab.c q2.tab.h lex.yy.c part1 part2 output.txt build/