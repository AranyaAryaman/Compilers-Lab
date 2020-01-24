#include "main.h"

#include "code_gen.h"

FILE *input_file;
FILE *output_file;
FILE *lex_file;
void exit_func();
int main(int argc, char **argv) {
	atexit(exit_func);
	input_file  = stdin;
	lex_file	= fopen("lex.txt", "w");
	output_file = fopen("out.txt", "w");
	if(argc == 1) {
		fprintf(stderr, "No input file given, falling back to stdin\n");
	} else {
		input_file  = fopen(argv[1], "r");
		if(input_file == NULL) {
			input_file = stdin;
			fprintf(stderr, "No such file found, falling back to stdin\n");
		}
	}

	// Compile/Parse here
	statements();
	return 0;
}
void exit_func() {
	// Cleanly exit
	printf("Exiting\n");
	fclose(input_file);
	fclose(lex_file);
	fclose(output_file);
}