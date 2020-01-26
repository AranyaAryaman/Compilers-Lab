#include "code_gen.h"

#include "lex.h"
#include "main.h"
#include "name.h"

#include <stdio.h>
#include <stdlib.h>
int label_count = 0;
char *statements(void);
char *expression(void);
char *non_relational(void);
char *minomial(void);
char *term(void);
char *factor(void);

char *statements(void) {
	// statements ->    expression SEMI
	//              |   expression SEMI statements
	//              |   id COL EQ expression SEMI
	//              |   id COL EQ expression SEMI statements
	//              |   if expression then statements
	//              |   while expression do statements
	//              |   begin opt_statements end
	//              |   begin opt_statements end statements
	char *tempvar, *tempvar2;

	while(!match(EOI)) {
		if(match(IF)) {
			advance();
			tempvar = expression();
			printf("\tCMP %s\n", tempvar);
			label_count++;
			printf("\tJNZ LABEL%d\n", label_count);
			if(match(THEN)) {
				advance();
				tempvar2 = statements();
				printf("LABEL%d:\n", label_count);
			}
			freename(tempvar2);
		}

		else if(match(WHILE)) {
			advance();
			tempvar = expression();
			if(match(DO)) {
				advance();
				tempvar2 = statements();
			}
			// printf("WE HAVE REACHED THE ENDGAME");
			freename(tempvar2);
		} else {
			tempvar = expression();
		}
		if(match(SEMI))
			advance();
		else
			fprintf(stderr, "%d: Inserting missing semicolon in statements\n", yylineno);
		freename(tempvar);
	}
	return "STATEMENT_RETURN";
}
char *monomial(void) {
	// monomial ->      factor MUL monomial
	//              |   factor DIV monomial
	//              |   factor
	char *tempvar, *tempvar2;
	tempvar = factor();
	while(match(MUL) || match(DIV)) {
		char temp;
		if(match(MUL))
			temp = '*';
		else
			temp = '/';
		advance();
		tempvar2 = monomial();
		printf("\t%s %c= %s\n", tempvar, temp, tempvar2);
		freename(tempvar2);
	}
	return tempvar;
}
char *non_relational(void) {
	char *tempvar, *tempvar2;
	tempvar = monomial();
	// non_relational ->    non_relational + monomial
	//                  |   non_relational - monomial
	//                  |   monomial
	while(match(PLUS) || match(MINUS)) {
		char temp;
		if(match(PLUS))
			temp = '+';
		else
			temp = '-';
		advance();
		tempvar2 = non_relational();
		printf("\t%s %c= %s\n", tempvar, temp, tempvar2);
		freename(tempvar2);
	}
	return tempvar;
}
char *expression(void) {
	// expression ->    non_relational
	//              |   non_relational EQ non_relational
	//              |   non_relational GT non_relational
	//              |   non_relational LT non_relational

	char *tempvar, *tempvar2;

	tempvar = non_relational();
	while(match(EQ)) {
		advance();
		tempvar2 = non_relational();
		printf("\t%s == %s\n", tempvar, tempvar2);
		freename(tempvar2);
	}
	while(match(LT)) {
		advance();
		tempvar2 = non_relational();
		printf("\t%s <= %s\n", tempvar, tempvar2);
		freename(tempvar2);
	}
	while(match(GT)) {
		advance();
		tempvar2 = non_relational();
		printf("\t%s >= %s\n", tempvar, tempvar2);
		freename(tempvar2);
	}

	return tempvar;
}
char *term(void) {
	char *tempvar, *tempvar2;

	tempvar = factor();
	while(match(MUL)) {
		advance();
		tempvar2 = factor();
		printf("\t%s *= %s\n", tempvar, tempvar2);
		freename(tempvar2);
	}

	return tempvar;
}
char *factor(void) {
	char *tempvar;

	if(match(NUM_OR_ID)) {
		/* Print the assignment instruction. The %0.*s conversion is a form of
		 * %X.Ys, where X is the field width and Y is the maximum number of
		 * characters that will be printed (even if the string is longer). I'm
		 * using the %0.*s to print the string because it's not \0 terminated.
		 * The field has a default width of 0, but it will grow the size needed
		 * to print the string. The ".*" tells printf() to take the maximum-
		 * number-of-characters count from the next argument (yyleng).
		 */

		printf("\t%s = %.*s\n", tempvar = newname(), yyleng, yytext);
		advance();
	} else if(match(LP)) {
		advance();
		tempvar = non_relational();
		if(match(RP))
			advance();
		else
			fprintf(stderr, "%d: Mismatched parenthesis\n", yylineno);
	} else
		fprintf(stderr, "%d: Number or identifier expected\n", yylineno);

	return tempvar;
}


// statements()
// {
// 		/*statements -> statements statement | statement


// 	assFile = fopen("Assembly.asm", "w");
// 	interFile = fopen("Intermediate.txt", "w");

// 	fprintf(assFile, "%s\n", "ORG 0000h");

// 	while(!match(EOI))
// 		statement();

// 	fprintf(assFile, "%s\n", "END");
// 	fclose(assFile);
// 	fclose(interFile);
// }

// statement()
// {
// 	/*  statement -> ID:=expression1; | IF expression1 then statement |
// 		while expression1 do statement | expression1; |
// 		begin  stmt_list  end |
// 		begin end
// 	  */

// 	char *tempvar;


// 		if(match(ID))
// 		{
// 			char assignment[100];
// 			int loop_var=0;
// 			for(;loop_var<yyleng;loop_var++)assignment[loop_var]=*(yytext+loop_var);
// 			assignment[loop_var]='\0';

// 			advance();
// 			if( !legal_lookahead( COL, 0 ) )
// 				goto legal_lookahead_SEMI;
// 			if(match(COL))
// 			{
// 				advance();
// 				if( !legal_lookahead( EQUAL, 0 ) )
// 					goto legal_lookahead_SEMI;
// 				if(match(EQUAL))
// 				{
// 					advance();
// 					tempvar = expression1();
// 					fprintf(interFile,"%s <- %s\n",assignment,tempvar);

// 					if(strcmp(tempvar, "t0") == 0){
// 						fprintf(assFile, "STA _%s\n", assignment);
// 					} else {
// 						fprintf(assFile, "PUSH A\nMOV A %c\nSTA _%s\nPOP A\n", REG[tempvar[1]-'0'], assignment);
// 					}
// 				}
// 				else
// 				{
// 					fprintf( stderr, "%d: Inserting missing equal\n", yylineno );
// 				}
// 			}
// 			else
// 			{
// 				fprintf( stderr, "%d: Inserting missing colon\n", yylineno );
// 			}
// 		}
// 		else if(match(IF))
// 			{
// 				advance();
// 				fprintf(interFile, "if (\n");
// 				tempvar = expression1();
// 				if( !legal_lookahead( THEN, 0 ) )
// 				{
// 					freename(tempvar);
// 					fprintf( stderr, "%d: Inserting missing then\n", yylineno );
// 					goto legal_lookahead_SEMI;
// 				}
// 				if(match(THEN))
// 				{
// 					fprintf(interFile, "%s)\n", tempvar);
// 					int ifthenLabel = getIfThenLabel();
// 					fprintf(assFile, "CMP %c 0\nJZ IFTHEN%d\n", REG[tempvar[1] -'0'], ifthenLabel);
// 					fprintf(interFile, "%s\n", "then {");
// 					advance();
// 					freename(tempvar);
// 					statement();
// 					fprintf(interFile, "%s\n", "}");
// 					fprintf(assFile, "IFTHEN%d:\n", ifthenLabel);
// 					return;
// 				}
// 				else
// 					fprintf( stderr, "%d: Inserting missing then\n", yylineno );
// 			}
// 		else if(match(WHILE))
// 			{
// 				advance();
// 				int loopLabel1 = getLoopLabel();
// 				fprintf(assFile, "LOOP%d:\n",loopLabel1);
// 				fprintf(interFile, "while (\n");
// 				tempvar = expression1();
// 				if( !legal_lookahead( DO, 0 ) )
// 				{
// 					freename(tempvar);
// 					goto legal_lookahead_SEMI;
// 				}
// 				if(match(DO))
// 				{
// 					fprintf(interFile, "%s)\n", tempvar);
// 					int loopLabel = getLoopLabel();
// 					fprintf(assFile, "CMP %c 0\nJZ LOOP%d\n", REG[tempvar[1]-'0'], loopLabel);

// 					fprintf(interFile, "%s\n", "do {");
// 					advance();

// 					freename(tempvar);
// 					statement();
// 					fprintf(interFile, "%s\n", "}");
// 					fprintf(assFile, "JMP LOOP%d\nLOOP%d:\n", loopLabel1, loopLabel);
// 					// freename(tempvar);
// 					return;
// 				}
// 				else
// 					fprintf( stderr, "%d: Inserting missing do\n", yylineno );

// 			}
// 		else if(match(BEGIN))
// 		{

// 				fprintf(interFile, "%s\n", "BEGIN{");
// 				advance();
// 				if(match(END)){printf("END\n");advance();return;}
// 				stmt_list();
// 				if(!legal_lookahead(END,0))
// 				{
// 					fprintf( stderr, "%d: Inserting missing END\n", yylineno );
// 					goto legal_lookahead_SEMI;
// 				}

// 				fprintf(interFile, "} %s\n", "END");
// 				advance();
// 				return;
// 		}
// 		else tempvar = expression1();

// 		if(tempvar!=NULL)freename( tempvar );
// 		else exit(1);

// legal_lookahead_SEMI:
// 		if( match( SEMI ) )
// 			advance();
// 		else
// 			fprintf( stderr, "%d: Inserting missing semicolon\n", yylineno );
// }

// stmt_list()
// {

// 	/*stmt_list -> statement stmt_list*/

// 	while(!match(END)&&!match(EOI))
// 		statement();
// 	if(match(EOI))fprintf( stderr, "%d: End of file reached no END found\n", yylineno );
// }
// */