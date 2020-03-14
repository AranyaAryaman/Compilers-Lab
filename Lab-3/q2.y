%{
#include<stdio.h>
int yylex();
int yyerror(char* msg __attribute__((unused))){}
#include"sql_runner.h"
%}

%token SELECT PROJECT CARPRO EQJN OR AND EQ COMMA ID NUM LP RP LA RA DOT NEWLINE
%start S1
%%
S1: S7 NEWLINE {YYACCEPT;}| S2 NEWLINE {YYACCEPT;}| S4 NEWLINE {YYACCEPT;}| S6 NEWLINE {YYACCEPT;}| error NEWLINE{YYABORT;};

S4: SELECT			LA S5 RA		LP ID RP ;
S2: PROJECT			LA S3 RA		LP ID RP ;
S7: LP ID RP		CARPRO			LP ID RP ;
S6: LP ID RP		EQJN			LA CONDITION RA			LP ID RP ;

S5: S5 AND CONDITION | S5 OR CONDITION | CONDITION ;
S3: S3 COMMA ID | ID ;
NID: ID DOT ID ;
CONDITION: DATA LA DATA | DATA LA EQ DATA | DATA EQ DATA | DATA RA DATA | DATA RA EQ DATA | DATA LA RA DATA ;
DATA: ID | NUM | NID ;
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
	// while(1) {
		// printf(">>>");
		// if(yyparse()) {
		// 	printf("Invalid Syntax\n");
		// 	continue;
		// }
		// printf("Valid Syntax\n");
		// run_sql();
	// }
		argc--;argv++;
		if(!argc)
			return 0;
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