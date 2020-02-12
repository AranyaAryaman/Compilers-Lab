#include<stdio.h>
#include<stdlib.h>

int main()
{
	FILE *fptr;
	int lines=0,comments=0,comment_state=0,blank_lines=0,blank_state=0;		
	char c;
	fptr=fopen("input2.txt","r");
	if(fptr==NULL)
	{
		printf("Couldn't find the file!\n");
		return 0;
	}
	c=getc(fptr);
	while(c!=EOF)
	{
		if(c=='\n')
		{
			lines++;
			if(blank_state==1)
			{
				blank_lines++;
				blank_state=0;
			}
			c=getc(fptr);
			if(c=='\n')
			{
				blank_state=1;
				blank_lines++;
				lines++;
			}
		}
		if(c=='/')
		{
			c=getc(fptr);
			if(c=='*')
			{
				comment_state=1;
			}
		}
		if(c=='*')
		{
			c=getc(fptr);
			if(c=='/' && comment_state==1)
			{
				comments++;
				comment_state=0;
			}			
		}
		if(c!='\n')
		{
			blank_state=0;
		}
		c=getc(fptr);	
	}
	fclose(fptr);
	printf("Number of statements		: %d\n",lines);
	printf("Number of Comments		: %d\n",comments);
	printf("Number of blank lines		: %d\n",blank_lines);
	return 0;
}
