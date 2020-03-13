%{
    #include<stdio.h>
    #include<stdlib.h>
	int yylex(void);
	int yyerror(char *msg);
%}

%token SELECT PROJECT CARPRO EQJN OR AND EQ COMMA ID NUM LP RP LA RA DOT

%%
    S1: S7 | S2 | S4 | S6
        ;
    S7: LP ID RP CARPRO LP ID RP
        ;
    S2: PROJECT LA ID S3 RA LP ID RP
        ;
    S4: SELECT LA CONDITION S5 RA LP ID RP
        ;
    S6: LP ID RP EQJN LA CONDITION S5 RA LP ID RP
        ;

    S3: COMMA ID S3 | EPSILON
        ;
    S5: AND CONDITION S5 | OR CONDITION S5 | EPSILON
        ;
    EPSILON:
        ;
    NID: ID DOT ID
        ;
    CONDITION: DATA OPERATION DATA
        ;
    DATA: ID | NUM | NID
        ;
    OPERATION: LA | RA | EQ | LA EQ | RA EQ
        ;
%%

#include"lex.yy.c"
#include<ctype.h>
int yyerror(char *msg)
{
    printf("Invalid Syntax\n");
    exit(0);
}

int main()
{
    printf("Enter the RA input:");
    yyparse();
    printf("Valid Syntax\n");
	return 0;
}
