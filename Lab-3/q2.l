%option noyywrap
%%
(?i:select)												{return SELECT;}
(?i:project)											{return PROJECT;}
(?i:cartesian_product)									{return CARTPROD;}
(?i:equi_join)											{return EQUIJOIN;}
(?i:or)													{return OR;}
(?i:and)												{return AND;}
(?i:not)												{return NOT;}
[+-]?[[:digit:]]+\.?[[:digit:]]*						{
															yylval.str = str_duplicate(yytext);
															return NUM;
														}
[+-]?\.[[:digit:]]+										{
															yylval.str = str_duplicate(yytext);
															return NUM;
														}
[+-]?([[:digit:]]*\.)?[[:digit:]]+[eE][-+]?[[:digit:]]+	{
															yylval.str = str_duplicate(yytext);
															return NUM;
														}
[+-]?[[:digit:]]+\.[eE][-+]?[[:digit:]]+				{
															yylval.str = str_duplicate(yytext);
															return NUM;
														}
[[:alpha:]_]([[:alnum:]_])*								{
															yylval.str = str_duplicate(yytext);
															return ID;
														}
[=]														{return EQ;}
[(]														{return LP;}
[)]														{return RP;}
[,]														{return COMMA;}
[<]														{return LT;}
[>]														{return GT;}
[.]														{return DOT;}
["]([^"\\\n]|\\.)*["]									{
															yylval.str = str_escape(yytext);
															return QUOTED_STRING;
														}
[']([^'\\\n]|\\.)*[']									{
															yylval.str = str_escape(yytext);
															return QUOTED_STRING;
														}
[\n]													{return NEWLINE;}
[!]														{return EXM;}
[ \t\r\v\f]+											{}
<<EOF>>													{return ENDOF;}
.														{return yytext[0];}

%%