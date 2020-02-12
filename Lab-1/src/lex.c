/* This file takes the input and breaks it down into lexemes, returning one of the enums*/
#include "lex.h"

#include "main.h"
#include "name.h"

#include <ctype.h>
#include <stdarg.h>
#include <stdio.h>
#include <string.h>

char *yytext = "";		  // Lexeme (not '\0'terminated)
char *prev_yytext = "";
int yyleng = 0;		   // Lexeme length
int prev_yyleng = 0;
int yylineno = 0;		 // Input line number
int prev_yylineno = 0;
char input_buffer[1024];
char prev_input_buffer[1024];
int lookahead = DUMMY_VAL; /* lookahead token */
int prev_lookahead = DUMMY_VAL;
int get_from_prev_buffer = 0;
int lex_orig(void);
// Get next lexeme
int lex(void) {
	static char* enum_expand[]= {
	"INVALID",
	"DUMMY",
	"EOI",		   // End of input
	"SEMI",		   // ;
	"PLUS",		   // +
	"MUL",		   // *
	"LP",		   // (
	"RP",		   // )
	"MINUS",	   // -
	"DIV",		   // /
	"LT",		   // <
	"GT",		   // >
	"EQ",		   // =
	"COL",		   // :
	"IF",		   // if
	"THEN",		   // then
	"WHILE",	   // while
	"DO",		   // do
	"BEGIN",	   // begin
	"END",		   // end,
	"NUMBER",	   // Decimal number
	"ID"		   // Identifier
}; 
	// Proxy for lex function. Stores lex debug info into lex_file
	int res = lex_orig();
	int offset = 0;
	if(yyleng % 2 == 0)
		offset = 1;
	int offset2 = 0;
	int yyleng2 = strlen(enum_expand[res]);
	if(yyleng2 % 2 == 0)
		offset2 = 1;
	if(!isprint(yytext[0])) {
		fprintf(lex_file, "<Token, ID> = <          ~          ,%*s%s%*s>\n",10 - yyleng2 / 2, "", enum_expand[res], offset2 + 10 - yyleng2 / 2, "");
	} else {
		fprintf(lex_file, "<Token, ID> = <%*s%.*s%*s,%*s%s%*s>\n",
				10 - yyleng / 2, "", yyleng, yytext, offset + 10 - yyleng / 2, "",
				10 - yyleng2 / 2, "", enum_expand[res], offset2 + 10 - yyleng2 / 2, "");
	}
	return res;
}

int lex_orig(void) {
	char *current;

	current = yytext + yyleng;		  // Skip current lexeme

	// Get the next one
	while(1) {
		while(!*current) {
			/* Get new lines, skipping any leading
			 * white space on the line,
			 * until a nonblank line is found.
			 */
			current = input_buffer;

			if(get_from_prev_buffer == 1) {
				for(int i = sizeof(prev_input_buffer) - 1; i >= 0; i--)
					input_buffer[i] = prev_input_buffer[i];
				get_from_prev_buffer = 0;
			} else {
				for(int i = sizeof(prev_input_buffer) - 1; i >= 0; i--)
					prev_input_buffer[i] = input_buffer[i];
				if(fgets(input_buffer, sizeof(input_buffer), input_file) == NULL) {
					*current = 0;
					return EOI;
				}
			}
			// printf("%s\n", input_buffer);
			++yylineno;
			while(isspace(*current))
				++current;
		}
		for(; *current; ++current) {
			/* Get the next token */
			yytext = current;
			yyleng = 1;
			switch(*current) {
				case ';': return SEMI;
				case '+': return PLUS;
				case '-': return MINUS;
				case '*': return MUL;
				case '/': return DIV;
				case '<': return LT;
				case '>': return GT;
				case '=': return EQ;
				case '(': return LP;
				case ')': return RP;
				case ':': return COL;
				case '\n':
				case '\r':
				case '\t':
				case ' ': break;
				case '\0': return EOI;
				default:
					if(!isalnum(*current))
						fprintf(stderr, "Not alphanumeric <%c>\n", *current);
					else {
						yyleng = 0;
						char buffer[1024];
						while(isalnum(*current)) {
							buffer[yyleng] = *current;
							++current;
							++yyleng;
						}
						if(strncmp("if", buffer, 2) == 0)
							return IF;
						if(strncmp("then", buffer, 4) == 0)
							return THEN;
						if(strncmp("while", buffer, 5) == 0)
							return WHILE;
						if(strncmp("do", buffer, 2) == 0)
							return DO;
						if(strncmp("begin", buffer, 5) == 0)
							return BEGIN;
						if(strncmp("end", buffer, 3) == 0)
							return END;
						if(isalpha(yytext[0]))
							return ID;
						if(yytext[0] == '_')
							return ID;
						for(int i = 0; i < yyleng; i++)
							if(!isdigit(yytext[i])) {
								fprintf(stderr, "%.*s is not a number or id\n", yyleng, yytext);
								return INVALID;
							}
						return NUMBER;
					}
					break;
			}
		}
	}
	return EOI;
}

int match(int token) {
	/* Return true if "token" matches the current lookahead symbol. */
	if(lookahead == DUMMY_VAL)
		lookahead = lex();
	return token == lookahead;
}
void advance(void) {
	/* Advance the lookahead to the next input symbol.*/
	prev_lookahead = lookahead;
	// for(int i = sizeof(prev_input_buffer) - 1; i >= 0; i--)
	// 	prev_input_buffer[i] = input_buffer[i];
	prev_yyleng = yyleng;
	prev_yylineno = yylineno;
	prev_yytext = yytext;
	lookahead = lex();
}

void revert_one(void) {
	lookahead = prev_lookahead;
	yyleng = prev_yyleng;
	yytext = prev_yytext;
	if(yylineno != prev_yylineno) {
		yylineno = prev_yylineno;
		for(int i = sizeof(prev_input_buffer) - 1; i >= 0; i--)
			input_buffer[i] = prev_input_buffer[i];
	}
	fseek(lex_file, -60L, SEEK_CUR);
}

int legal_lookahead(int first_arg, ...) {
	/* Simple error detection and recovery. Arguments are a 0-terminated list of
	 * those tokens that can legitimately come next in the input. If the list is
	 * empty, the end of file must come next. Print an error message if
	 * necessary. Error recovery is performed by discarding all input symbols
	 * until one that's in the input list is found
	 *
	 * Return true if there's no error or if we recovered from the error,
	 * false if we can't recover.
	 */

	va_list args;
	int tok;
	int lookaheads[MAXFIRST], *p = lookaheads, *current;
	int error_printed = 0;
	int rval = 0;

	va_start(args, first_arg);

	if(!first_arg) {
		if(match(EOI))
			rval = 1;
	} else {
		*p++ = first_arg;
		while((tok = va_arg(args, int)) && p < &lookaheads[MAXFIRST])
			*p++ = tok;

		while(!match(SYNCH)) {
			for(current = lookaheads; current < p; ++current)
				if(match(*current)) {
					rval = 1;
					va_end(args);
					return rval;
				}

			if(!error_printed) {
				fprintf(stderr, "Line %d: Syntax error\n", yylineno);
				error_printed = 1;
			}

			advance();
		}
	}
	va_end(args);
	return rval;
}
