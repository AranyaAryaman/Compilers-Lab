%option noyywrap
%%
(?i:select)				    {return SELECT;}
(?i:project)			    {return PROJECT;}
(?i:cartesian_product)	    {return CARPRO;}
(?i:equi_join)			    {return EQJN;}
(?i:or)					    {return OR;}
(?i:and) 				    {return AND;}
[[:digit:]]+				{yylval.numdata = atoi(yytext); return NUM;}
[[:alpha:]_]([[:alnum:]_])*	{sscanf(yytext, "%s", yylval.str); return ID;}
"="						    {return EQ;}
"("						    {return LP;}
")"						    {return RP;}
","						    {return COMMA;}
"<"						    {return LA;}
">"						    {return RA;}
"."						    {return DOT;}
["]                         {return DOUBLE_QUOTE;}
[']                         {return SINGLE_QUOTE;}
"\n"					    {return NEWLINE;}
[ \t\r\v\f]+			    {}
.       				    {return yytext[0];}
%%