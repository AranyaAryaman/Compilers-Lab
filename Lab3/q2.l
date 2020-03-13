%{
    #include "q2.tab.h"
%}

alpha [A-Za-z]
digit [0-9]
%option noyywrap
%%

[ \t\n]+
select return SELECT;
project return PROJECT;
cartesian_product return CARPRO;
equi_join return EQJN;
or return OR;
and return AND;
{digit}+ return NUM;
{alpha}({alpha}|{digit})* return ID;
"=" return EQ;
"(" return LP;
")" return RP;
"," return COMMA;
"<" return LA;
">" return RA;
"." return DOT;
. return yytext[0];

%%