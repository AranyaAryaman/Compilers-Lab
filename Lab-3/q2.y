%{
#include<stdio.h>
#include<string.h>
int yylex();
int yyerror(char* msg) {
	printf("%s\n", msg);
	return 0;
}
#include"sql_runner.h"
typedef struct data_ret{
	int type;
	char strval[MAX_STRLEN];
	int intval;
}data_ret;
%}

%token SELECT PROJECT CARTPROD EQUIJOIN OR AND EQ COMMA ID NUM LP RP LT GT DOT NEWLINE SINGLE_QUOTE DOUBLE_QUOTE
%type <str>			ID
%type <numdata>		NUM
%type <dataval>	DATA
%type <condvar>		CONDITION
%union{
	char str[25];
	int numdata;
	data_ret dataval;
	conditions condvar;
}
%start S1
%%
S1: S7 NEWLINE					{
									YYACCEPT;
								}

	| S2 NEWLINE				{
									YYACCEPT;
								}

	| S4 NEWLINE				{
									YYACCEPT;
								}

	| S6 NEWLINE				{
									YYACCEPT;
								}
								
	| error NEWLINE				{
									YYABORT;
								};

S4: SELECT LT S5 GT LP ID RP	{
									stmt_type=E_SELECT;
									strncpy(tables[0], $6, MAX_STRLEN);
								};

S2: PROJECT LT S3 GT LP ID RP	{
									stmt_type=E_PROJECT;
									strncpy(tables[0], $6, MAX_STRLEN);
								};

S7: LP ID RP CARTPROD LP ID RP	{
									stmt_type=E_CARTPROD;
									strncpy(tables[0], $2, MAX_STRLEN);
									strncpy(tables[1], $6, MAX_STRLEN);
								};

S6: LP ID RP EQUIJOIN LT ID DOT ID EQ ID DOT ID GT LP ID RP	{
															stmt_type=E_EQUIJOIN;
															strncpy(tables[0], $2, MAX_STRLEN);
															strncpy(tables[1], $15, MAX_STRLEN);
															strncpy(equi_tables[0], $6, MAX_STRLEN);
															strncpy(equi_tables[1], $10, MAX_STRLEN);
															strncpy(equi_id[0], $8, MAX_STRLEN);
															strncpy(equi_id[1], $12, MAX_STRLEN);
														};

S5: S5 AND CONDITION	{
							cond_list[cond_num].cond_join=E_AND;
							cond_list[cond_num].operation=$3.operation;
							cond_list[cond_num].operand_type[0]=$3.operand_type[0];
							cond_list[cond_num].operand_type[1]=$3.operand_type[1];
							strncpy(cond_list[cond_num].str[0],$3.str[0],MAX_STRLEN);
							strncpy(cond_list[cond_num].str[1],$3.str[1], MAX_STRLEN);
							cond_list[cond_num].num[0]=$3.num[0];
							cond_list[cond_num].num[1]=$3.num[1];
							cond_num++;
						}
						
	| S5 OR CONDITION	{
							cond_list[cond_num].cond_join=E_OR;
							cond_list[cond_num].operation=$3.operation;
							cond_list[cond_num].operand_type[0]=$3.operand_type[0];
							cond_list[cond_num].operand_type[1]=$3.operand_type[1];
							strncpy(cond_list[cond_num].str[0],$3.str[0],MAX_STRLEN);
							strncpy(cond_list[cond_num].str[1],$3.str[1], MAX_STRLEN);
							cond_list[cond_num].num[0]=$3.num[0];
							cond_list[cond_num].num[1]=$3.num[1];
							cond_num++;
						}

	| CONDITION			{
							cond_list[cond_num].cond_join=E_DUMMY;
							cond_list[cond_num].operation=$1.operation;
							cond_list[cond_num].operand_type[0]=$1.operand_type[0];
							cond_list[cond_num].operand_type[1]=$1.operand_type[1];
							strncpy(cond_list[cond_num].str[0],$1.str[0],MAX_STRLEN);
							strncpy(cond_list[cond_num].str[1],$1.str[1], MAX_STRLEN);
							cond_list[cond_num].num[0]=$1.num[0];
							cond_list[cond_num].num[1]=$1.num[1];
							cond_num++;
						};

S3: S3 COMMA ID			{
							strncpy(cols[col_num], $3, MAX_STRLEN);
							col_num++;
						}

	| ID				{
							strncpy(cols[col_num], $1, MAX_STRLEN);
							col_num++;
						};

CONDITION: DATA LT DATA	{
							$$.operation=E_LT;
							$$.operand_type[0]=$1.type;
							$$.operand_type[1]=$3.type;
							strncpy($$.str[0], $1.strval, MAX_STRLEN);
							strncpy($$.str[1], $3.strval, MAX_STRLEN);
							$$.num[0]=$1.intval;
							$$.num[1]=$3.intval;
						}

	| DATA LT EQ DATA	{
							$$.operation=E_LTEQ;
							$$.operand_type[0]=$1.type;
							$$.operand_type[1]=$4.type;
							strncpy($$.str[0], $1.strval, MAX_STRLEN);
							strncpy($$.str[1], $4.strval, MAX_STRLEN);
							$$.num[0]=$1.intval;
							$$.num[1]=$4.intval;
						}

	| DATA EQ DATA		{
							$$.operation=E_EQ;
							$$.operand_type[0]=$1.type;
							$$.operand_type[1]=$3.type;
							strncpy($$.str[0], $1.strval, MAX_STRLEN);
							strncpy($$.str[1], $3.strval, MAX_STRLEN);
							$$.num[0]=$1.intval;
							$$.num[1]=$3.intval;
						}

	| DATA GT DATA		{
							$$.operation=E_GT;
							$$.operand_type[0]=$1.type;
							$$.operand_type[1]=$3.type;
							strncpy($$.str[0], $1.strval, MAX_STRLEN);
							strncpy($$.str[1], $3.strval, MAX_STRLEN);
							$$.num[0]=$1.intval;
							$$.num[1]=$3.intval;
						}

	| DATA GT EQ DATA	{
							$$.operation=E_EQ;
							$$.operand_type[0]=$1.type;
							$$.operand_type[1]=$4.type;
							strncpy($$.str[0], $1.strval, MAX_STRLEN);
							strncpy($$.str[1], $4.strval, MAX_STRLEN);
							$$.num[0]=$1.intval;
							$$.num[1]=$4.intval;
						}

	| DATA LT GT DATA	{
							$$.operation=E_NEQ;
							$$.operand_type[0]=$1.type;
							$$.operand_type[1]=$4.type;
							strncpy($$.str[0], $1.strval, MAX_STRLEN);
							strncpy($$.str[1], $4.strval, MAX_STRLEN);
							$$.num[0]=$1.intval;
							$$.num[1]=$4.intval;
						};

DATA: ID				{
							$$.type=E_VAR;
							strncpy($$.strval, $1, MAX_STRLEN);
						}

	| NUM				{
							$$.type=E_INT;
							$$.intval=$1;
						}
	| SINGLE_QUOTE ID SINGLE_QUOTE	{
										$$.type=E_STR;
										strncpy($$.strval, $2, MAX_STRLEN);
									}

	| DOUBLE_QUOTE ID DOUBLE_QUOTE	{
										$$.type=E_STR;
										strncpy($$.strval, $2, MAX_STRLEN);
									};
%%

#include"lex.yy.c"
#include"sql_runner.h"
void test_equijoin() {
	stmt_type = E_EQUIJOIN;
	strcpy(tables[0], "e");
	strcpy(tables[1], "w");
	strcpy(equi_tables[0], "w");
	strcpy(equi_tables[1], "e");
	strcpy(equi_id[0], "d");
	strcpy(equi_id[1], "b");
	run_sql();
}
void test_project(){
	stmt_type = E_PROJECT;
	strcpy(cols[0], "b");
	strcpy(cols[1], "a");
	strcpy(tables[0], "e");
	col_num = 2;
	run_sql();
}
void test_cartprod(){
	stmt_type = E_CARTPROD;
	strcpy(tables[0], "e");
	strcpy(tables[1], "w");
	run_sql();
}
void test_select(){
	stmt_type = E_SELECT;

	run_sql();
}
int main(int argc, char **argv) {
	argc--;argv++;
	if(!argc) {
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
	init_ds();
	if(!strcmp(argv[0], "c"))
		test_cartprod();
	else if(!strcmp(argv[0], "p"))
		test_project();
	else if(!strcmp(argv[0], "e"))
		test_equijoin();
	else if(!strcmp(argv[0], "s"))
	test_select();
	return 0;
}