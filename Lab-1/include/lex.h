#ifndef _LEX_
#define _LEX_

#define MAXFIRST 16
#define SYNCH SEMI

enum {
	INVALID,
	DUMMY_VAL,
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
extern char *prev_yytext;
extern int yyleng;
extern int prev_yyleng;
extern int yylineno;
extern int prev_yylineno;
extern int lookahead;
extern int prev_lookahead;
extern char input_buffer[1024];
extern char prev_input_buffer[1024];

extern int get_from_prev_buffer;
int lex(void);
int match(int token);
int legal_lookahead(int first_arg, ...);
void advance(void);
void revert_one(void);
#endif
