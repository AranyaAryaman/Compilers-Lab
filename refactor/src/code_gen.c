#include "code_gen.h"

#include "lex.h"
#include "main.h"
#include "name.h"

#include <stdio.h>
#include <stdlib.h>
int label_count = 0;
char *statements(void);
char *expression(void);
char *non_relational(void);
char *minomial(void);
char *term(void);
char *factor(void);

char *statements(void) {
	// statements ->    expression SEMI
	//              |   expression SEMI statements
	//              |   id COL EQ expression SEMI
	//              |   id COL EQ expression SEMI statements
	//              |   if expression then statements
	//              |   while expression do statements
	//              |   begin opt_statements end
	//              |   begin opt_statements end statements
	char *tempvar, *tempvar2;

	while(!match(EOI)) {
		if(match(IF)) {
			advance();
			tempvar = expression();
			printf("\tCMP %s\n", tempvar);
			label_count++;
			printf("\tJNZ LABEL%d\n", label_count);
			if(match(THEN)) {
				advance();
				tempvar2 = statements();
				printf("LABEL%d:\n", label_count);
			}
			freename(tempvar2);
		}

		else if(match(WHILE)) {
			advance();
			tempvar = expression();
			if(match(DO)) {
				advance();
				tempvar2 = statements();
			}
			// printf("WE HAVE REACHED THE ENDGAME");
			freename(tempvar2);
		} else {
			tempvar = expression();
		}
		if(match(SEMI))
			advance();
		else
			fprintf(stderr, "%d: Inserting missing semicolon in statements\n", yylineno);
		freename(tempvar);
	}
	return "STATEMENT_RETURN";
}
char *monomial(void) {
	// monomial ->      factor MUL monomial
	//              |   factor DIV monomial
	//              |   factor
	char *tempvar, *tempvar2;
	tempvar = factor();
	while(match(MUL) || match(DIV)) {
		char temp;
		if(match(MUL))
			temp = '*';
		else
			temp = '/';
		advance();
		tempvar2 = monomial();
		printf("\t%s %c= %s\n", tempvar, temp, tempvar2);
		freename(tempvar2);
	}
	return tempvar;
}
char *non_relational(void) {
	char *tempvar, *tempvar2;
	tempvar = monomial();
	// non_relational ->    non_relational + monomial
	//                  |   non_relational - monomial
	//                  |   monomial
	while(match(PLUS) || match(MINUS)) {
		char temp;
		if(match(PLUS))
			temp = '+';
		else
			temp = '-';
		advance();
		tempvar2 = non_relational();
		printf("\t%s %c= %s\n", tempvar, temp, tempvar2);
		freename(tempvar2);
	}
	return tempvar;
}
char *expression(void) {
	// expression ->    non_relational
	//              |   non_relational EQ non_relational
	//              |   non_relational GT non_relational
	//              |   non_relational LT non_relational

	char *tempvar, *tempvar2;

	tempvar = non_relational();
	while(match(EQ)) {
		advance();
		tempvar2 = non_relational();
		printf("\t%s == %s\n", tempvar, tempvar2);
		freename(tempvar2);
	}
	while(match(LT)) {
		advance();
		tempvar2 = non_relational();
		printf("\t%s <= %s\n", tempvar, tempvar2);
		freename(tempvar2);
	}
	while(match(GT)) {
		advance();
		tempvar2 = non_relational();
		printf("\t%s >= %s\n", tempvar, tempvar2);
		freename(tempvar2);
	}

	return tempvar;
}
char *term(void) {
	char *tempvar, *tempvar2;

	tempvar = factor();
	while(match(MUL)) {
		advance();
		tempvar2 = factor();
		printf("\t%s *= %s\n", tempvar, tempvar2);
		freename(tempvar2);
	}

	return tempvar;
}
char *factor(void) {
	char *tempvar;

	if(match(NUM_OR_ID)) {
		/* Print the assignment instruction. The %0.*s conversion is a form of
		 * %X.Ys, where X is the field width and Y is the maximum number of
		 * characters that will be printed (even if the string is longer). I'm
		 * using the %0.*s to print the string because it's not \0 terminated.
		 * The field has a default width of 0, but it will grow the size needed
		 * to print the string. The ".*" tells printf() to take the maximum-
		 * number-of-characters count from the next argument (yyleng).
		 */

		printf("\t%s = %.*s\n", tempvar = newname(), yyleng, yytext);
		advance();
	} else if(match(LP)) {
		advance();
		tempvar = non_relational();
		if(match(RP))
			advance();
		else
			fprintf(stderr, "%d: Mismatched parenthesis\n", yylineno);
	} else
		fprintf(stderr, "%d: Number or identifier expected\n", yylineno);

	return tempvar;
}