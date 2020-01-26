#include "code_gen.h"

#include "lex.h"
#include "main.h"
#include "name.h"

#include <stdio.h>
#include <stdlib.h>
int label_count = 0;
char *statement(void);
char *expression(void);
char *non_relational(void);
char *monomial(void);
char *term(void);
char *factor(void);
void debug(char *str) {
	// fprintf(stderr, "%s\n", str);
}
void start(void) {
	// start		->	statement
	if(match(EOI))
		err("FILE <%s> IS EMPTY\n", input_filename);
	while(!match(EOI)) {
		statement();
	}
	printf("NOP\n");
}
char *statement(void) {
	debug("ENTER statement");
	// statement ->		expression SEMI
	//				|	expression SEMI statement
	//				|	id COL EQ expression SEMI
	//				|	id COL EQ expression SEMI statement
	//				|	if expression then statement
	//				|	while expression do statement
	//				|	begin opt_statements end
	//				|	begin opt_statements end statement
	char *tempvar, *tempvar2;

	if(match(IF)) {
		advance();
		tempvar = expression();
		printf("\tCMP %s, 0\n", tempvar);
		label_count++;
		int temp_label = label_count;
		printf("\tJE L%d\n", temp_label);
		if(match(THEN)) {
			advance();
			statement();
			printf("L%d:\n", temp_label);
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
		printf("L%d:\n", temp_label);
		tempvar = expression();
		printf("\tCMP %s, 0\n", tempvar);
		printf("\tJE L%d\n", temp_label2);
		if(match(DO)) {
			advance();
			statement();
			printf("\nJMP L%d\n", temp_label);
			printf("L%d:\n", temp_label2);
		} else {
			err("Line %d:DO clause not found\n", yylineno);
		}
		freename(tempvar);
		// } else if(match(BEGIN)) {
		// 	advance();
		// 	tempvar = opt_statements();			// TODO
		// 	if(match(END)) {
		// 		advance();
		// 		tempvar2 = statements();
		// 	}
		// 	freename(tempvar2);
		//  freename(tempvar);
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
				printf("\tMOV %s, %s\n", tempvar_arr, tempvar2);
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
	return "STATEMENT_RETURN";
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
		printf("\t%s == %s\n", tempvar, tempvar2);
		freename(tempvar2);
	} else if(match(LT)) {
		advance();
		tempvar2 = non_relational();
		printf("\t%s <= %s\n", tempvar, tempvar2);
		freename(tempvar2);
	} else if(match(GT)) {
		advance();
		tempvar2 = non_relational();
		printf("\t%s >= %s\n", tempvar, tempvar2);
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
	if(match(PLUS) || match(MINUS)) {
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
	debug("EXIT monomial");
	return tempvar;
}
char *term(void) {
	debug("ENTER term");
	char *tempvar, *tempvar2;

	tempvar = factor();
	while(match(MUL)) {
		advance();
		tempvar2 = factor();
		printf("\t%s *= %s\n", tempvar, tempvar2);
		freename(tempvar2);
	}
	debug("EXIT term");
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
		printf("\tMOV %s, %.*s\n", tempvar = newname(), yyleng, yytext);
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
