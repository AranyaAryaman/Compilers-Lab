#include "name.h"

#include "lex.h"

#include <stdio.h>
#include <stdlib.h>

// Names refer to registers(kind of).
// Biggest expression our compiler could
// parse can not have more than 8 monomials.
char *Names[] = {"t0", "t1", "t2", "t3", "t4", "t5", "t6", "t7"};
char **Namep = Names;

// Get a new name to store a procedure.
char *newname() {
	if(Namep >= &Names[sizeof(Names) / sizeof(*Names)]) {
		fprintf(stderr, "%d: Expression too complex\n", yylineno);
		exit(1);
	}
	return (*Namep++);
}

// Free a name for future use.
void freename(char *s) {
	// printf("\n==%s, %s==\n", s, *Namep);
	if(Namep > Names)
		*--Namep = s;
	else {
		fprintf(stderr, "%d: (Internal error) Name stack underflow\n", yylineno);
		exit(0);
	}
}
