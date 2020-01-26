#include "code_gen.h"

#include "lex.h"
#include "main.h"
#include "name.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
int label_count = 0;
void statement(void);
char *expression(void);
char *non_relational(void);
char *monomial(void);
char *factor(void);
void debug(char *str) {
	assert(str != NULL);
	// fprintf(stderr, "%s\n", str);
}
void start(void) {
	// start		->	statement+
	if(input_filename != NULL && match(EOI)) {
		err("FILE <%s> IS EMPTY\n", input_filename);
	}
	fprintf(output_file, ".global _start\n");
	fprintf(output_file, ".section\n.text\n\n");
	fprintf(output_file, "_start:\n");
	while(!match(EOI)) {
		statement();
	}
	fprintf(output_file, "\tHLT\n");
}
void statement(void) {
	debug("ENTER statement");
	// statement ->		expression() SEMI
	//				|	ID COL EQ expression() SEMI
	//				|	IF expression() THEN statement()
	//				|	WHILE expression() DO statement()
	//				|	BEGIN statement* END
	char *tempvar, *tempvar2;

	if(match(IF)) {
		advance();
		tempvar = expression();
		fprintf(output_file, "\tCMP %s, 0\n", tempvar);
		label_count++;
		int temp_label = label_count;
		fprintf(output_file, "\tJE L%d\n", temp_label);
		if(match(THEN)) {
			advance();
			statement();
			fprintf(output_file, "L%d:\n", temp_label);
		} else {
			err("THEN clause not found%s", "\n");
		}
		freename(tempvar);
	} else if(match(WHILE)) {
		advance();
		label_count++;
		int temp_label = label_count;
		label_count++;
		int temp_label2 = label_count;
		fprintf(output_file, "L%d:\n", temp_label);
		tempvar = expression();
		fprintf(output_file, "\tCMP %s, 0\n", tempvar);
		fprintf(output_file, "\tJE L%d\n", temp_label2);
		if(match(DO)) {
			advance();
			statement();
			fprintf(output_file, "\tJMP L%d\n", temp_label);
			fprintf(output_file, "L%d:\n", temp_label2);
		} else {
			err("Line %d:DO clause not found\n", yylineno);
		}
		freename(tempvar);
	} else if(match(BEGIN)) {
		advance();
		while(!match(END) && !match(EOI)) {
			statement();
		}
		if(match(END)) {
			advance();
		} else {
			err("Line %d:No END clause found\n", yylineno);
		}
	} else if(match(ID)) {
		char tempvar_arr[1024];
		strncpy(tempvar_arr, yytext, yyleng);
		tempvar_arr[yyleng] = 0;
		advance();
		if(match(COL)) {
			advance();
			if(match(EQ)) {
				advance();
				tempvar2 = expression();
				fprintf(output_file, "\tMOV %s, %s\n", tempvar_arr, tempvar2);
				if(match(SEMI))
					advance();
				else {
					err("Line %d: Missing semicolon\n", yylineno);
				}
			} else {
				err("Line %d: Assignment operator expected", yylineno);
			}
		} else {
			err("Line %d: Assignment operator expected", yylineno);
		}
		freename(tempvar2);
	} else {
		tempvar = expression();
		if(match(SEMI))
			advance();
		else {
			err("Line %d: Missing semicolon\n", yylineno);
		}
		freename(tempvar);
	}
	debug("EXIT statement");
}
char *expression(void) {
	debug("ENTER expression");
	// expression ->	non_relational
	//				|	non_relational EQ non_relational
	//				|	non_relational GT non_relational
	//				|	non_relational LT non_relational
	char *tempvar, *tempvar2;

	tempvar = non_relational();
	if(match(EQ)) {
		advance();
		tempvar2 = non_relational();
		fprintf(output_file, "\tCMP %s, %s\n", tempvar, tempvar2);
		fprintf(output_file, "\tSETZ %s\n", tempvar);
		freename(tempvar2);
	} else if(match(LT)) {
		advance();
		tempvar2 = non_relational();
		fprintf(output_file, "\tCMP %s, %s\n", tempvar, tempvar2);
		fprintf(output_file, "\tSETL %s\n", tempvar);
		freename(tempvar2);
	} else if(match(GT)) {
		advance();
		tempvar2 = non_relational();
		fprintf(output_file, "\tCMP %s, %s\n", tempvar, tempvar2);
		fprintf(output_file, "\tSETG %s\n", tempvar);
		freename(tempvar2);
	}
	debug("EXIT expression");
	return tempvar;
}
char *non_relational(void) {
	debug("ENTER non_relational");
	// non_relational	->	monomial + non_relational
	//					|	monomial - non_relational
	//					|	monomial
	char *tempvar, *tempvar2;

	tempvar = monomial();
	if(match(PLUS)) {
		advance();
		tempvar2 = non_relational();
		fprintf(output_file, "\tADD %s, %s\n", tempvar, tempvar2);
		freename(tempvar2);
	} else if(match(MINUS)) {
		advance();
		tempvar2 = non_relational();
		fprintf(output_file, "\tSUB %s, %s\n", tempvar, tempvar2);
		freename(tempvar2);
	}
	debug("EXIT non_relational");
	return tempvar;
}
char *monomial(void) {
	debug("ENTER monomial");
	// monomial ->		factor MUL monomial
	//				|	factor DIV monomial
	//				|	factor
	char *tempvar, *tempvar2;
	tempvar = factor();
	if(match(MUL)) {
		advance();
		tempvar2 = monomial();
		fprintf(output_file, "\tMUL %s, %s\n", tempvar, tempvar2);
		freename(tempvar2);
	} else if(match(DIV)) {
		advance();
		tempvar2 = monomial();
		fprintf(output_file, "\tDIV %s, %s\n", tempvar, tempvar2);
		freename(tempvar2);
	}
	debug("EXIT monomial");
	return tempvar;
}
char *factor(void) {
	debug("ENTER factor");
	char *tempvar;

	if(match(NUMBER) || match(ID)) {
		/* Print the assignment instruction. The %0.*s conversion is a form of
		 * %X.Ys, where X is the field width and Y is the maximum number of
		 * characters that will be printed (even if the string is longer). I'm
		 * using the %0.*s to print the string because it's not \0 terminated.
		 * The field has a default width of 0, but it will grow the size needed
		 * to print the string. The ".*" tells printf() to take the maximum-
		 * number-of-characters count from the next argument (yyleng).
		 */

		// printf("\t%s = %.*s\n", tempvar = newname(), yyleng, yytext);
		fprintf(output_file, "\tMOV %s, %.*s\n", tempvar = newname(), yyleng, yytext);
		advance();
	} else if(match(LP)) {
		advance();
		tempvar = non_relational();
		if(match(RP)) {
			advance();
		} else {
			err("Line %d: Mismatched parenthesis\n", yylineno);
		}
	} else {
		err("Line %d: Number or identifier expected\n", yylineno);
	}
	debug("EXIT factor");
	return tempvar;
}
