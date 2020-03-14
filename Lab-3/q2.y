%{
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
int yylex();
int yyerror(char* msg) {
	printf("%s\n", msg);
	return 0;
}
%}

%token SELECT PROJECT CARTPROD EQUIJOIN OR AND EQ COMMA ID NUM LP RP LT GT DOT NEWLINE SINGLE_QUOTE DOUBLE_QUOTE
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

S4: SELECT LT S5 GT LP ID RP ;

S2: PROJECT LT S3 GT LP ID RP ;

S7: LP ID RP CARTPROD LP ID RP ;

S6: LP ID RP EQUIJOIN LT ID DOT ID EQ ID DOT ID GT LP ID RP ;

S5: S5 AND CONDITION
	| S5 OR CONDITION
	| CONDITION ;

S3: S3 COMMA ID
	| ID ;

CONDITION: DATA LT DATA
	| DATA LT EQ DATA
	| DATA EQ DATA
	| DATA GT DATA
	| DATA GT EQ DATA
	| DATA LT GT DATA ;

DATA: ID
	| NUM
	| SINGLE_QUOTE ID SINGLE_QUOTE
	| DOUBLE_QUOTE ID DOUBLE_QUOTE ;
%%

#include"lex.yy.c"
int main(int argc, char **argv) {
	while(1) {
		printf(">>> ");
		if(yyparse()) {
			printf("Invalid Syntax\n");
			continue;
		}
		printf("Valid Syntax\n");
	}
	return 0;
}