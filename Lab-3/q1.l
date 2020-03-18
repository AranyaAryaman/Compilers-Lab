%{
#include <stdio.h>
#include <string.h>
int k=0;
int blank = 0;
int total = 0;
int mac_def = 0;
int var_dec = 0;
int com_line = 0;
int func_dec = 0;
int func_def = 0;
int in_pass2 = 0;
int is_blank = 1;
int com_count = 0;
int fdec_line = 0;
int fdef_line = 0;
int mdef_line = 0;
int vdec_line = 0; 
FILE *inter_file;// = fopen("inter_file.txt", "w");
// %option noyywrap
%}
DATATYPE int|float|char|double|extern|long|const|void|short|auto|enum|signed|static|unsigned|FILE|int|string
B [ \t]*
COMMENT "/*"[.]*"*/"|""
%x Mcomment Scomment Mdec pass2
%%
[ \t]+				{
						fprintf(inter_file, " ");
					}

"\n"[ \t]*			{
						mdef_line=0;
						com_line=0;
						total++;
						if(is_blank)
							blank++;
						else
							fprintf(inter_file, "\n");
						is_blank=1;
						k=0;
					}

"#"					{
						if(!mdef_line)
							mac_def++;
						is_blank=0;
						fprintf(inter_file, "%s", yytext);
					}

"//"				{
						BEGIN(Scomment);
						k=1;
					}

<Scomment>[^\n]*	{/*eat anything that's not \n */}

<Scomment>\n		{
						total++;
						if(!com_line)
							com_count++;
						com_line=0;
						is_blank=1;
						BEGIN(INITIAL);
						k=0;
					}

"/*"				{
						BEGIN(Mcomment);
						is_blank=0;
						k=1;
					}

<Mcomment>[^*\n]*		{/* eat anything that's not a '*' */}

<Mcomment>"*"+[^*/\n]*	{/* eat up '*'s not followed by '/'s */}

<Mcomment>\n			{
							total++;
							if(!com_line)
								com_count++;
							com_line=0;
						}
						
<Mcomment>"*"+"/"		{
							if(!com_line) {
								com_count++;
								com_line=1;
							}
							BEGIN(INITIAL);
						}

.						{
							mdef_line=1;
							is_blank=0;
							fprintf(inter_file, "%s", yytext);
						}

<pass2>{B}{DATATYPE}{B}[[:alnum:]]*{B}[(][.]*[)]{B}[;]			{fdec_line=1;}

<pass2>{B}{DATATYPE}{B}[[:alnum:]]*{B}[(][.]*[)]{B}[{]			{fdef_line=1;}

<pass2>{B}{DATATYPE}{B}[[:alnum:]]*{B}[(][.]*[)]{B}[\n][{]		{fdef_line=1;}

<pass2>{B}{DATATYPE}{B}[*]*[[:alnum:]]*{B}[,=\[;]				{vdec_line=1;}

<pass2>\n		{
					if(fdef_line)
						func_def++;
					if(fdec_line)
						func_dec++;
					if(vdec_line)
						var_dec++;
					fdec_line=0;
					fdef_line=0;
					vdec_line=0;
				}

<pass2>.		{}
%%
int yywrap(){
	if(in_pass2){
		fclose(inter_file);
		{if(fdef_line)func_def++; if(fdec_line)func_dec++; if(vdec_line)var_dec++; fdec_line=0; fdef_line=0; vdec_line=0;}
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
		in_pass2 = 1;
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
