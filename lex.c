#include "lex.h"
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

char *yytext = ""; /* Lexeme (not '\0'
							 terminated)              */
int yyleng = 0;	/* Lexeme length.           */
int yylineno = 0;  /* Input line number        */

int lex(void)
{

	static char input_buffer[1024];
	char *current;

	current = yytext + yyleng; /* Skip current
											lexeme        */

	while (1)
	{ /* Get the next one         */
		while (!*current)
		{
			/* Get new lines, skipping any leading
			* white space on the line,
			* until a nonblank line is found.
			*/

			current = input_buffer;
			if (!gets(input_buffer))
			{
				*current = '\0';

				return EOI;
			}
			++yylineno;
			while (isspace(*current))
				++current;
		}
		for (; *current; ++current)
		{
			/* Get the next token */
			yytext = current;
			yyleng = 1;
			switch (*current)
			{
				case ';':
					return SEMI;
				case '+':
					return PLUS;
				case '-':
					return MINUS;
				case '*':
					return MUL;
				case '/':
					return DIV;
				case '<':
					return LT;
				case '>':
					return GT;
				case '=':
					return EQ;
				case '(':
					return LP;
				case ')':
					return RP;
				case ':':
					return COL;
				case '\n':
				case '\t':
				case ' ':
					break;
				default:
					if (!isalnum(*current))
						fprintf(stderr, "Not alphanumeric <%c>\n", *current);
					else
					{
						yyleng = 0;
						char buffer[100];
						while (isalnum(*current))
						{
							buffer[yyleng] = *current;
							++current;
							++yyleng;
						}
						buffer[yyleng] = 0;
						//printf("%s\n",buffer);
						if (strcmp("if", buffer)==0)
							return IF;
						else if (strcmp("then", buffer)==0)
							return THEN;
						else if (strcmp("while", buffer)==0)
							return WHILE;
						else if (strcmp("do", buffer)==0)
							return DO;
						else if (strcmp("begin", buffer)==0)
							return BEGIN;
						else if (strcmp("end", buffer)==0)
							return END;
						return NUM_OR_ID;						
					}
					break;
			}
		}
	}
}

static int Lookahead = -1; /* Lookahead token  */

int match(int token)
{
	/* Return true if "token" matches the
		current lookahead symbol.                */

	if (Lookahead == -1)
		Lookahead = lex();

	return token == Lookahead;
}

void advance(void)
{
	/* Advance the lookahead to the next
	input symbol.                               */

	Lookahead = lex();
}
