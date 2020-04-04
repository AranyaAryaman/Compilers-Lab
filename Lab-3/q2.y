%{
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include"gc.h"
#include"str.h"
#include"sql_runner.h"

int yylex();
int yyerror(char* msg __attribute__((unused))) {}

typedef struct data_ret{
	int type;
	char *str;
}data_ret;
%}

%token SELECT PROJECT CARTPROD EQUIJOIN
%token OR AND NOT
%token QUOTED_STRING
%token EQ LT GT EXM
%token NEWLINE ENDOF
%token ID NUM
%token COMMA DOT LP RP

%type <str>			QUOTED_STRING
%type <str>			ID NUM 
%type <data>		DATA
%type <cond>		SNAN SA SN CONDITION
%type <clq_node>	COMMALIST
%union{
	char *str;
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
					// an empty line is not invalid syntax
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
					stmt_type = E_SELECT;
					tables[0] = $6;
					ast_root = $3;
};

PROJECT_RA: PROJECT LT COMMALIST GT LP ID RP {
					stmt_type = E_PROJECT;
					tables[0] = $6;
					clq_head = $3;

};

CARTPROD_RA: LP ID RP CARTPROD LP ID RP {
					stmt_type = E_CARTPROD;
					tables[0] = $2;
					tables[1] = $6;
};

EQUIJOIN_RA: LP ID RP EQUIJOIN LT ID DOT ID EQ ID DOT ID GT LP ID RP {
					stmt_type = E_EQUIJOIN;
					tables[0] = $2;
					tables[1] = $15;
					equi_tables[0] = $6;
					equi_tables[1] = $10;
					equi_id[0] = $8;
					equi_id[1] = $12;
};

COMMALIST: COMMALIST COMMA ID {
					$$ = new_clq_node();
					$$->str = $3;
					$$->next = $1;
}| ID {
					$$ = new_clq_node();
					$$->str = $1;
					$$->next = NULL;
};

SNAN: SNAN OR SA {
					$$ = new_ast_node();
					$$->operation = E_OR;
					$$->child[0] = $1;
					$$->child[1] = $3;	
}| SA {
					$$ = $1;
};

SA: SA AND SN {
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
					$$->operation = E_LT;
					$$->operand_type[0] = $1.type;
					$$->operand_type[1] = $3.type;
					$$->str[0] = $1.str;
					$$->str[1] = $3.str;
}| DATA LT EQ DATA {
					$$ = new_ast_node();
					$$->operation = E_LTEQ;
					$$->operand_type[0] = $1.type;
					$$->operand_type[1] = $4.type;
					$$->str[0] = $1.str;
					$$->str[1] = $4.str;
}| DATA EQ DATA {
					$$ = new_ast_node();
					$$->operation = E_EQ;
					$$->operand_type[0] = $1.type;
					$$->operand_type[1] = $3.type;
					$$->str[0] = $1.str;
					$$->str[1] = $3.str;
}| DATA GT DATA {
					$$ = new_ast_node();
					$$->operation = E_GT;
					$$->operand_type[0] = $1.type;
					$$->operand_type[1] = $3.type;
					$$->str[0] = $1.str;
					$$->str[1] = $3.str;
}| DATA GT EQ DATA {
					$$ = new_ast_node();
					$$->operation = E_GTEQ;
					$$->operand_type[0] = $1.type;
					$$->operand_type[1] = $4.type;
					$$->str[0] = $1.str;
					$$->str[1] = $4.str;
}| DATA LT GT DATA {
					$$ = new_ast_node();
					$$->operation = E_NEQ;
					$$->operand_type[0] = $1.type;
					$$->operand_type[1] = $4.type;
					$$->str[0] = $1.str;
					$$->str[1] = $4.str;
}| DATA EXM EQ DATA {
					$$ = new_ast_node();
					$$->operation = E_NEQ;
					$$->operand_type[0] = $1.type;
					$$->operand_type[1] = $4.type;
					$$->str[0] = $1.str;
					$$->str[1] = $4.str;
}| LP SNAN RP {
					$$ = $2;
};

DATA:ID {
					$$.type = E_VAR;
					$$.str = $1;
}| NUM {
					$$.type = E_NUM;
					$$.str = $1;
}| QUOTED_STRING {
					$$.type = E_STR;
					$$.str = $1;
};
%%

#include"lex.yy.c"

int main(int argc, char **argv) {
	argc--;argv++;
	gc_init();
	atexit(gc_destroy);
	while(1) {
		printf(">>> ");
		if(yyparse()) {
			printf("Invalid Syntax\n");
			continue;
		}
		run_sql();
	}
	return 0;
}