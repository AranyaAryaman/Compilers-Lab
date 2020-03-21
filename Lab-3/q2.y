%{
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include"gc.h"
#include"sql_runner.h"

int yylex();
int yyerror(char* msg __attribute__((unused))) {}

typedef struct data_ret{
	int type;
	char str[MAX_STRLEN];
	int num;
}data_ret;
/*
WARNING: For now, we would not focus on malloc errors, and assume it will never fail.
On another note, FUCK UNIONS... Let's put "EVERYTHING" in a struct and use only those
members which we want and ignore all others. Who the fuck cares about optimization!!!

""""""""""""PREMATURE ABSTRACTION IS THE ROOT OF ALL EVIL""""""""""""
*/
%}

%token SELECT PROJECT CARTPROD EQUIJOIN
%token OR AND NOT
%token SINGLE_QUOTE DOUBLE_QUOTE
%token EQ LT GT EXM
%token NEWLINE ENDOF
%token ID NUM
%token COMMA DOT LP RP

%type <str>			ID
%type <num>			NUM
%type <data>		DATA
%type <cond>		SNAN SA SN CONDITION
%type <clq_node>	COMMALIST
%union{
	char str[25];
	int num;
	data_ret data;
	ast* cond; 
	clq *clq_node;
}
%start S1
%%
S1: CARTPROD_RA DELIM	{
					YYACCEPT;
}| PROJECT_RA DELIM {
					YYACCEPT;
}| SELECT_RA DELIM {
					YYACCEPT;
}| EQUIJOIN_RA DELIM {
					YYACCEPT;
}| NEWLINE {
					// an empty line is not invalid sntac
					YYACCEPT;
}| ENDOF {
					// Safely exit on Ctrl+D
					// Ctrl+D passes <<EOF>> to stdin,
					// indicating that stream will be closed
					printf("Exit...\n");
					exit(0);
}| error DELIM {
					// Panic mode for REPL, skip to next newline
					YYABORT;
};
DELIM: NEWLINE | ENDOF;
SELECT_RA: SELECT LT SNAN GT LP ID RP {
					stmt_type=E_SELECT;
					strncpy(tables[0], $6, MAX_STRLEN);
					ast_root = $3;
};

PROJECT_RA: PROJECT LT COMMALIST GT LP ID RP {
					stmt_type = E_PROJECT;
					strncpy(tables[0], $6, MAX_STRLEN);
					clq_head = $3;

};

CARTPROD_RA: LP ID RP CARTPROD LP ID RP {
					stmt_type=E_CARTPROD;
					strncpy(tables[0], $2, MAX_STRLEN);
					strncpy(tables[1], $6, MAX_STRLEN);
};

EQUIJOIN_RA: LP ID RP EQUIJOIN LT ID DOT ID EQ ID DOT ID GT LP ID RP {
					stmt_type=E_EQUIJOIN;
					strncpy(tables[0], $2, MAX_STRLEN);
					strncpy(tables[1], $15, MAX_STRLEN);
					strncpy(equi_tables[0], $6, MAX_STRLEN);
					strncpy(equi_tables[1], $10, MAX_STRLEN);
					strncpy(equi_id[0], $8, MAX_STRLEN);
					strncpy(equi_id[1], $12, MAX_STRLEN);
};

COMMALIST: COMMALIST COMMA ID {
					$$ = new_clq_node();
					strncpy($$->str, $3, MAX_STRLEN);
					$$->next = $1;
}| ID {
					$$ = new_clq_node();
					strncpy($$->str, $1, MAX_STRLEN);
					$$->next = NULL;
};

SNAN: SA OR SA {
					$$ = new_ast_node();
					$$->operation = E_OR;
					$$->child[0] = $1;
					$$->child[1] = $3;	
}| SA {
					$$ = $1;
};

SA: SN AND SN {
					$$ = new_ast_node();
					$$->operation = E_AND;
					$$->child[0] = $1;
					$$->child[1] = $3;
}| SN {
					$$ = $1;
};

SN: CONDITION {
					$$ = $1;
}| NOT CONDITION{
					$$ = new_ast_node();
					$$->operation = E_NOT;
					$$->child[0] = $2;
};

CONDITION: DATA LT DATA {
					$$ = new_ast_node();
					$$->operation=E_LT;
					$$->operand_type[0] = $1.type;
					$$->operand_type[1] = $3.type;
					strncpy($$->str[0], $1.str, MAX_STRLEN);
					strncpy($$->str[1], $3.str, MAX_STRLEN);
					$$->num[0] = $1.num;
					$$->num[1] = $3.num;
}| DATA LT EQ DATA {
					$$ = new_ast_node();
					$$->operation=E_LTEQ;
					$$->operand_type[0] = $1.type;
					$$->operand_type[1] = $4.type;
					strncpy($$->str[0], $1.str, MAX_STRLEN);
					strncpy($$->str[1], $4.str, MAX_STRLEN);
					$$->num[0] = $1.num;
					$$->num[1] = $4.num;
}| DATA EQ DATA {
					$$ = new_ast_node();
					$$->operation=E_EQ;
					$$->operand_type[0] = $1.type;
					$$->operand_type[1] = $3.type;
					strncpy($$->str[0], $1.str, MAX_STRLEN);
					strncpy($$->str[1], $3.str, MAX_STRLEN);
					$$->num[0] = $1.num;
					$$->num[1] = $3.num;
}| DATA GT DATA {
					$$ = new_ast_node();
					$$->operation=E_GT;
					$$->operand_type[0] = $1.type;
					$$->operand_type[1] = $3.type;
					strncpy($$->str[0], $1.str, MAX_STRLEN);
					strncpy($$->str[1], $3.str, MAX_STRLEN);
					$$->num[0] = $1.num;
					$$->num[1] = $3.num;
}| DATA GT EQ DATA {
					$$ = new_ast_node();
					$$->operation=E_GTEQ;
					$$->operand_type[0] = $1.type;
					$$->operand_type[1] = $4.type;
					strncpy($$->str[0], $1.str, MAX_STRLEN);
					strncpy($$->str[1], $4.str, MAX_STRLEN);
					$$->num[0] = $1.num;
					$$->num[1] = $4.num;
}| DATA LT GT DATA {
					$$ = new_ast_node();
					$$->operation=E_NEQ;
					$$->operand_type[0] = $1.type;
					$$->operand_type[1] = $4.type;
					strncpy($$->str[0], $1.str, MAX_STRLEN);
					strncpy($$->str[1], $4.str, MAX_STRLEN);
					$$->num[0] = $1.num;
					$$->num[1] = $4.num;
}| DATA EXM EQ DATA {
					$$ = new_ast_node();
					$$->operation=E_NEQ;
					$$->operand_type[0] = $1.type;
					$$->operand_type[1] = $4.type;
					strncpy($$->str[0], $1.str, MAX_STRLEN);
					strncpy($$->str[1], $4.str, MAX_STRLEN);
					$$->num[0] = $1.num;
					$$->num[1] = $4.num;
}| LP SNAN RP {
					$$ = $2;
};

DATA:ID {
					$$.type=E_VAR;
					strncpy($$.str, $1, MAX_STRLEN);
}| NUM {
					$$.type=E_INT;
					$$.num=$1;
}| SINGLE_QUOTE ID SINGLE_QUOTE {
					$$.type=E_STR;
					strncpy($$.str, $2, MAX_STRLEN);
}| DOUBLE_QUOTE ID DOUBLE_QUOTE {
					$$.type=E_STR;
					strncpy($$.str, $2, MAX_STRLEN);
};
%%

#include"lex.yy.c"

int main(int argc, char **argv) {
	argc--;argv++;
	gc_init();
	while(1) {
		init_ds();
		printf(">>> ");
		if(yyparse()) {
			printf("Invalid Syntax\n");
			continue;
		}
		printf("Valid Syntax\n");
		run_sql();
	}
	return 0;
}