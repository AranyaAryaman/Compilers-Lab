%{
#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#define DEBUG 1
int yylex();
int yyerror(char* msg __attribute__((unused))){}
%}

%token SELECT PROJECT CARPRO EQJN OR AND EQ COMMA ID NUM LP RP LA RA DOT NEWLINE
%start S1
%%
S1: S7 NEWLINE {YYACCEPT;}| S2 NEWLINE {YYACCEPT;}| S4 NEWLINE {YYACCEPT;}| S6 NEWLINE {YYACCEPT;}| error NEWLINE{YYABORT;};

S4: SELECT					LA S5 RA				LP ID RP ;
S2: PROJECT					LA S3 RA				LP ID RP ;
S7: LP ID RP				CARPRO					LP ID RP ;
S6: LP ID RP		EQJN			LA CONDITION RA			LP ID RP ;

S5: S5 AND CONDITION | S5 OR CONDITION | CONDITION ;
S3: S3 COMMA ID | ID ;
NID: ID DOT ID ;
CONDITION: DATA LA DATA | DATA LA EQ DATA | DATA EQ DATA | DATA RA DATA | DATA RA EQ DATA | DATA LA RA DATA ;
DATA: ID | NUM | NID ;
%%

#include"lex.yy.c"

int main() {
	while(1) {
		printf(">>>");
		if(yyparse()) {
			printf("Invalid Syntax\n");
			continue;
		}
		printf("Valid Syntax\n");
		// DO something here
	}
	return 0;
}