%{
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int yylex();
int yyerror(char* msg __attribute__((unused))) {}
#include"sql_runner.h"
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

%token SELECT PROJECT CARTPROD EQUIJOIN OR AND EQ COMMA ID NUM LP RP LT GT DOT NEWLINE SINGLE_QUOTE DOUBLE_QUOTE EXM NOT ENDOF
%type <str>			ID
%type <num>			NUM
%type <data>		DATA
%type <cond>		SNAN SA SN CONDITION
%union{
	char str[25];
	int num;
	data_ret data;
	condition_ast* cond; 
}
%start S1
%%
S1: CARTPROD_RA NEWLINE	{
					YYACCEPT;
}| PROJECT_RA NEWLINE {
					YYACCEPT;
}| SELECT_RA NEWLINE {
					YYACCEPT;
}| EQUIJOIN_RA NEWLINE {
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
}| error NEWLINE {
					// Panic mode for REPL, skip to next newline
					YYABORT;
};

SELECT_RA: SELECT LT SNAN GT LP ID RP {
					stmt_type=E_SELECT;
					strncpy(tables[0], $6, MAX_STRLEN);
					ast = $3;
};

PROJECT_RA: PROJECT LT S3 GT LP ID RP {
					stmt_type = E_PROJECT;
					strncpy(tables[0], $6, MAX_STRLEN);
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

S3: S3 COMMA ID {
					strncpy(cols[col_num], $3, MAX_STRLEN);
					col_num++;
}| ID {
					strncpy(cols[col_num], $1, MAX_STRLEN);
					col_num++;
};

SNAN: SA OR SA {
					$$ = new_node();
					$$->operation = E_OR;
					$$->child[0] = $1;
					$$->child[1] = $3;	
}| SA {
					$$ = $1;
};

SA: SN AND SN {
					$$ = new_node();
					$$->operation = E_AND;
					$$->child[0] = $1;
					$$->child[1] = $3;
}| SN {
					$$ = $1;
};

SN: CONDITION {
					$$ = $1;
}| NOT CONDITION{
					$$ = new_node();
					$$->operation = E_NOT;
					$$->child[0] = $2;
};

CONDITION: DATA LT DATA {
					$$ = new_node();
					$$->operation=E_LT;
					$$->operand_type[0] = $1.type;
					$$->operand_type[1] = $3.type;
					strncpy($$->str[0], $1.str, MAX_STRLEN);
					strncpy($$->str[1], $3.str, MAX_STRLEN);
					$$->num[0] = $1.num;
					$$->num[1] = $3.num;
}| DATA LT EQ DATA {
					$$ = new_node();
					$$->operation=E_LTEQ;
					$$->operand_type[0] = $1.type;
					$$->operand_type[1] = $4.type;
					strncpy($$->str[0], $1.str, MAX_STRLEN);
					strncpy($$->str[1], $4.str, MAX_STRLEN);
					$$->num[0] = $1.num;
					$$->num[1] = $4.num;
}| DATA EQ DATA {
					$$ = new_node();
					$$->operation=E_EQ;
					$$->operand_type[0] = $1.type;
					$$->operand_type[1] = $3.type;
					strncpy($$->str[0], $1.str, MAX_STRLEN);
					strncpy($$->str[1], $3.str, MAX_STRLEN);
					$$->num[0] = $1.num;
					$$->num[1] = $3.num;
}| DATA GT DATA {
					$$ = new_node();
					$$->operation=E_GT;
					$$->operand_type[0] = $1.type;
					$$->operand_type[1] = $3.type;
					strncpy($$->str[0], $1.str, MAX_STRLEN);
					strncpy($$->str[1], $3.str, MAX_STRLEN);
					$$->num[0] = $1.num;
					$$->num[1] = $3.num;
}| DATA GT EQ DATA {
					$$ = new_node();
					$$->operation=E_GTEQ;
					$$->operand_type[0] = $1.type;
					$$->operand_type[1] = $4.type;
					strncpy($$->str[0], $1.str, MAX_STRLEN);
					strncpy($$->str[1], $4.str, MAX_STRLEN);
					$$->num[0] = $1.num;
					$$->num[1] = $4.num;
}| DATA LT GT DATA {
					$$ = new_node();
					$$->operation=E_NEQ;
					$$->operand_type[0] = $1.type;
					$$->operand_type[1] = $4.type;
					strncpy($$->str[0], $1.str, MAX_STRLEN);
					strncpy($$->str[1], $4.str, MAX_STRLEN);
					$$->num[0] = $1.num;
					$$->num[1] = $4.num;
}| DATA EXM EQ DATA {
					$$ = new_node();
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
// void test_equijoin() {
// 	stmt_type = E_EQUIJOIN;
// 	strcpy(tables[0], "e");
// 	strcpy(tables[1], "w");
// 	strcpy(equi_tables[0], "w");
// 	strcpy(equi_tables[1], "e");
// 	strcpy(equi_id[0], "d");
// 	strcpy(equi_id[1], "b");
// 	run_sql();
// }
// void test_project(){
// 	stmt_type = E_PROJECT;
// 	strcpy(cols[0], "b");
// 	strcpy(cols[1], "a");
// 	strcpy(tables[0], "e");
// 	col_num = 2;
// 	run_sql();
// }
// void test_cartprod(){
// 	stmt_type = E_CARTPROD;
// 	strcpy(tables[0], "e");
// 	strcpy(tables[1], "w");
// 	run_sql();
// }
// void test_select(){
// 	stmt_type = E_SELECT;

// 	run_sql();
// }
int main(int argc, char **argv) {
	argc--;argv++;
	// if(!argc) {
		while(1) {
			init_ds();
			printf(">>> ");
			if(yyparse()) {
				printf("Invalid Syntax\n");
				continue;
			}
			// printf("Valid Syntax\n");
			// run_sql();
		}
		// return 0;
	// }
	// init_ds();
	// if(!strcmp(argv[0], "c"))
	// 	test_cartprod();
	// else if(!strcmp(argv[0], "p"))
	// 	test_project();
	// else if(!strcmp(argv[0], "e"))
	// 	test_equijoin();
	// else if(!strcmp(argv[0], "s"))
	// test_select();
	return 0;
}