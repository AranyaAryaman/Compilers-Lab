%option noyywrap
%%
(?i:select)				    {return SELECT;}
(?i:project)			    {return PROJECT;}
(?i:cartesian_product)	    {return CARTPROD;}
(?i:equi_join)			    {return EQUIJOIN;}
(?i:or)					    {return OR;}
(?i:and) 				    {return AND;}
(?i:not)                    {return NOT;}
[[:digit:]]+				{yylval.num = atoi(yytext);return NUM;}
[[:alpha:]_]([[:alnum:]_])*	{strncpy(yylval.str, yytext, MAX_STRLEN);return ID;}
"="						    {return EQ;}
"("						    {return LP;}
")"						    {return RP;}
","						    {return COMMA;}
"<"						    {return LT;}
">"						    {return GT;}
"."						    {return DOT;}
"\""                        {return DOUBLE_QUOTE;}
"'"                         {return SINGLE_QUOTE;}
"\n"					    {return NEWLINE;}
"!"                         {return EXM;}
[ \t\r\v\f]+			    {}
<<EOF>>                     {return ENDOF;}
.       				    {return yytext[0];}
%%