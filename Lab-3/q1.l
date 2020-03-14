%{
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
int com_count = 0, blank = 0, total = 0, mac_def = 0;
bool com_line = false, mdef_line = false, is_blank=true, k=false;
int func_dec = 0, var_dec = 0, func_def = 0;
bool fdef_line = false, fdec_line = false, vdec_line = false; 
bool in_pass2 = false;
FILE *inter_file;// = fopen("inter_file.txt", "w");
// %option noyywrap
%}
DATATYPE int|float|char|double|extern|long|const|void|short|auto|enum|signed|static|unsigned|FILE|bool|string
B [ \t]*
COMMENT "/*"[.]*"*/"|""
%x Mcomment Scomment Mdec pass2
%%
[ \t]+      {fprintf(inter_file, " ");}
"\n"[ \t]*        {mdef_line=false; com_line=false; total++; if(is_blank)blank++; else fprintf(inter_file, "\n"); is_blank=true; k=false;}
"#"     {if(!mdef_line)++mac_def; is_blank=false;fprintf(inter_file, "%s", yytext);}
"//"        {BEGIN(Scomment); k=true;}
<Scomment>[^\n]*        /*eat anything that's not \n */
<Scomment>\n        {total++; if(!com_line){++com_count;} com_line=false; is_blank=true; BEGIN(INITIAL); k=false;}
"/*"        {BEGIN(Mcomment); is_blank=false; k=true;}
<Mcomment>[^*\n]*       /* eat anything that's not a '*' */
<Mcomment>"*"+[^*/\n]*  /* eat up '*'s not followed by '/'s */
<Mcomment>\n        {total++; if(!com_line){++com_count;} com_line=false;}
<Mcomment>"*"+"/"       {if(!com_line){++com_count; com_line=true;} BEGIN(INITIAL);}
.       {mdef_line=true; is_blank=false;fprintf(inter_file, "%s", yytext);}
<pass2>{B}{DATATYPE}{B}[[:alnum:]]*{B}[(][.]*[)]{B}[;]       {fdec_line=true;}
<pass2>{B}{DATATYPE}{B}[[:alnum:]]*{B}[(][.]*[)]{B}[\n][{]       {fdef_line=true;}
<pass2>{B}{DATATYPE}{B}[[:alnum:]]*{B}[(][.]*[)]{B}[{]       {fdef_line=true;}
<pass2>{B}{DATATYPE}{B}[*]*[[:alnum:]]*{B}[,=\[;]       {vdec_line=true;}
<pass2>\n       {if(fdef_line)func_def++; if(fdec_line)func_dec++; if(vdec_line)var_dec++; fdec_line=false; fdef_line=false; vdec_line=false;}
<pass2>.       {;}
%%
int yywrap(){
    if(in_pass2){
        fclose(inter_file);
        {if(fdef_line)func_def++; if(fdec_line)func_dec++; if(vdec_line)var_dec++; fdec_line=false; fdef_line=false; vdec_line=false;}
        printf("Total line count of variable declaration is %d\n", var_dec);
        printf("Total line count of function declaration is %d\n", func_dec);
        printf("Total line count of function defination is %d\n", func_def);
        remove("inter_file.txt");
        return 1;
    }else{
        total++;
        if(!com_line && k){++com_count;}
        printf("Total line count of comments is %d\n", com_count);
        printf("Total line count of code is %d\n", total);
        printf("Total line count of macro defination is %d\n", mac_def);
        printf("Total line count of blank lines is %d\n", blank);
        fclose(yyin);

        fclose(inter_file);
        inter_file = fopen("inter_file.txt", "r");
        yyin = inter_file;
        BEGIN(pass2);
        in_pass2 = true;
        return 0;
    }
}
int main(int argc,char** argv){
    FILE *fh;
    if (argc == 2 && (fh = fopen(argv[1], "r")))
        yyin = fh;
    inter_file = fopen("inter_file.txt", "w");
    yylex();
    return 0;
}
