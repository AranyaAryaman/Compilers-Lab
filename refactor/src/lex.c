/* This file takes the input and breaks it down into lexemes, returning one of the enums*/
#include "lex.h"

#include "main.h"
#include "name.h"

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *yytext = "";		  // Lexeme (not '\0'terminated)
int yyleng   = 0;		  // Lexeme length
int yylineno = 0;		  // Input line number
int lex_orig(void);
// Get next lexeme
int lex(void) {
	// Proxy for lex function. Stores lex debug info into lex_file
	int res	= lex_orig();
	int offset = 0;
	if(yyleng % 2 == 0)
		offset = 1;
	if(!isprint(yytext[0]))
		for(int i = 0; i < yyleng; i++)
			yytext[i] = '-';
	fprintf(lex_file, "Token=<%*s%.*s%*s>,\tID=<%2d>\n", 10 - yyleng / 2, "", yyleng, yytext, offset + 10 - yyleng / 2,
			"", res);
	return res;
}
int lex_orig(void) {
	static char input_buffer[1024];
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
			if(fgets(input_buffer, sizeof(input_buffer), input_file) == NULL) {
				*current = '\0';
				return EOI;
			}

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
				case '\t':
				case ' ': break;
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
						else if(strncmp("then", buffer, 4) == 0)
							return THEN;
						else if(strncmp("while", buffer, 5) == 0)
							return WHILE;
						else if(strncmp("do", buffer, 2) == 0)
							return DO;
						else if(strncmp("begin", buffer, 5) == 0)
							return BEGIN;
						else if(strncmp("end", buffer, 3) == 0)
							return END;
						// printf("#");
						// for(int i = 0; i < yyleng; i++)
						// 	printf("=%c", buffer[i]);
						// printf("=\n");
						// TODO: Distinction between number and identifier
						return NUM_OR_ID;
					}
					break;
			}
		}
	}
}

int Lookahead = UNLEXED; /* Lookahead token  */

int match(int token) {
	/* Return true if "token" matches the
		current lookahead symbol.                */

	if(Lookahead == -1)
		Lookahead = lex();

	return token == Lookahead;
}

void advance(void) {
	/* Advance the lookahead to the next
	input symbol.                               */
	Lookahead = lex();
}