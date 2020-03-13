%{
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
int com_count = 0, func_dec = 0, var_dec = 0, func_def = 0, blank = 0, total = 0, mac_def = 0;
bool com_line = false, fdef_line = true, fdec_line = true, mdef_line = false, vdec_line = true, is_blank=true; 
%}
DATATYPE int|float|char|double|extern|long|const|void|short|auto|enum|signed|static|unsigned|FILE|bool|string
%option noyywrap
%x Mcomment Scomment Mdec
%%
[ \t]*{DATATYPE}[ \t]*[[:alnum:]]*[ \t]*[(][.]*[)][ \t]*[;]       {func_dec++; is_blank=false;}
[ \t]*{DATATYPE}[ \t]*[[:alnum:]]*[ \t]*[(][.]*[)][ \t]*[{]       {func_def++; is_blank=false;}
[ \t]*{DATATYPE}[ \t]*[[:alnum:]]*[ \t]*[,=\[;]       {var_dec++; is_blank=false;}
[ \t]     {is_blank=false;}
"\n"        {mdef_line=false; com_line=false; total++; if(is_blank)blank++; is_blank=true;}
"#"     {if(!mdef_line)++mac_def; is_blank=false;}
"//"        BEGIN(Scomment);
<Scomment>[^\n]*        /*eat anything that's not \n */
<Scomment>\n        {total++; if(!com_line){++com_count;} com_line=false; is_blank=true; BEGIN(INITIAL);}
"/*"        {BEGIN(Mcomment); is_blank=false;}
<Mcomment>[^*\n]*       /* eat anything that's not a '*' */
<Mcomment>"*"+[^*/\n]*  /* eat up '*'s not followed by '/'s */
<Mcomment>\n        {total++; if(!com_line){++com_count;} com_line=false;}
<Mcomment>"*"+"/"       {if(!com_line){++com_count; com_line=true;} BEGIN(INITIAL);}
.       {mdef_line=true; is_blank=false;}
%%

int main(int argc,char** argv){
FILE *fh;
    if (argc == 2 && (fh = fopen(argv[1], "r")))
        yyin = fh;
    yylex();
    printf("Total line count of comments is %d\nTotal line count of code is %d\nTotal line count of macro defination is %d\nTotal line count of blank lines is %d\nTotal line count of variable declaration is %d\nTotal line count of function declaration is %d\nTotal line count of function defination is %d", com_count, ++total, mac_def, blank, var_dec, func_dec, func_def);
    return 0;
}