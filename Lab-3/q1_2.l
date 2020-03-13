%{
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
int func_dec = 0, var_dec = 0, func_def = 0;
bool fdef_line = true, fdec_line = true, vdec_line = true; 
%}
DATATYPE int|float|char|double|extern|long|const|void|short|auto|enum|signed|static|unsigned|FILE|bool|string
B [ \t\n]*
%option noyywrap
%%
{B}{DATATYPE}{B}[[:alnum:]]*{B}[(][.]*[)]{B}[;]       {func_dec++;}
{B}{DATATYPE}{B}[[:alnum:]]*{B}[(][.]*[)]{B}[{]       {func_def++;}
{B}{DATATYPE}{B}[*]*[[:alnum:]]*{B}[,=\[;]       {var_dec++;}
.       ;
%%

int main(int argc,char** argv){
    FILE *fh;
    if (argc == 2 && (fh = fopen(argv[1], "r")))
        yyin = fh;
    yylex();
    FILE *f=fopen("output.txt", "a");
    fprintf(f,"Total line count of variable declaration is %d\nTotal line count of function declaration is %d\nTotal line count of function defination is %d", var_dec, func_dec, func_def);
    fclose(f);
    fclose(fh);
    return 0;
}