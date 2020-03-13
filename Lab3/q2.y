%{
    #include<stdio.h>
    #include<stdlib.h>
	int yylex(void);
	int yyerror(char *msg);
%}

%token SELECT PROJECT CARPRO EQJN OR AND EQ COMMA ID NUM LP RP LA RA DOT

%%
    S1: S7 {printf("Valid Syntax\n");exit(0);} | S2 {printf("Valid Syntax\n");exit(0);} | S4 {printf("Valid Syntax\n");exit(0);} | S6 {printf("Valid Syntax\n");exit(0);} ;
    S7: LP ID RP CARPRO LP ID RP ;
    S2: PROJECT LA ID S3 RA LP ID RP ;
    S3: COMMA ID S3 | EPSILON ;
    S4: SELECT LA CONDITION S5 RA LP ID RP;
    S5: AND CONDITION S5 | OR CONDITION S5 | EPSILON ;
    S6: LP ID RP EQJN LA CONDITION S5 RA LP ID RP;
    EPSILON: ;
    NID: ID DOT ID;
    CONDITION: ID LA ID | ID RA ID | ID EQ ID | ID LA NUM | ID RA NUM | ID EQ NUM | NID EQ NID | NID LA NID | NID RA NID ; 
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
	return 0;
}