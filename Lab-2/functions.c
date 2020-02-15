#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<string.h>

int var_state=0;
int func_def_state=0;
int func_dec_state=0;
int vCount=0, fdefCount=0, fdecCount=0;
int isDataType( char buffer[] ){
	char datatype[15][10]={"int", "float", "char", "double", "extern", "long", "const", "void", "short", "auto", "enum", "signed", "static", "unsigned", "FILE"};
	int i, flag = 0;
	
	for(i = 0; i < 32; ++i){
		if(strcmp(datatype[i], buffer) == 0){
			flag = 1;
			break;
		}
	}

	return flag;
}

int main(int argc, char *argv[]){
	/*if ( argc < 2 ){
		fprintf( stderr, "USAGE: %s  <filename>\n", argv[0] );
		exit( EXIT_FAILURE );
	}*/
	FILE *fp = fopen( "in.txt", "r");
	if(!fp){
		fprintf( stderr, "Cannot open file %s\n", argv[1] );
	 	exit( EXIT_FAILURE );
	}
	int i=0;
	int flag=0;
	int count=0;
	char c='\0';
	char buffer[10]={""};
	while((c=fgetc(fp))!=EOF){
		flag=0;
		while(1){
			if(c==' '||c=='\t'||c=='\r'||c=='\n'){
				c=fgetc(fp);
			}else break;
		}
		count=0;
		while(count<10){
			printf("%c", c);
			buffer[count]=c;
			count++;
			buffer[count]='\0';
			c=fgetc(fp);
			if(c==' '||c=='\t'||c=='\r'||c=='\n'){
				break;
			}
		}
		if(isDataType(buffer)){
		var_state=1;
	 	func_dec_state=1;
	 	func_def_state=1;
			while((c=fgetc(fp))!=EOF){
				printf(" %c", c);
		 		if(c=='='||c==','){
		 			flag=1;
		 			func_dec_state=0;
		 			func_def_state=0;
		 		}
		 		else if(c=='('){
		 			flag=1;
		 			var_state=0;
		 		}
		 		else if(c=='{'){
		 			flag=1;
		 			var_state=0;
		 			func_dec_state=0;
		 		}
		 		else if(c==';'){
		 			flag=1;
		 			func_def_state=0;
		 		}
		 		if(flag==1){
		 			while((c=fgetc(fp))&&(c!='\n')&&(c!=EOF)){
		 				continue;
		 			}
		 			if(var_state==1){
		 				vCount++;
		 			}
		 			if(func_def_state==1){
		 				fdefCount++;
		 			}
		 			else if(func_dec_state==1){
		 				fdecCount++;
		 			}
		 			printf("%d, %d, %d\n", vCount, fdefCount, fdecCount);
		 			var_state=0;
		 			func_dec_state=0;
		 			func_def_state=0;
		 			break;
		 		}
			}
		var_state=0;
		func_dec_state=0;
		func_def_state=0;
		}
		else{
			while((c=fgetc(fp))&&(c!='\n')&&(c!=EOF)){
				continue;
			}
		}
	}
	printf("%d number of variables", vCount);
	printf("%d number of function declaration", fdecCount);
	printf("%d number of function defination", fdefCount);
	return 0;
}
