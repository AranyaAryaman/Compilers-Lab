#include "main.h"

#include "code_gen.h"

#include <stdarg.h>

FILE *input_file;
FILE *output_file;
FILE *lex_file;
char *input_filename;
void exit_func();
int main(int argc, char **argv) {
	atexit(exit_func);
	input_filename = NULL;
	input_file = stdin;
	lex_file = fopen("lex.txt", "w");
	output_file = stdout;
	if(argc == 1) {
		fprintf(stderr, "No input file given, falling back to stdin\n");
	} else {
		input_file = fopen(argv[1], "r");
		if(input_file == NULL) {
			input_file = stdin;
			output_file = stdout;
			fprintf(stderr, "No such file found, falling back to stdin\n");
		} else {
			input_filename = argv[1];
			output_file = fopen("out.s", "w");
		}
	}

	// Compile/Parse here
	start();
	return 0;
}
void exit_func() {
	// Cleanly exit
	fclose(input_file);
	fclose(lex_file);
	fclose(output_file);
}
void err(char *str, ...) {
	va_list args;
	va_start(args, str);
	vfprintf(stderr, str, args);
	va_end(args);
	exit(0);
}
