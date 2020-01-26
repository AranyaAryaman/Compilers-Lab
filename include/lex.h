#ifndef _LEX_
#define _LEX_

#define MAXFIRST 16
#define SYNCH SEMI

enum {
	INVALID,
	UNLEXED,
	EOI,		   // End of input
	SEMI,		   // ;
	PLUS,		   // +
	MUL,		   // *
	LP,			   // (
	RP,			   // )
	MINUS,		   // -
	DIV,		   // /
	LT,			   // <
	GT,			   // >
	EQ,			   // =
	COL,		   // :
	IF,			   // if
	THEN,		   // then
	WHILE,		   // while
	DO,			   // do
	BEGIN,		   // begin
	END,		   // end,
	NUMBER,		   // Decimal number
	ID			   // Identifier
};

extern char *yytext;
extern int yyleng;
extern int yylineno;
extern int Lookahead;

int lex(void);
int match(int token);
int legal_lookahead(int first_arg, ...);
void advance(void);

#endif
