%{ 
int no_of_lines = 0;
int single_comments = 0;
int multi_comments = 0;
int variables = 0; 
int macro_definitions = 0;
%} 

TYPE int|char|bool|float|double|short|long
SECONDTYPE extern|auto|static
DIGIT [0-9]
ID [a-z][a-z0-9A-Z]*
SPACE " "

%% 
#define ++macro_definitions; 
{TYPE}{SPACE}{ID} ++variables;
{SECONDTYPE}{SPACE}{ID} ++variables;
{SECONDTYPE}{SPACE}{TYPE}{SPACE}{ID} ++variables;  
"/""/" ++single_comments;
"/""*"(.*|\n*)"*""/" ++multi_comments;
\n ++no_of_lines;
. {}
end return 0;
%% 

int yywrap(){} 

int main()
{ 
	FILE *fp; 
	//char filename[50]; 
	//printf("Enter the filename: \n"); 
	//scanf("%s",filename); 
	fp = fopen("a.txt","r"); 
	yyin = fp; 

	yylex(); 
	printf("Source Code Statements= %d\n", no_of_lines);
	printf("Number of Comments= %d\n", single_comments+multi_comments);
	printf("Number of Macro Definitions= %d\n", macro_definitions);
	printf("Number of Variable Declarations= %d\n", variables);	
	return 0; 
} 

