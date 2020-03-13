%{
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
int com_count = 0, blank = 0, total = 0, mac_def = 0;
bool com_line = false, mdef_line = false, is_blank=true; 
%}
DATATYPE int|float|char|double|extern|long|const|void|short|auto|enum|signed|static|unsigned|FILE|bool|string
B [ \t]*
COMMENT "/*"[.]*"*/"|""
%option noyywrap
%x Mcomment Scomment Mdec pass2
%%
[ \t]+      {printf(" ");}
"\n"[ \t]*        {mdef_line=false; com_line=false; total++; if(is_blank)blank++; else printf("\n"); is_blank=true;}
"#"     {if(!mdef_line)++mac_def; is_blank=false;printf("%s", yytext);}
"//"        BEGIN(Scomment);
<Scomment>[^\n]*        /*eat anything that's not \n */
<Scomment>\n        {total++; if(!com_line){++com_count;} com_line=false; is_blank=true; BEGIN(INITIAL);}
"/*"        {BEGIN(Mcomment); is_blank=false;}
<Mcomment>[^*\n]*       /* eat anything that's not a '*' */
<Mcomment>"*"+[^*/\n]*  /* eat up '*'s not followed by '/'s */
<Mcomment>\n        {total++; if(!com_line){++com_count;} com_line=false;}
<Mcomment>"*"+"/"       {if(!com_line){++com_count; com_line=true;} BEGIN(INITIAL);}
.       {mdef_line=true; is_blank=false;printf("%s", yytext);}
%%

int main(int argc,char** argv){
    FILE *fh;
    if (argc == 3 && (fh = fopen(argv[1], "r")))
        yyin = fh;
    yylex();
    FILE *f=fopen("output.txt", "a");
    if(!strcmp(argv[2], "1")){
        fprintf(f,"Total line count of comments is %d\nTotal line count of code is %d\nTotal line count of macro defination is %d\nTotal line count of blank lines is %d\n", com_count, ++total, mac_def, blank);
    }
    fclose(f);
    fclose(fh);
    return 0;
}