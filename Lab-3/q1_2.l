%{
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
int func_dec = 0, var_dec = 0, func_def = 0;
bool fdef_line = false, fdec_line = false, vdec_line = false; 
%}
DATATYPE int|float|char|double|extern|long|const|void|short|auto|enum|signed|static|unsigned|FILE|bool|string
B [ \t]*
%option noyywrap
%%
{B}{DATATYPE}{B}[*]*{B}[[:alnum:]]*{B}[(][.]*[)]{B}[;]       {fdec_line=true;}
{B}{DATATYPE}{B}[*]*{B}[[:alnum:]]*{B}[(][.]*[)]{B}[{]       {fdef_line=true;}
{B}{DATATYPE}{B}[*]*{B}[[:alnum:]]*{B}[(][.]*[)]{B}[\n][{]       {fdef_line=true;}
{B}{DATATYPE}{B}[*]*{B}[[:alnum:]]*{B}[,=\[;]       {vdec_line=true;}
"\n"        {if(fdef_line)func_def++; if(fdec_line)func_dec++; if(vdec_line)var_dec++; fdec_line=false; fdef_line=false; vdec_line=false;}
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