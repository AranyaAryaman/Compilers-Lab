%option noyywrap
%%
(?i:select)				    {return SELECT;}
(?i:project)			    {return PROJECT;}
(?i:cartesian_product)	    {return CARTPROD;}
(?i:equi_join)			    {return EQUIJOIN;}
(?i:or)					    {return OR;}
(?i:and) 				    {return AND;}
[[:digit:]]+				{return NUM;}
[[:alpha:]_]([[:alnum:]_])*	{return ID;}
"="						    {return EQ;}
"("						    {return LP;}
")"						    {return RP;}
","						    {return COMMA;}
"<"						    {return LT;}
">"						    {return GT;}
"."						    {return DOT;}
["]                         {return DOUBLE_QUOTE;}
[']                         {return SINGLE_QUOTE;}
"\n"					    {return NEWLINE;}
[ \t\r\v\f]+			    {}
.       				    {return yytext[0];}
%%