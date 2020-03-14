%{
#include<stdio.h>
#include<string.h>
int yylex();
int yyerror(char* msg __attribute__((unused))){}
#include"sql_runner.h"
int i=0;
%}

%token SELECT PROJECT CARPRO EQJN OR AND EQ COMMA ID NUM LP RP LA RA DOT NEWLINE SINGLE_QUOTE DOUBLE_QUOTE
%type <str>			ID
%type <numdata>		NUM
%type <data_ret>	DATA
%union{
	char str[25];
	int numdata;
	struct data_ret{int type;char strval[MAX_STRLEN];int intval;};
}
%start S1
%%
S1: S7 NEWLINE {YYACCEPT;}| S2 NEWLINE {YYACCEPT;}| S4 NEWLINE {YYACCEPT;}| S6 NEWLINE {YYACCEPT;}| error NEWLINE{YYABORT;};

S4: SELECT			LA S5 RA		LP ID RP {stmt_type=E_SELECT; strncpy(tables[0], $6, MAX_STRLEN);}
S2: PROJECT			LA S3 RA		LP ID RP {stmt_type=E_PROJECT; strncpy(tables[0], $6, MAX_STRLEN);}
S7: LP ID RP		CARPRO			LP ID RP {stmt_type=E_CARTPROD; strncpy(tables[0], $2, MAX_STRLEN); strncpy(tables[1], $6, MAX_STRLEN);}
S6: LP ID RP		EQJN			LA ID DOT ID EQ ID DOT ID RA			LP ID RP {stmt_type=E_EQUIJOIN; strncpy(tables[0], $2, MAX_STRLEN); strncpy(tables[1], $15, MAX_STRLEN);}

S5: S5 AND CONDITION {cond_list[i].cond_join=E_AND;}| S5 OR CONDITION {cond_list[i].cond_join=E_OR;}| CONDITION ;
S3: S3 COMMA ID | ID ;
CONDITION: DATA LA DATA {con_list[i].oper}| DATA LA EQ DATA | DATA EQ DATA | DATA RA DATA | DATA RA EQ DATA | DATA LA RA DATA ;
DATA: ID {$$->type=E_STR; strncpy($$->strval, $1, MAX_STRLEN)}| NUM {$$->type=E_INT; strncpy($$->intval, $1, MAX_STRLEN)}| SINGLE_QUOTE ID SINGLE_QUOTE {$$->type=E_STR; strncpy($$->strval, $2, MAX_STRLEN)}| DOUBLE_QUOTE ID DOUBLE_QUOTE {$$->type=E_STR; strncpy($$->strval, $2, MAX_STRLEN)};
%%

#include"lex.yy.c"
#include"sql_runner.h"
int main() {
	// // while(1) {
	// 	init_ds();
	// 	// strcpy(cols[0], "b");
	// 	// strcpy(cols[1], "a");
	// 	// col_num = 2;
	// 	stmt_type = E_CARTPROD;
	// 	strcpy(tables[0], "e");
	// 	strcpy(tables[1], "e");
	// 	// printf(">>>");
	// 	// if(yyparse()) {
	// 	// 	printf("Invalid Syntax\n");
	// 	// 	continue;
	// 	// }
	// 	// printf("Valid Syntax\n");
	// 	run_sql();
	// // }
	while(1) {
		printf(">>>");
		if(yyparse()) {
			printf("Invalid Syntax\n");
			continue;
		}
		printf("\n%s\n", tables[0]);
		printf("Valid Syntax\n");
	}
	return 0;
}